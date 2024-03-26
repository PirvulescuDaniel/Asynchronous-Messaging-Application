#include "pch.h"
#include "TCPClient.h"
#include "Session.h"
#include "IRequest.h"
#include "RequestEncoder.h"
#include "IRequestHandler.h"

TCPClient::TCPClient()
{
	// Force the "run()" method from service not to exit when it has no more events to process.
	mWork.reset(new asio::io_service::work(mIoService));

	mServiceThreadPool.reset(new std::thread(
		[this]()
		{
			mIoService.run();
		}
	));
}

void TCPClient::SendRequest(RequestPtr aRequest, std::string_view aServerIp, unsigned short aServerPort)
{
	auto session = std::make_shared<Session>(mIoService, aServerIp, aServerPort, aRequest, nullptr); //to be modified.

	session->mSocket.open(session->mServerEndpoint.protocol());

	{
		std::unique_lock<std::mutex> lock(mActiveSessionsGuard);
		mActiveSessions.insert(std::make_pair(aRequest->GetId(), session));
	}

	session->mSocket.async_connect(session->mServerEndpoint,
		[this,session](const asio::error_code& aErrorCode)
		{
			if (aErrorCode.value() != 0)
			{
				session->mErrorCode = aErrorCode;
				OnRequestComplete(session);
				return;
			}

			OnConnect(session);
		}
	);
}

void TCPClient::CancelRequest(unsigned int aRequestId)
{
	std::unique_lock<std::mutex> activeSessionsLock(mActiveSessionsGuard);

	auto sessionIt = mActiveSessions.find(aRequestId);
	if (sessionIt != mActiveSessions.end())
	{
		auto& session = sessionIt->second;

		std::unique_lock<std::mutex> cancelLock(session->mCancelGuard);

		session->mCanceled = true;
		session->mSocket.cancel();
	}
}

void TCPClient::Close()
{
	// Let the "run()" method to exit.
	mWork.reset(nullptr);

	mIoService.stop();

	if (mServiceThreadPool && mServiceThreadPool->joinable())
		mServiceThreadPool->join();
}

void TCPClient::OnConnect(SessionPtr aSession)
{
	{	
		std::unique_lock<std::mutex> cancelLock(aSession->mCancelGuard);

		if (aSession->mCanceled)
		{
			OnRequestComplete(aSession);
			return;
		}
	}
	
	RequestEncoder encoder;
	const auto encodedRequest = encoder.EncodeRequest(aSession->mRequest.get());

	asio::async_write(aSession->mSocket, asio::buffer(encodedRequest),
		[this,aSession](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			if (aErrorCode.value() != 0)
			{
					aSession->mErrorCode = aErrorCode;
					OnRequestComplete(aSession);
					return;
			}

			OnSent(aSession);
		}
	);
}

void TCPClient::OnSent(SessionPtr aSession)
{
	{
		std::unique_lock<std::mutex> cancelLock(aSession->mCancelGuard);

		if (aSession->mCanceled)
		{
			OnRequestComplete(aSession);
			return;
		}
	}

	// This implementation will be changed in the future.
	const char delim = '\n';
	asio::async_read_until(aSession->mSocket, aSession->mResponseBuffer, delim,
		[this,aSession](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			if (aErrorCode.value() != 0)
			{
				aSession->mErrorCode = aErrorCode;
				OnRequestComplete(aSession);
				return;
			}

			OnReceived(aSession);
		}
	);
}

void TCPClient::OnReceived(SessionPtr aSession)
{
	std::istream responseStream(&aSession->mResponseBuffer);
	std::getline(responseStream, aSession->mResponse);
	
	OnRequestComplete(aSession);
}

void TCPClient::OnRequestComplete(SessionPtr aSession)
{
	// We do not care about error codes in case the connection was not made.
	asio::error_code ignoredErrorCode;
	aSession->mSocket.shutdown(asio::ip::tcp::socket::shutdown_both, ignoredErrorCode);

	// Remove the session from active sessions list.
	{
		std::unique_lock<std::mutex> activeSessionsLock(mActiveSessionsGuard);

		auto sessionIt = mActiveSessions.find(aSession->mRequest->GetId());
		if (sessionIt != mActiveSessions.end())
			mActiveSessions.erase(sessionIt);
	}

	asio::error_code errorCode;
	if (aSession->mErrorCode.value() == 0 && aSession->mCanceled)
		errorCode = asio::error::operation_aborted;
	else
		errorCode = aSession->mErrorCode;
	
	// Handle sent request.
	aSession->mHandler->Handle(aSession->mRequest, aSession->mResponse, aSession->mErrorCode);
}
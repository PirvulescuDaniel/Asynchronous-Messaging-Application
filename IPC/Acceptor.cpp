#include "pch.h"
#include "Acceptor.h"
#include "ServiceDispatcher.h"

void Acceptor::StartAccepting()
{
	mStopped.store(false);

	// Put the acceptor in "listen" mode and start accepting connection requests from queue.
	mAcceptor.listen();
	InitAccept();
}

void Acceptor::Stop()
{
	mStopped.store(true);
}

void Acceptor::InitAccept()
{
	auto communicationSocket = std::make_shared<asio::ip::tcp::socket>(mIoService);

	mAcceptor.async_accept(*communicationSocket.get(),
		[this, communicationSocket](const asio::error_code& aErrorCode)
		{
			OnAccept(aErrorCode, communicationSocket);
		}
	);
}

void Acceptor::OnAccept(const asio::error_code& aErrorCode, CommunicationSocket aCommunicationSocket)
{
	// Do not return when it fails to continue with the other connection requests.
	if (aErrorCode.value() != 0)
		std::cout << aErrorCode.message() << ": " << aErrorCode.value();
	else
	{
		// From this point aCommunicationSocket is valid. 
		auto dispatcher = std::make_shared<ServiceDispatcher>(aCommunicationSocket);
		dispatcher->StartDispatching();
	}

	if (!mStopped.load())
		InitAccept();
	else
		mAcceptor.close();
}
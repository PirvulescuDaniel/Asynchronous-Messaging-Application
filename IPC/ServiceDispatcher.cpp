#include "pch.h"
#include "ServiceDispatcher.h"
#include "IRequest.h"
#include "IService.h"
#include "ServiceRequestText.h"

ServiceDispatcher::ServiceDispatcher(SocketPtr aSocket)
	:mSocket(aSocket)
{
}

void ServiceDispatcher::StartDispatching()
{
	// TO BE MODIFIED

	asio::async_read_until(*mSocket.get(), mRequestBuffer, '\n',
		[this](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			OnRequestReceived(aErrorCode, aBytesTransferred);
		}
	);
}

void ServiceDispatcher::OnRequestReceived(const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
{
	if (aErrorCode.value() != 0)
	{
		std::cout << aErrorCode.message() << ": " << aErrorCode.value() << std::endl;
		return;
	}

	std::istream requestStream(&mRequestBuffer);
	std::string  rawRequest;

	// TO BE MODIFIED
	std::getline(requestStream, rawRequest, '\n');

	const auto requestType = static_cast<IRequest::RequestType>(rawRequest[0] - '0');
	const auto request = rawRequest.substr(1, std::string::npos);

	IService* service = nullptr;

	switch (requestType)
	{
		case IRequest::RequestType::MESSAGE_TEXT:
			service = new ServiceRequestText(mSocket, request);
			break;
	}

	if (service)
		service->Process();
}
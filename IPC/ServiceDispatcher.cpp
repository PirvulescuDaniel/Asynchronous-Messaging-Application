#include "pch.h"
#include "ServiceDispatcher.h"
#include "IRequest.h"
#include "IService.h"
#include "ServiceRequestText.h"

ServiceDispatcher::ServiceDispatcher(SocketPtr aSocket)
	:mSocket(aSocket)
{
}

void ServiceDispatcher::StartDispatching(UICallback aCallback)
{
	// TO BE MODIFIED

	asio::async_read_until(*mSocket.get(), mRequestBuffer, '\n',
		std::bind(&ServiceDispatcher::OnRequestReceived, shared_from_this(), std::placeholders::_1, std::placeholders::_2, aCallback));
}

void ServiceDispatcher::OnRequestReceived(const asio::error_code& aErrorCode, std::size_t aBytesTransferred, UICallback aCallback)
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
	const auto request     = rawRequest.substr(1, std::string::npos);

	const auto& senderIp  = mSocket->remote_endpoint().address().to_string();
	const auto& wSenderIp = std::wstring(senderIp.begin(), senderIp.end());
	const auto& wRequest  = std::wstring(request.begin(), request.end());

	aCallback(wSenderIp.c_str(), wRequest.c_str(), true);

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
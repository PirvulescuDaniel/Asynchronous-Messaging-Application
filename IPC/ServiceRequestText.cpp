#include "pch.h"
#include "ServiceRequestText.h"

ServiceRequestText::ServiceRequestText(SocketPtr aSocket, std::string_view aRequest)
	:mSocket(aSocket)
	,mRequest(aRequest)
{
}

void ServiceRequestText::Process()
{
	ProcessRequest();

	ProcessResponse();

	// Send the response.
	asio::async_write(*mSocket.get(), asio::buffer(mResponse),
		[this](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			OnResponseSent(aErrorCode, aBytesTransferred);
		}
	);
}

void ServiceRequestText::ProcessRequest()
{
	// TO BE MODIFIED
	std::cout << mRequest << std::endl;
}

void ServiceRequestText::ProcessResponse()
{
	mResponse = "Received\n";
}

void ServiceRequestText::OnResponseSent(const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
{
	if (aErrorCode.value() != 0)
		std::cout << aErrorCode.message() << ": " << aErrorCode.value() << std::endl;

	OnFinish();
}

void ServiceRequestText::OnFinish()
{
	delete this;
}
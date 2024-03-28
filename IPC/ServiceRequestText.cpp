#include "pch.h"
#include "ServiceRequestText.h"

ServiceRequestText::ServiceRequestText(SocketPtr aSocket)
	:mSocket(aSocket)
{
}

void ServiceRequestText::StartHandling()
{
	// TO BE MODIFIED

	const char delim = '\n';

	asio::async_read_until(*mSocket.get(), mRequestBuffer, delim,
		[this](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			OnRequestReceived(aErrorCode, aBytesTransferred);
		}
	);
}

void ServiceRequestText::OnRequestReceived(const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
{
	if (aErrorCode.value() != 0)
	{
		std::cout << aErrorCode.message() << ": " << aErrorCode.value() << std::endl;
		OnFinish();
		return;
	}

	ProcessRequest();

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
	std::istream requestStream(&mRequestBuffer);
	std::string  rawRequest;

	// TO BE MODIFIED
	std::getline(requestStream, rawRequest, '\n');
	std::cout << rawRequest << std::endl;

	mResponse = "Received!\n";
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
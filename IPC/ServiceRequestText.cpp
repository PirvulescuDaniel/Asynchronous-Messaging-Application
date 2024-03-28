#include "pch.h"
#include "ServiceRequestText.h"

ServiceRequestText::ServiceRequestText(SocketPtr aSocket)
	:mSocket(aSocket)
{
}

void ServiceRequestText::StartHandling()
{
	// TODO
}

void ServiceRequestText::OnRequestReceived()
{
	// TODO
}

void ServiceRequestText::ProcessRequest()
{
	// TODO
}

void ServiceRequestText::OnResponseSent(const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
{
	// TODO
}
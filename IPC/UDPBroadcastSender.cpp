#include "pch.h"
#include "UDPBroadcastSender.h"

unsigned short               UDPBroadcastSender::kBroadcastPort = 3333;
UDPBroadcastSender::Endpoint UDPBroadcastSender::kBroadcastEndpoint(asio::ip::address_v4::broadcast(), kBroadcastPort);

UDPBroadcastSender::UDPBroadcastSender(ServicePtr aService)
	:mSocket(*aService.get())
{
	mSocket.open(asio::ip::udp::v4());

	mSocket.set_option(asio::socket_base::reuse_address(true));
	mSocket.set_option(asio::socket_base::broadcast(true));
}

void UDPBroadcastSender::Broadcast(const std::string& aMessage)
{
	mSocket.async_send_to(asio::buffer(aMessage), kBroadcastEndpoint,
		[](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			// We don't care if the message was sent or not.
		}
	);
}
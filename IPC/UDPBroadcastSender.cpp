#include "pch.h"
#include "UDPBroadcastSender.h"

UDPBroadcastSender::UDPBroadcastSender(asio::io_service& aService, std::string_view aIp, unsigned short aPort)
	:mService(aService)
	,mSocket(mService)
	,mBroadcastEndpoint(asio::ip::address::from_string(aIp.data()),aPort)
{
	mSocket.open(asio::ip::udp::v4());

	mSocket.set_option(asio::socket_base::reuse_address(true));
	mSocket.set_option(asio::socket_base::broadcast(true));
}

void UDPBroadcastSender::BroadcastAsync(const std::string& aMessage)
{
	mSocket.async_send_to(asio::buffer(aMessage), mBroadcastEndpoint,
		[](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			// We don't care if the message was sent or not.
		}
	);
}

void UDPBroadcastSender::BroadcastSync(const std::string& aMessage)
{
	mSocket.send_to(asio::buffer(aMessage), mBroadcastEndpoint);
}
#include "pch.h"
#include "UDPBroadcastListener.h"

UDPBroadcastListener::UDPBroadcastListener(asio::io_service& aService, unsigned short aPort)
	:mService(aService)
	,mSocket(mService)
	,mPort(aPort)
{
	mSocket.open(asio::ip::udp::v4());

	mSocket.set_option(asio::socket_base::reuse_address(true));
	mSocket.set_option(asio::socket_base::broadcast(true));

	mSocket.bind(asio::ip::udp::endpoint(asio::ip::address_v4::any(), aPort));
}

void UDPBroadcastListener::StartListening()
{
	// TODO
}

void UDPBroadcastListener::HandleReceive()
{
	// TODO
}
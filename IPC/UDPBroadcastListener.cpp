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
	auto buffer         = std::make_shared<std::string>(32, '0');
	auto senderEndpoint = std::make_shared<asio::ip::udp::endpoint>();

	mSocket.async_receive_from(
		asio::buffer(*buffer), *senderEndpoint,
		std::bind(&UDPBroadcastListener::HandleReceive, this, buffer, senderEndpoint)
	);
}

void UDPBroadcastListener::HandleReceive(BufferPtr aBuffer, EndpointPtr aSenderEndpoint)
{
	// Start to listen the next datagram.
	StartListening();

	std::cout << "Message sent from " << aSenderEndpoint->address() << ": " << *aBuffer << std::endl;
}
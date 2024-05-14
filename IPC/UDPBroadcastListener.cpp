#include "pch.h"
#include "UDPBroadcastListener.h"
#include "Utility.h"

namespace
{
	constexpr const unsigned int kDatagramLength = 8;
}

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

void UDPBroadcastListener::StartListening(Callback aCallback)
{
	mStopped = false;

	auto buffer         = std::make_shared<std::string>(kDatagramLength, '0');
	auto senderEndpoint = std::make_shared<asio::ip::udp::endpoint>();

	mSocket.async_receive_from(
		asio::buffer(*buffer), *senderEndpoint,
		std::bind(&UDPBroadcastListener::HandleReceive, this, buffer, senderEndpoint, aCallback)
	);
}

void UDPBroadcastListener::StopListening()
{
	mStopped = true;
}

void UDPBroadcastListener::HandleReceive(BufferPtr aBuffer, EndpointPtr aSenderEndpoint, Callback aCallback)
{
	// Start to listen the next datagram.
	if(!mStopped)
		StartListening(aCallback);

	// Do not handle our own broadcast messages.
	const auto & arpInterfaces = Utility::GetARPInterfaces();

	const auto& found = std::any_of(arpInterfaces.begin(), arpInterfaces.end(),
		[&aSenderEndpoint](const std::string& aIp)
		{
			return aIp == aSenderEndpoint->address().to_string();
		}
	);

	if (found)
		return;

	aCallback(aSenderEndpoint->address().to_string(), *aBuffer);
}
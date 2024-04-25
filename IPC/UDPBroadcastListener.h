#pragma once
#include "pch.h"

class UDPBroadcastListener
{
public:

	using Socket            = asio::ip::udp::socket;
	using BufferPtr         = std::shared_ptr<std::string>;
	using EndpointPtr       = std::shared_ptr<asio::ip::udp::endpoint>;

	UDPBroadcastListener(asio::io_service& aService, unsigned short aPort);

	/*
		Start the async listening process.
	*/
	void StartListening();

	/*
		Stop the listening process.
	*/
	void StopListening();

private:

	/*
		Handle the received datagram.
	*/
	void HandleReceive(BufferPtr aBuffer, EndpointPtr aSenderEndpoint);

	asio::io_service& mService;
	Socket            mSocket;
	unsigned short    mPort;

	std::atomic_bool mStopped{ true };
};
#pragma once
#include "pch.h"

class UDPBroadcastListener
{
public:

	using Socket = asio::ip::udp::socket;

	UDPBroadcastListener(asio::io_service& aService, unsigned short aPort);

	void StartListening();

private:

	void HandleReceive();

	asio::io_service& mService;
	Socket            mSocket;
	unsigned short    mPort;
};
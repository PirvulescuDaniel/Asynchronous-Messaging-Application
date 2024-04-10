#pragma once
#include "pch.h"

class UDPBroadcastSender
{
public:

	using Socket     = asio::ip::udp::socket;
	using Endpoint   = asio::ip::udp::endpoint;

	UDPBroadcastSender() = default;
	UDPBroadcastSender(asio::io_service& aService, std::string_view aIp, unsigned short aPort);

	void BroadcastAsync(const std::string& aMessage);

	void BroadcastSync(const std::string& aMessage);
	
private:
	asio::io_service& mService;
	Socket	          mSocket;
	Endpoint          mBroadcastEndpoint;
};
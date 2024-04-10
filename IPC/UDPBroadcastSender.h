#pragma once
#include "pch.h"

class UDPBroadcastSender
{
public:

	using Socket     = asio::ip::udp::socket;
	using Endpoint   = asio::ip::udp::endpoint;
	using ServicePtr = std::shared_ptr<asio::io_service>;

	UDPBroadcastSender(ServicePtr aService, Endpoint aBroadcastEndpoint);

	void BroadcastAsync(const std::string& aMessage);

	void BroadcastSync(const std::string& aMessage);
	
private:
	ServicePtr mService;
	Socket     mSocket;
	Endpoint   mBroadcastEndpoint;
};
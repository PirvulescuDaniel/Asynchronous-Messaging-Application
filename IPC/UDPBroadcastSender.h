#pragma once
#include "pch.h"

class UDPBroadcastSender
{
public:

	using Socket     = asio::ip::udp::socket;
	using Endpoint   = asio::ip::udp::endpoint;
	using ServicePtr = std::shared_ptr<asio::io_service>;

	UDPBroadcastSender(ServicePtr aService);

	void Broadcast(const std::string& aMessage);

	static unsigned short kBroadcastPort;
	static Endpoint kBroadcastEndpoint;
	
private:
	Socket mSocket;
};
#pragma once
#include "pch.h"

class UDPBroadcastSender;

class DiscoveryManager
{
public:

	using WorkerPtr      = std::unique_ptr<asio::io_service::work>;
	using BroadcasterPtr = std::unique_ptr<UDPBroadcastSender>;
	using Endpoint       = asio::ip::udp::endpoint;

	DiscoveryManager(std::string_view aBroadcastIP, unsigned short aPort);

	/*
		It broadcasts only once, asynchronously.
	*/
	void Broadcast();

	void StartRecurrentBroadcasting();

	void StopRecurrentBroadcasting();

private:
	asio::io_service   mIoService;
	WorkerPtr          mWorker;

	BroadcasterPtr mBroadcaster;

	std::string mMessageHello {"Hello"};
	std::string mMessageBye		{"Bye"};
};
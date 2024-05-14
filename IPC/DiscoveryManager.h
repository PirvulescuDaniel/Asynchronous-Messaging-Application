#pragma once
#include "pch.h"

class UDPBroadcastSender;
class UDPBroadcastListener;

class DiscoveryManager
{
public:

	using WorkerPtr      = std::unique_ptr<asio::io_service::work>;
	using ThreadWorker   = std::unique_ptr<std::thread>;
	using SenderPtr      = std::unique_ptr<UDPBroadcastSender>;
	using ListenerPtr    = std::unique_ptr<UDPBroadcastListener>;
	using Endpoint       = asio::ip::udp::endpoint;
	using BroadcastDelay = std::chrono::seconds;
	using Callback       = std::function<void(std::string, std::string)>;

	DiscoveryManager(std::string_view aBroadcastIP, unsigned short aPort);

	~DiscoveryManager();

	/*
		It broadcasts only once, asynchronously.
	*/
	void Broadcast(const std::string& aMessage);

	/*
		Start the broadcasting process at an interval of aDelay seconds.
	*/
	void StartRecurrentBroadcasting(BroadcastDelay aDelay);

	/*
		Stops the current recurrent broadcasting process.
	*/
	void StopRecurrentBroadcasting();

	/*
		Start the listening process.
	*/
	void StartListening(Callback aCallback);

	/*
		Stop the listening process.
	*/
	void StopListening();

private:

	asio::io_service mIoService;
	WorkerPtr        mWorker;
	ThreadWorker     mThreadWorker;

	SenderPtr   mBroadcastSender;
	ListenerPtr mBroadcastListener;

	std::string mMessageHello {"Hello"};
	std::string mMessageBye   {"Bye"};
};
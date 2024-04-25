#pragma once
#include "pch.h"

class UDPBroadcastSender;

class DiscoveryManager
{
public:

	using WorkerPtr      = std::unique_ptr<asio::io_service::work>;
	using ThreadWorker   = std::unique_ptr<std::thread>;
	using BroadcasterPtr = std::unique_ptr<UDPBroadcastSender>;
	using Endpoint       = asio::ip::udp::endpoint;
	using BroadcastDelay = std::chrono::seconds;
	using TimerPtr       = std::unique_ptr<asio::steady_timer>;

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

private:

	/*
		Handle the expiration of the timer.
		If there are errors, we stop the process. otherwise we do another broadcast.
	*/
	void HandleTimeExpired(const asio::error_code& aErrorCode, BroadcastDelay aDelay);

	asio::io_service   mIoService;
	WorkerPtr          mWorker;
	ThreadWorker       mThreadWorker;

	BroadcasterPtr   mBroadcaster;
	std::atomic_bool mBroadcastStoped {true};

	std::string mMessageHello {"Hello"};
	std::string mMessageBye   {"Bye"};

	TimerPtr mTimer;
};
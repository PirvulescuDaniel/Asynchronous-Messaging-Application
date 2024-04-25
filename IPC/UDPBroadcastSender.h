#pragma once
#include "pch.h"

class UDPBroadcastSender
{
public:

	using Socket         = asio::ip::udp::socket;
	using Endpoint       = asio::ip::udp::endpoint;
	using BroadcastDelay = std::chrono::seconds;
	using TimerPtr       = std::unique_ptr<asio::steady_timer>;

	UDPBroadcastSender() = default;
	UDPBroadcastSender(asio::io_service& aService, std::string_view aIp, unsigned short aPort);

	void BroadcastAsync(const std::string& aMessage);

	void BroadcastSync(const std::string& aMessage);

	/*
		Start the broadcasting process at an interval of aDelay seconds.
	*/
	void StartBroadcasting(const std::string& aMessage, BroadcastDelay aDelay);

	/*
		Stops the current recurrent broadcasting process.
	*/
	void StopBroadcasting();
	
private:

	/*
		Handle the expiration of the timer.
		If there are errors, we stop the process. otherwise we do another broadcast.
	*/
	void HandleTimeExpired(const asio::error_code& aErrorCode, BroadcastDelay aDelay, const std::string& aMessage);

	asio::io_service& mService;
	Socket	          mSocket;
	Endpoint          mBroadcastEndpoint;

	std::atomic_bool mStopped{ true };

	TimerPtr mTimer;
};
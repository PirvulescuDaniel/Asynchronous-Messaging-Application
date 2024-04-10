#pragma once
#include "pch.h"

class UDPBroadcastSender;

class DiscoveryManager
{
public:

	using WorkerPtr      = std::unique_ptr<asio::io_service::work>;
	using BroadcasterPtr = std::unique_ptr<UDPBroadcastSender>;

	DiscoveryManager();

	void Broadcast();

	void StartRecurrentBroadcasting();

	void StopRecurrentBroadcasting();

private:
	asio::io_service mIoService;
	WorkerPtr        mWorker;

	BroadcasterPtr mBroadcaster;
};
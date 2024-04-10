#include "pch.h"
#include "DiscoveryManager.h"
#include "UDPBroadcastSender.h"

DiscoveryManager::DiscoveryManager()
{
	mBroadcaster.reset(nullptr);
	mWorker.reset(new asio::io_service::work(mIoService));
}

void DiscoveryManager::Broadcast()
{
	// TODO
}

void DiscoveryManager::StartRecurrentBroadcasting()
{
	// TODO
}

void DiscoveryManager::StopRecurrentBroadcasting()
{
	// TODO
}
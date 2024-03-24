#include "pch.h"
#include "TCPServer.h"

TCPServer::TCPServer()
{
	// Force the "run()" method from service not to exit when it has no more events to process.
	mWork.reset(new asio::io_service::work(mIoService));
}

void TCPServer::Start(unsigned short aPort, unsigned int aThreadPoolSize)
{
	assert(aThreadPoolSize > 0);

	// Start accepting connection requests from clients.
	//TODO

	// Create several event processors.
	for (int i = 0; i < aThreadPoolSize; i++)
	{
		ThreadPoolPtr threadPool(new std::thread(
			[this]()
			{
				mIoService.run();
			}
		));

		mThreadPools.push_back(std::move(threadPool));
	}
}

void TCPServer::Stop()
{
	// Let the "run()" method to exit.
	mWork.reset(nullptr);

	// Wait for the event processors to finish what is left.
	for (auto& threadPool : mThreadPools)
	{
		if (threadPool && threadPool->joinable())
			threadPool->join();
	}
}
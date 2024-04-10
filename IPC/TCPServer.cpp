#include "pch.h"
#include "TCPServer.h"
#include "Acceptor.h"

TCPServer::TCPServer()
{
	// Force the "run()" method from service not to exit when it has no more events to process.
	mWork.reset(new asio::io_service::work(mIoService));
}

void TCPServer::Start(unsigned short aPort, unsigned int aThreadPoolSize)
{
	assert(aThreadPoolSize > 0);

	// Start accepting connection requests from clients.
	mAcceptor.reset(new Acceptor(mIoService, aPort));
	mAcceptor->StartAccepting();

	// Create several event processors.
	for (unsigned int i = 0; i < aThreadPoolSize; i++)
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
	mAcceptor->Stop();

	mIoService.stop();

	// Wait for the event processors to finish what is left.
	for (auto& threadPool : mThreadPools)
	{
		if (threadPool && threadPool->joinable())
			threadPool->join();
	}
}
#include "pch.h"
#include "TCPClient.h"

TCPClient::TCPClient()
{
	// Force the "run()" method from service not to exit when it has no more events to process.
	mWork.reset(new asio::io_service::work(mIoService));

	mServiceThreadPool.reset(new std::thread(
		[this]()
		{
			mIoService.run();
		}
	));
}

void TCPClient::SendRequest()
{
	//TODO
}

void TCPClient::ReceiveResponse()
{
	//TODO
}

void TCPClient::CancelRequest()
{
	//TODO
}

void TCPClient::Close()
{
	// Let the "run()" method to exit.
	mWork.reset(nullptr);

	if (mServiceThreadPool && mServiceThreadPool->joinable())
		mServiceThreadPool->join();
}

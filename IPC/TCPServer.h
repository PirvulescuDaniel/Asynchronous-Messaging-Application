#pragma once
#include "pch.h"
#include "IServer.h"

class Acceptor;

class TCPServer : public IServer
{
public:

	using ThreadPoolPtr   = std::unique_ptr<std::thread>;
	using ThreadPoolsList = std::vector<ThreadPoolPtr>;

	TCPServer();

	/*
		Starts the server.
	*/
	void Start(unsigned short aPort, unsigned int aThreadPoolSize) override;

	/*
		Stop the server. Blocks the thread that calls it!
	*/
	void Stop() override;

private:
	asio::io_service                        mIoService;
	std::unique_ptr<Acceptor>               mAcceptor;
	std::unique_ptr<asio::io_service::work> mWork;
	ThreadPoolsList                         mThreadPools;
};
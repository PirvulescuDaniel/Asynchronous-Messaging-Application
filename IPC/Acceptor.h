#pragma once
#include "pch.h"

class Acceptor
{
public:

	using CommunicationSocket = std::shared_ptr<asio::ip::tcp::socket>;

	Acceptor(asio::io_service& aIoService, unsigned short aPort)
		:mIoService(aIoService)
		,mAcceptor(mIoService, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), aPort))
	{
	}

	/*
		Non-blocking method that starts the process of accepting connection requests from clients.
	*/
	void StartAccepting();

	/*
		Stops the accepting process.
	*/
	void Stop();

private:

	/*
		Waits for connection requests from clients.
	*/
	void InitAccept();

	/*
		It is called after a connection request has been accepted.
	*/
	void OnAccept(const asio::error_code& aErrorCode, CommunicationSocket aCommunicationSocket);

	asio::io_service&       mIoService;
	asio::ip::tcp::acceptor mAcceptor;
	std::atomic_bool        mStopped{ true };
};
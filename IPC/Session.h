#pragma once
#include "pch.h"

class IRequestHandler;
class IRequest;

/*
	Class that defines a request session.
*/
class Session
{
public:

  using RequestPtr = std::shared_ptr<IRequest>;

  Session(asio::io_service& aIoService,
          std::string_view  aServerIp,	
          unsigned short    aServerPort,
          RequestPtr        aRequest,
          IRequestHandler*  aHandler)
    : mSocket(aIoService)
    , mServerEndpoint(asio::ip::address::from_string(aServerIp.data()), aServerPort)
    , mRequest(aRequest)
    , mHandler(aHandler)
	{
	}

	asio::ip::tcp::socket   mSocket;
	asio::ip::tcp::endpoint mServerEndpoint;

	RequestPtr mRequest;

	std::string     mResponse;
	asio::streambuf mResponseBuffer;

	std::mutex mCancelGuard;
	bool       mCanceled{ false };

	IRequestHandler* mHandler;

	asio::error_code mErrorCode;
};
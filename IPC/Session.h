#pragma once
#include "pch.h"

class IRequestCallback;

/*
	A structure that defines a request session.
*/
struct Session
{
  Session(asio::io_service& aIoService,
          std::string_view  aServerIp,	
          unsigned short    aServerPort,
          std::string_view  aRequest,
          unsigned int      aRequestId,
          IRequestCallback* aCallback)
    : mSocket(aIoService)
    , mServerEndpoint(asio::ip::address::from_string(aServerIp.data()), aServerPort)
    , mRequest(aRequest)
    , mRequestId(aRequestId)
    , mCallback(aCallback)
	{
	}

	asio::ip::tcp::socket   mSocket;
	asio::ip::tcp::endpoint mServerEndpoint;

	std::string  mRequest;
	unsigned int mRequestId;

	std::string     mResponse;
	asio::streambuf mResponseBuffer;

	std::mutex mCancelGuard;
	bool       mCanceled{ false };

	IRequestCallback* mCallback;

	asio::error_code mErrorCode;
};
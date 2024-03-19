#pragma once

class IRequest;

class IClient
{
public:

	virtual ~IClient() = default;

	virtual void SendRequest(IRequest* aRequest, std::string_view aServerIp, unsigned short aServerPort) = 0;

	virtual void CancelRequest() = 0;

	virtual void Close() = 0;
};
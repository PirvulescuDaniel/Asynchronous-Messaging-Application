#pragma once

class IRequest;

class IClient
{
public:
	using RequestPtr = std::shared_ptr<IRequest>;

	virtual ~IClient() = default;

	virtual void SendRequest(RequestPtr aRequest, std::string_view aServerIp, unsigned short aServerPort) = 0;

	virtual void CancelRequest(unsigned int aRequestId) = 0;

	virtual void Close() = 0;
};
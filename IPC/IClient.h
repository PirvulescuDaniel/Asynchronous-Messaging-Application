#pragma once

class IClient
{
public:

	virtual ~IClient() = default;

	virtual void SendRequest() = 0;

	virtual void ReceiveResponse() = 0;

	virtual void CancelRequest() = 0;

	virtual void Close() = 0;
};
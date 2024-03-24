#pragma once

class IServer
{
public:
	virtual ~IServer() = default;

	virtual void Start(unsigned short aPort, unsigned int aThreadPoolSize) = 0;

	virtual void Stop() = 0;
};
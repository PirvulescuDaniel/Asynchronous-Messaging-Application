#pragma once

class IServer
{
public:
    using UICallback = std::function<void(const wchar_t *, const wchar_t *, bool)>;

	virtual ~IServer() = default;

	virtual void Start(unsigned short aPort, unsigned int aThreadPoolSize, UICallback aCallback) = 0;

	virtual void Stop() = 0;
};
#pragma once
#include "IClient.h"

class Session;

class TCPClient : public IClient
{
public:

	using SessionPtr  = std::shared_ptr<Session>;
	using SessionsMap = std::unordered_map<unsigned int, SessionPtr>;

	TCPClient();

	void SendRequest() override;

	void ReceiveResponse() override;

	void CancelRequest() override;

	void Close() override;

private:
	asio::io_service mIoService;

	SessionsMap mActiveSessions;
	std::mutex  mSessionsMapGuard;	

	std::unique_ptr<asio::io_service::work> mWork;
	std::unique_ptr<std::thread>            mServiceThreadPool;

};
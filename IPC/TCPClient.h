#pragma once
#include "IClient.h"

struct Session;
class  IRequest;

class TCPClient : public IClient
{
public:

	using RequestPtr  = std::shared_ptr<IRequest>;
	using SessionPtr  = std::shared_ptr<Session>;
	using SessionsMap = std::unordered_map<unsigned int, SessionPtr>;

	TCPClient();

	void SendRequest(RequestPtr aRequest, std::string_view aServerIp, unsigned short aServerPort) override;

	void CancelRequest() override;

	void Close() override;

private:

	/*
		It is called after we successfully connected and there were no errors.
	*/
	void OnConnect(SessionPtr aSession);

	/*
		It is called after the request was sent successfully and there were no errors.
	*/
	void OnSent(SessionPtr aSession);

	/*
		It is called after receiving the response from the server.
	*/
	void OnReceived(SessionPtr aSession);

	/*
		It is called after the entire cycle of sending a request has ended successfully,
		or errors have occurred along the way, or the request operation has been canceled.
	*/
	void OnRequestComplete(SessionPtr aSession);

	asio::io_service mIoService;

	SessionsMap mActiveSessions;
	std::mutex  mActiveSessionsGuard;	

	std::unique_ptr<asio::io_service::work> mWork;
	std::unique_ptr<std::thread>            mServiceThreadPool;
};
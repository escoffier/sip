#pragma once
#include "eXosip2/eXosip.h"
#include <string>
#include "MessageFactory.h"

class MessageQueue;
class OsipSender;

class SIPUserServer
{
public:
	SIPUserServer();
	~SIPUserServer();

	bool Initialize(const std::string &Name, const std::string& Ip, int port, const std::string Id, int expires);
	void Dispatch(MessageQueue & msgqueue);
	//void SendSIPMessage(AbstractMessage &msg);
private:
	void GetRegisterInfomation(std::string & info);
private:
	struct eXosip_t* sipContext_;
	eXosip_event_t *event_;
	MessageFactory *msgFactory_;
	AbstractSender *sender_;
};



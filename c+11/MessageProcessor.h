#pragma once
/*
业务层处理接口，与sip协议层完全隔离
*/
#include"InviteMessage.h"
#include "RegisterMessage.h"
#include "AbstractMessageProcessor.h"
class AbstractSender;
class MessageProcessor :public AbstractMessageProcessor
{
public:
	MessageProcessor();
	MessageProcessor(AbstractSender *sender);
	~MessageProcessor();
	virtual void OnInviteMessage(const InviteMessage & msg);
	virtual void OnRegisterMessage(const RegisterMessage & msg);

private:
	AbstractSender *sender_;
};
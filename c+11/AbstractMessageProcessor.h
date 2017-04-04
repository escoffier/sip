#pragma once
class InviteMessage;

class AbstractMessageProcessor
{
public:
	AbstractMessageProcessor() {};
	~AbstractMessageProcessor() {};

	virtual void OnInviteMessage(const InviteMessage & msg) = 0;
private:

};
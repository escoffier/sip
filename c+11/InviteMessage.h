#pragma once
#include"abstractmessage.h"

class InviteMessage : public AbstractMessage
{
public:
	InviteMessage();
	InviteMessage(MessageProcessor  *msgProcessor);
	InviteMessage(std::function<void()> &f);
	~InviteMessage();

	virtual void Process();
	virtual bool ParseFromSIP(const std::vector< TiXmlNode* > &nodes);
private:

};
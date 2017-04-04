#pragma once
#include"abstractmessage.h"

class RegisterMessage : public AbstractMessage
{
public:
	RegisterMessage();
	RegisterMessage(MessageProcessor  *msgProcessor);
	RegisterMessage(std::function<void()> &f);
	~RegisterMessage();

	virtual void Process();
	virtual bool ParseFromSIP(const std::vector< TiXmlNode* > &nodes);

	int GetTid() const { return tid_; }
	const std::string &GetUser() { return user_; }
	int GetExpires() const { return expires_; }
private:
	int tid_;
	std::string user_;
	int expires_;
};
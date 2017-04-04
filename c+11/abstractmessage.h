#pragma once
#include<functional>
#include<vector>
#include "tinystr.h"
#include "tinyxml.h"

class MessageProcessor;

class AbstractMessage
{
public:
	AbstractMessage();
	AbstractMessage(MessageProcessor  *msgProcessor);
	AbstractMessage(std::function<void()> &f);
	~AbstractMessage();
	std::function<void()> processFunc;
	virtual void Process() = 0;
	virtual bool ParseFromSIP(const std::vector< TiXmlNode* > &nodes) =0;
protected:

	MessageProcessor  *msgProcessor;
};

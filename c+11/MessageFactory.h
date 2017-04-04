#pragma once

class AbstractMessage;
class MessageProcessor;
class MessageProcessor;
class AbstractSender;

class MessageFactory
{
public:
	MessageFactory();
	MessageFactory(AbstractSender *sender);
	~MessageFactory();

	AbstractMessage * CreateInviteMessage();
	AbstractMessage * CreateRegisterMessage();
private:
	MessageProcessor  *msgProcessor;
};
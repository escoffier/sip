#include "MessageFactory.h"
#include "MessageProcessor.h"

MessageFactory::MessageFactory()
{
	msgProcessor = new MessageProcessor;
}

MessageFactory::~MessageFactory()
{
}

AbstractMessage * MessageFactory::CreateInviteMessage()
{
	return new InviteMessage(msgProcessor);
}

MessageFactory::MessageFactory(AbstractSender *sender)
{
	msgProcessor = new MessageProcessor(sender);
}

AbstractMessage * MessageFactory::CreateRegisterMessage()
{
	RegisterMessage * msg = new RegisterMessage(msgProcessor);

	return msg;
}

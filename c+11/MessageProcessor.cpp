#include "MessageProcessor.h"
#include<iostream>
//#include "eXosip2\eXosip.h"
#include "AbstractSender.h"
#include "Sender.h"
#include<cassert>
//void AbstractMessageProcessor::OnInviteMessage(const InviteMessage & msg)
//{
//}
//AbstractMessageProcessor::AbstractMessageProcessor()
//{
//}
//
//AbstractMessageProcessor::~AbstractMessageProcessor()
//{
//}

MessageProcessor::MessageProcessor()
{
}

MessageProcessor::~MessageProcessor()
{
}


void MessageProcessor::OnInviteMessage(const InviteMessage & msg)
{
	std::cout << "OnInviteMessage\n ";
}

MessageProcessor::MessageProcessor(AbstractSender * sender) :sender_(sender)
{
}

void MessageProcessor::OnRegisterMessage(const RegisterMessage & msg)
{
	std::cout << "OnRegisterMessage\n ";
	assert(sender_);
	sender_->SendRegisterAck(msg);
}

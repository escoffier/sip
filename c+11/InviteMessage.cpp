#include"InviteMessage.h"
#include "MessageProcessor.h"

InviteMessage::InviteMessage()
{
}

InviteMessage::InviteMessage(MessageProcessor * msgProc) :AbstractMessage(msgProc)
{
	processFunc = std::bind(&MessageProcessor::OnInviteMessage, msgProcessor, std::cref(*this));
}

InviteMessage::InviteMessage(std::function<void()> &f) : AbstractMessage(f)
{
}

InviteMessage::~InviteMessage()
{
}

void InviteMessage::Process()
{
	msgProcessor->OnInviteMessage(*this);
}

bool InviteMessage::ParseFromSIP(const std::vector<TiXmlNode*>& nodes)
{
	return false;
}

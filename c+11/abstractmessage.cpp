#include"abstractmessage.h"

AbstractMessage::AbstractMessage()
{
}

AbstractMessage::AbstractMessage(MessageProcessor * msgProc) :msgProcessor(msgProc)
{
}

AbstractMessage::AbstractMessage(std::function<void()> &f)
{
}

AbstractMessage::~AbstractMessage()
{
}
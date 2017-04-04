#include "MessageQueue.h"
#include "abstractmessage.h"

void MessageQueue::Push(std::shared_ptr<AbstractMessage> msg)
{
	std::lock_guard<std::mutex> lk(mutex_);
	queue_.push(msg);
	condition_.notify_all();
}

std::shared_ptr<AbstractMessage> MessageQueue::Pop()
{
	std::unique_lock<std::mutex> lk(mutex_);
	condition_.wait(lk, [&]() {return !queue_.empty(); });
	auto msg = queue_.front();
	queue_.pop();
	return msg;
}

MessageQueue::MessageQueue()
{
}

MessageQueue::~MessageQueue()
{
}
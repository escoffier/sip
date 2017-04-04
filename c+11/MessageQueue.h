#pragma once
#include <mutex>
#include<condition_variable>
#include<queue>
#include<memory>
#include "abstractmessage.h"

//class AbstractMessage;

class MessageQueue
{
public:
	MessageQueue();
	~MessageQueue();

	void Push(std::shared_ptr<AbstractMessage> msg);
	std::shared_ptr<AbstractMessage> Pop();

private:
	std::mutex mutex_;
	std::condition_variable condition_;
	std::queue<std::shared_ptr<AbstractMessage>> queue_;
};


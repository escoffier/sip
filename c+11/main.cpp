// c+11.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <future>
#include<cmath>
#include<iostream>
#include<functional>
#include "MessageFactory.h"
#include "abstractmessage.h"
#include"SIPUserServer.h"
#include"MessageQueue.h"
#if 0
class MessageProcessor;

class AbstractMessage
{
public:
	AbstractMessage();
	AbstractMessage( MessageProcessor  *msgProcessor);
	AbstractMessage(std::function<void()> &f);
   ~AbstractMessage();
   std::function<void()> processFunc;
protected:
	
	MessageProcessor  *msgProcessor;
};
class InviteMessage : public AbstractMessage
{
public:
	InviteMessage();
	InviteMessage( MessageProcessor  *msgProcessor);
	InviteMessage(std::function<void()> &f);
	~InviteMessage();

private:

};
class MessageProcessor
{
public:
	MessageProcessor();
	~MessageProcessor();
	void OnInviteMessage(const InviteMessage & msg);

private:

};


AbstractMessage::AbstractMessage()
{
}

AbstractMessage::AbstractMessage( MessageProcessor * msgProc):msgProcessor(msgProc)
{
}

AbstractMessage::AbstractMessage(std::function<void()> &f)
{
}

AbstractMessage::~AbstractMessage()
{
}




MessageProcessor::MessageProcessor()
{
}

MessageProcessor::~MessageProcessor()
{
}

InviteMessage::InviteMessage()
{
}

InviteMessage::InviteMessage(  MessageProcessor * msgProc):AbstractMessage(msgProc)
{
	processFunc = std::bind( &MessageProcessor::OnInviteMessage, msgProcessor, std::cref(*this) );
}

InviteMessage::InviteMessage(std::function<void()> &f):AbstractMessage(f)
{
}

InviteMessage::~InviteMessage()
{
}





void MessageProcessor::OnInviteMessage(const InviteMessage & msg)
{
	std::cout << "OnInviteMessage\n ";
}


class MessageFactory
{
public:
	MessageFactory();
	~MessageFactory();

	AbstractMessage * CreateInviteMessage();
private:
	MessageProcessor  *msgProcessor;
};

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
#endif


void lamdaTask()
{
	std::packaged_task<double(int, int)> task([](int a, int b) {return std::pow(a, b); });
	std::future<double> result = task.get_future();

	task(2, 5);
	std::cout << "lamdaTask: "<<result.get() << std::endl;
}

void processMessage(MessageQueue &msgqueue)
{
	while (true)
	{
		//std::cout << "Processing Message\n";
		auto msg = msgqueue.Pop();
		msg->Process();
	}
}
int main()
{
	SIPUserServer sipUserServer;
	sipUserServer.Initialize("Datang", "192.168.0.112", 5060, "15010000002000000001", 60);
	MessageQueue msgQueue;

	std::thread dispatchthread(&SIPUserServer::Dispatch, &sipUserServer, std::ref(msgQueue));
	std::thread processthread(&processMessage, std::ref(msgQueue));
	dispatchthread.join();
	processthread.join();
	//MessageFactory msgFactory;

	//AbstractMessage *msg = msgFactory.CreateInviteMessage();
	//msg->Process();
	//lamdaTask();
    return 0;
}


#include"RegisterMessage.h"
#include "MessageProcessor.h"
#include <iostream>
#include<string>

RegisterMessage::RegisterMessage()
{
}

RegisterMessage::RegisterMessage(MessageProcessor * msgProc) :AbstractMessage(msgProc)
{
}

RegisterMessage::RegisterMessage(std::function<void()>& f)
{
}

RegisterMessage::~RegisterMessage()
{
}

void RegisterMessage::Process()
{
	msgProcessor->OnRegisterMessage(*this);
}

bool RegisterMessage::ParseFromSIP(const std::vector<TiXmlNode*>& nodes)
{
	size_t size = nodes.size();
	for (size_t i = 0; i < size; ++i)
	{
		TiXmlNode *pNode = nodes[i];
		if (pNode == NULL)
		{
			//DEBUG_LOG( "参数错误" );
			std::cout << "参数错误\n";
			continue;
		}

		//const char *type = pNode->Value();
		std::string type(pNode->Value());
		if (type.empty())
		{
			std::cout << "参数名字为空\n";
			continue;
		}

		if (type == "USER")
		{
			TiXmlNode *pChild = pNode->FirstChild();
			if (pChild == NULL)
			{
				continue;
			}

			const char* user = pChild->Value();
			if (user == NULL)
			{
				std::cout << "参数值为空\n";
				continue;
			}
			user_ = user;
			std::cout << "user :" << user << "\n";
		}
		else if(type == "EXPIRES")
		{
			TiXmlNode *pChild = pNode->FirstChild();
			if (pChild == NULL)
			{
				continue;
			}

			const char* user = pChild->Value();
			if (user == NULL)
			{
				std::cout << "参数值为空\n";
				continue;
			}
			expires_ = atoi(user);
			std::cout << "expires :" << expires_ << "\n";
		}
		else if(type == "TID")
		{
			TiXmlNode *pChild = pNode->FirstChild();
			if (pChild == NULL)
			{
				continue;
			}

			const char* tid = pChild->Value();
			if (tid == NULL)
			{
				std::cout << "参数值为空\n";
				continue;
			}
			tid_ = atoi(tid);
			std::cout << "tid :" << tid_ << "\n";
		}
		else
		{
			std::cout << "type :" << type << "\n";
			continue;
		}


	}
	return false;
}

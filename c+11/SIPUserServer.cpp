#include "SIPUserServer.h"
#include "eXosip2/eXosip.h"
#include "eXosip2/eX_setup.h"
#include "eXosip2/eX_message.h"
#include "osip2/osip_mt.h"
#include <winsock2.h>
#include<iostream>
#include <chrono>
#include <sstream>
#include"MessageQueue.h"
#include "MessageFactory.h"
#include "Sender.h"
SIPUserServer::SIPUserServer() : sipContext_(nullptr), event_(nullptr),msgFactory_(nullptr),sender_(nullptr)
{

}

SIPUserServer::~SIPUserServer()
{
	eXosip_quit(sipContext_);
}

bool SIPUserServer::Initialize(const std::string & name, const std::string & Ip, int port, const std::string Id, int expires)
{

	sipContext_ = eXosip_malloc();
	if (NULL == sipContext_)
	{
		//ERROR_LOG("m_Exosip_Context is NULL!");
		return false;
	}
	int ret = eXosip_init(sipContext_);
	if (ret != OSIP_SUCCESS)
	{
		return false;
	}

	eXosip_set_user_agent(sipContext_, name.c_str());

	ret = eXosip_listen_addr(sipContext_, IPPROTO_UDP, Ip.c_str(), port, AF_INET, 0);
	if (ret != OSIP_SUCCESS)
	{
		eXosip_quit(sipContext_);
		//ERROR_LOG("SIP服务监听启动失败");
		return false;
	}

	sender_ = new OsipSender(sipContext_);
	msgFactory_ = new MessageFactory(sender_);
	std::cout<<"SIP服务启动成功\n";

	return true;
}

std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();


void SIPUserServer::Dispatch(MessageQueue & msgqueue)
{
	osip_body_t *m_body;
	while (true)
	{
		//std::cout << "waiting for sip event....\n";
		last = std::chrono::steady_clock::now();

		event_ = eXosip_event_wait(sipContext_, 10, 500);

		current = std::chrono::steady_clock::now();
		std::cout << "waiting took "
			<< std::chrono::duration_cast<std::chrono::microseconds>(current - last).count()
			<< "us.\n";

		if (NULL == event_)
			continue;

		if (NULL != event_->request)
			osip_message_get_body(event_->request, 0, &m_body);

		osip_via_t *via;
		osip_message_get_via(event_->request, 0, &via);

		switch (event_->type)
		{
		case EXOSIP_IN_SUBSCRIPTION_NEW:
		{
		}
		break;

		case EXOSIP_SUBSCRIPTION_NOTIFY:
		{

		}
		break;

		case EXOSIP_MESSAGE_NEW:
		{

			AbstractMessage *msg = msgFactory_->CreateRegisterMessage();
			if (msg != nullptr)
			{
				std::string body;
				GetRegisterInfomation(body);
				TiXmlDocument doc;
				doc.Parse(body.c_str(), 0, TIXML_ENCODING_LEGACY);
				TiXmlElement *pRoot = doc.RootElement();

				std::vector< TiXmlNode* > nodes;
				for (TiXmlNode *pNode = pRoot->FirstChild(); pNode != 0; pNode = pNode->NextSibling())
				{
					nodes.push_back(pNode);
				}
				msg->ParseFromSIP(nodes);
				std::shared_ptr<AbstractMessage> msgptr(msg);
				msgqueue.Push(msgptr);
			}
			else
			{
				std::cout << "CreateInviteMessage failed\n";
			}

		}
		break;

		case EXOSIP_MESSAGE_ANSWERED:
		{

		}
		break;
		case EXOSIP_CALL_INVITE:// 请求视频 包括历史录像， 文件下载
		{

			//MsgBase *msg = msgFacotry_->CreateInviteMsg();

			//queue_->Push(msg);
		}
		break;

		case EXOSIP_CALL_ACK:
		{
			//startplay
			//CreateAckMsg( );
		}
		break;

		case EXOSIP_CALL_ANSWERED:
		{


		}
		break;
		case	EXOSIP_CALL_CLOSED:
		{
			// 收到上级平台发送的BYE, 转送给下级
			// 调用关闭会话函数， 传入DeviceID 
			//CreateByeMsg();
		}
		break;
		case EXOSIP_REGISTRATION_FAILURE:
		{

		}
		break;

		case EXOSIP_REGISTRATION_SUCCESS:
		{

		}
		break;
		case EXOSIP_CALL_MESSAGE_NEW:
		{
		}
		break;

		default:
			//ERROR_LOG("不处理的sip包类型: " << event_->type);
			break;
		}
		if (event_ != nullptr)
		{
			eXosip_event_free(event_);
		}
		

	}
}

void SIPUserServer::GetRegisterInfomation(std::string & info)
{

	osip_authorization_t *auth = NULL;
	int ret = osip_message_get_authorization(event_->request, 0, &auth);
	if (auth == NULL /*&& ret == -1*/)
	{

		//int ret = eXosip_message_build_answer(sipContext_, event_->tid, 401, &answer);
		//osip_www_authenticate_t * header = NULL;
		//osip_www_authenticate_init(&header);
		//ret = osip_message_set_www_authenticate(answer, "Digest realm=\"3402000000\",nonce=\"5396ea7d22a90f95\"");
		//ret = eXosip_message_send_answer(sipContext_, event_->tid, 401, answer);
		//return;
	}
	osip_contact_t *contact = NULL;


	osip_message_get_contact(event_->request, 0, &contact);

	int  expires = 0;
	osip_header_t *h;
	if (osip_message_header_get_byname(event_->request, "expires", 0, &h) != -1)
	{
		expires = atoi(h->hvalue);
	}

	contact->url->username;


	std::ostringstream content;
	content << "<?xml version=\"1.0\"?>\r\n";
	content << "<Info>\r\n";
	content << "<USER>" << contact->url->username << "</USER>\r\n";
	content << "<EXPIRES>" << expires << "</EXPIRES>\r\n";
	content << "<TID>" << event_->tid << "</TID>\r\n";
	content << "<AUTHORIZATION>" << "NO" << "</AUTHORIZATION>\r\n";
	content << "</Info>" << "\r\n";
	info = content.str();
}



#include"Sender.h"
#include "RegisterMessage.h"
#include<iostream>
#include<ctime>
OsipSender::OsipSender()
{
}

OsipSender::OsipSender(eXosip_t * sipContext):sipContext_(sipContext)
{
}

OsipSender::~OsipSender()
{
}

bool OsipSender::SendRegisterAck(const RegisterMessage &msg)
{
	osip_message_t *answer = NULL;
	eXosip_message_build_answer(sipContext_, msg.GetTid(), 200, &answer);

	char time[64] = { 0 };
	//std::time_t t = std::time(nullptr);
	//std::tm tm = *std::localtime(&t);
	//std::ostringstream content;
	//content << std::put_time(&tm, "%FT%T:000");
	//std::string strtime = content.str();

	std::time_t t = std::time(NULL);
	if (std::strftime(time, sizeof(time), "%FT%T:000", std::localtime(&t))) {
		std::cout <<"SendRegisterAck time: " <<time << '\n';
	}
	osip_message_set_date(answer, time);
	int ret;
	if ( (ret = eXosip_message_send_answer(sipContext_, msg.GetTid(), 200, answer)) != OSIP_SUCCESS)
	{
		std::cout << "eXosip_message_send_answer failed\n";
		return false;
	}

	return true;
}

bool OsipSender::SendRegister()
{
	return false;
}

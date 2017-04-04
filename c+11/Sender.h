#pragma once
#include "eXosip2/eXosip.h"
#include "AbstractSender.h"

class RegisterMessage;

class OsipSender : public AbstractSender
{
public:
	OsipSender();
	OsipSender(struct eXosip_t* sipContext);
	~OsipSender();
	virtual bool SendRegisterAck(const RegisterMessage &msg);
	virtual bool SendRegister() ;

private:
	struct eXosip_t* sipContext_;
};


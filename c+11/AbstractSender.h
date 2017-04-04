#pragma once

class AbstractMessage;
class RegisterMessage;

class AbstractSender
{
public:
	AbstractSender() {};
	~AbstractSender() {};

	virtual bool SendRegisterAck(const RegisterMessage &msg) = 0;
	virtual bool SendRegister() = 0;
	//virtual bool Send

private:

};
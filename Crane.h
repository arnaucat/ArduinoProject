#ifndef Crane_h
#define Crane_h

#include "Mail.h"

class Crane{
public:
	void deliverMail(Mail* mail); //Entrega el Mail
	void storeMail(Mail* mail);
};

#endif



#ifndef Mail_h
#define Mail_h

#include "Box.h"
#include "User.h"

class Mail{
	public:
		Mail(User* user, Box* box, float  tray_width);
		User* getUser();
		Box* getBox();
		float getTrayWidth();
		bool operator==(Mail& mail)const;
		Mail& operator=(const Mail& that);
	private:
		User* user; //usuari destinatari
		Box* box; //Box en el que esta emmagatzemat el paquet
		float tray_width; //amplada de la bandeja
};
#endif


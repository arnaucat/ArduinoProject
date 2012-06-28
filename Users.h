#ifndef Users_h
#define Users_h

#include "User.h"

class Users{
public:
	~Users();
	Users();
	User* getUser(int id); // Retorna l'usuari identificat per la id. Si no existeix retorna null

private:
	User* users;
	int usersCount;
};

#endif

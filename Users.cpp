#include "Users.h"
#include <stdlib.h>
Users::Users()
{
	this->users= (User*)malloc(2*sizeof(User));
	this->users[0]=User(12345,12345);
	this->users[1]=User(9010,9010);
	this->usersCount = 2;
}

User* Users::getUser(int id)
{
	int i;
	for(i=0;i<this->usersCount;i++)
	{
		if(this->users[i].getId() == id) return &this->users[i];
	}
	return NULL;
}

Users::~Users()
{
	free(this->users);
}


#include "User.h"


User::User(int id,int passwd)
{
	this->id=id;
	this->passwd=passwd; 
}
int User::getId(){return this->id;}
bool User::rightPassword(int passwd){return this->passwd == passwd;}

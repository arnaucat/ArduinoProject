#include "Mail.h"
Mail::Mail(User* user, Box* box, float  tray_width)
{
  this->user = user;
  this->box = box;
  this->tray_width=tray_width;
}



User* Mail::getUser(){return this->user;}
Box* Mail::getBox(){return this->box;}
float Mail::getTrayWidth(){return this->tray_width;}
bool  Mail::operator==(Mail& mail)const
{
    if(mail.getBox() == this->box)return true;
    return false;
}


Mail& Mail::operator=(const Mail& that)
{
    this->user = that.user;
    this->box = that.box;
    return *this;
}

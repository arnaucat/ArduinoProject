#include "Box.h"
Box::Box(float  h,float w,float d,float x,float y)
 {
  this->heigh= h;
  this->widt=w;
  this->depth=d;
  this->x=x;
  this->y=y;
 }


float Box::getHeigth(){return  this->heigh;}
float Box::getWidth(){return this->widt;}
float Box::getDepth(){return this->depth;}
float Box::getx(){return this->x;}
float Box::gety(){return this->y;}



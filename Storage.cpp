#include "Storage.h"
#include "Mail.h"
#include "Box.h"
//#include "WProgram.h"
#define NUM_BOXES 7
#define MAX_MAIL NUM_BOXES
#include <stdio.h>
#include <stdlib.h>


//http://icu-project.org/docs/papers/cpp_report/the_anatomy_of_the_assignment_operator.html


//Search pointer to object in a list of onjects
template <class T>
int indexOf(T object, T list[], int listLength)
{
  int i;
  for(i=0;i<listLength;i++)
  {

    if(list[i] == object) return i;
  }
  return -1;
}

//Search pointer to object in a list of pointers to object
template <class T>
int indexOf(T* object, T* list[], int listLength)
{
  int i;
  for(i=0;i<listLength;i++)
  {
    if(list[i] == object) return i;
  }
  return -1;
}





template <class T>
bool remove(T* object, T* list[], int listLength){
 int index = indexOf<T> (*object,*list,listLength);

 fflush(stdout);
 if(index==-1) return false;
  if( index == listLength-1 ){
     return true;
   } //Trivial, decrementa el contador

  int i;
  for(i=index;i<listLength-1;i++)
  {
    (*list)[i]=(*list)[i+1];
  }
  return true;
}




/*

(6,0)		(12,6)
++++++++++++++
+	+	 + 6 +
+ 1	+ 3	 +++++
++++++++++ 5 +
+	+	 +++++
+ 0	+ 2	 + 4 +
++++++++++++++
(0,0)		(12,0)

Boxn: h,w,d,x,y
----------------
Box0: 2,4,5,0,0;
Box1: 2,4,5,0,3;
Box2: 2,4,5,4,0;
Box3: 2,4,5,4,3;

Box4: 1,4,5,7,0;
Box5: 1,4,5,7,2;
Box6: 1,4,5,7,4;

*/


Storage::Storage(){
    this->boxes = (Box*)malloc(NUM_BOXES*sizeof(Box));


	this->boxes[0] =  Box(2,4,5,0,0);
	this->boxes[1] =  Box(2,4,5,0,3);
	this->boxes[2] =  Box(2,4,5,4,0);
	this->boxes[3] =  Box(2,4,5,4,3);
	this->boxes[4] =  Box(1,4,5,7,0);
	this->boxes[5] =  Box(1,4,5,7,2);
	this->boxes[6] =  Box(1,4,5,7,4);

    this->mails =(Mail*) malloc(MAX_MAIL*sizeof(Mail));
    this->mailCount=0;
    //Recuperar informació de la SD
    }

Storage::~Storage()
{


	free(this->mails);

	free(this->boxes);

}


Mail*  Storage::hasMail(User* user){
        int userMailCount = 0;

        int i;
        for(i=0;i<mailCount;i++)
        {
          if(this->mails[i].getUser()->getId() == user->getId() ){return &mails[i];}
        }
        return NULL;
};

int Storage::availableBoxes(float h, float w, float d,Box*** availableBoxesPtr){

    *availableBoxesPtr = (Box**)malloc(NUM_BOXES*sizeof(Box*));
    Box** availableBoxes = *availableBoxesPtr;
    int availableBoxesCount = 0;


    // Recupera els Box ocupats
    Box** ocupedBoxes = (Box**)malloc(this->mailCount*sizeof(Box*));
    int ocupedBoxesCount = 0;
    int i;
    for(i=0;i<this->mailCount;i++)
    {
        ocupedBoxes[i] =this->mails[i].getBox();
        ocupedBoxesCount++;
    }


    for(i=0;i<NUM_BOXES;i++)
    {
      if(indexOf<Box>(&this->boxes[i],ocupedBoxes,ocupedBoxesCount)==-1
          && this->boxes[i].getHeigth()>=h
          && this->boxes[i].getWidth()>=w
          && this->boxes[i].getDepth()>=d
      ){availableBoxes[availableBoxesCount]=&this->boxes[i]; availableBoxesCount++;}
    }
   return availableBoxesCount;
}



Mail * Storage::storeMail(Mail mail)
{

	this->mails[this->mailCount] = mail;
	this->mailCount++;
	    printf("Mailcount: %i\n",this->mailCount);
    fflush(stdout);

	return &this->mails[this->mailCount];



}

void Storage::removeMail(Mail* mail)
{
    bool removed = remove<Mail> (mail,&this->mails,this->mailCount);
    if(removed){this->mailCount--;}
    printf("Mailcount: %i\n",this->mailCount);
    fflush(stdout);

}



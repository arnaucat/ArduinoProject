#include <LiquidCrystal.h>

#include <Keypad.h>


#include <stdio.h>
#include <stdlib.h>
#include "User.h"
#include "Storage.h"
#include "Users.h"

#define NO_MAIL -1
#define USER_NOT_FOUND -2
#define NO_ROOM -3
#define OK 0

Users users;
Storage storage;
//Crane crane;









LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte ROWS = 4; //four rows
    const byte COLS = 3; //three columns
    char keys[ROWS][COLS] = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'#','0','*'}
    };
    byte rowPins[ROWS] = {31, 32, 33, 34}; //connect to the row pinouts of the keypad
    byte colPins[COLS] = {35, 36, 37}; //connect to the column pinouts of the keypad

    Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
   // keypad.setHoldTime(500);               // Default is 1000mS
    //keypad.setDebounceTime(250);           // Default is 50mS





#define RETURN_KEY '*'
#define DEL_KEY '#'
#define MAX_TEXT_INPUT_LENGTH 100

void setup();
void setupKeyPad();
void setupScreen();

bool binaryQuestion(char* question);
float getDimension(char* dimensioName);
char* getUserInput(int waitMillis,int* messageLength,char* displayMessage,bool inputAsPlainText);
void showMessage(char* message);

User * userLogin();
int porcessMailOutput(User* user);
int processMailInput();

/*Show the message to the user through the LCD display. Waits 1 second before returning*/
void showMessage(char* message)
{
    
    lcd.clear();   
    lcd.print(message);
    delay(1500);
    
}


/* Setup operations to be made on system startup */
void setup()
{
      Serial.begin(9600);
   Users users = Users();
    Storage storage = Storage();
   // ff();
    setupKeyPad();
    setupScreen();
   //messageLength = 0;
}


void setupKeyPad()
{
   
   
}

void setupScreen()
{
   LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  lcd.begin(16,2);
}

/**
* Encapsulates the login proces which is as follows:
* 1:User enters it's id -> The user can enter ids forever until a id match with one in the system.
* 2:User enters passwords -> The user has 3 oportunities to type in the correct password.
*
* Return a pointer to the validated user
*
**/
User * userLogin()
{
    User* user = NULL;
    bool validated;
    do
    {
        validated =false;
        int userIdStringLength=0;
        char* userIdString;

            while(user==NULL)
            {
                userIdString =getUserInput(10,&userIdStringLength,"Introdueix id:",true);
                if(userIdStringLength>0) user = users.getUser(atoi(userIdString));
            }

            int tryCount = 0;

            while(user==NULL || tryCount ==3)
            {
                int userPasswdStringLength;
                char* userPasswdString = getUserInput(10,&userPasswdStringLength,"Introdueix contrassenya:",false);
                if(userPasswdStringLength>0) validated = user->rightPassword(atoi(userPasswdString));

            }
    }
    while(!validated);

    return user;
}


float getDimension(char* dimensioName)
{
  
    int valueStringLength;
    while(true)
    {
      char* valueString = getUserInput(100,&valueStringLength,dimensioName,true);
      if(valueStringLength>0) return atof(valueString);
    }
    return -1;

}


/**
* Ask a binary question (yes or no) to the user. Returns the user answer.
* Keeps asking the question until a valid answer is given.
*
*/
bool binaryQuestion(char* question)
{
    while(true)
    {
        int responseStringLength;
        char* responseString = getUserInput(100,&responseStringLength,question,true);
        if(responseStringLength>0)
        {
          Serial.println(responseString);
           if(responseString=="0\0")  return false;
           if(responseString=="1\0")  return true;
        }
    }
}


void postMan()
{
  
Box** avalibleBoxes;
int avalibleBoxesCount = storage.availableBoxes(0,0,0,&avalibleBoxes); //Check if box exists to store this mail
  if(avalibleBoxesCount<1)
  {
    showMessage("No room for mail");
    return;
  
  }
    
  bool keepOn;
  do
  {
     processMailInput();
     keepOn = binaryQuestion("More 0:n 1:y");
  }while(!keepOn);
}




/**
* Get the user input data writen using the keyboard.
* If a message is given, shows it in the firs line of the screen
* When the user writes something with the keyboard, this input information is displayed in the first or second line of the screen.
* If "inputAsPlainText" == false, the characters typed by the user are replaced with "*" on the screen.
* If the user is inactive for a period longer than "waitMillis" miliseconds returns
* Return: a char array with the message and sets the value of *messageLength to be the numer of chars typed.
**/
char* getUserInput(int waitMillis,int* messageLength,char* displayMessage,bool inputAsPlainText)
{
   
    
    char* message = (char*) malloc(sizeof(char)*MAX_TEXT_INPUT_LENGTH );
     (*messageLength) = 0;
  
    int x =0;
    int y = 1;
    //if(displayMessage==NULL) y = 0; displayMessage =" ";


    unsigned long startT=millis();
    //while(millis()-startT<waitMillis)// The time hasn't been consumed
    

     lcd.clear();
     lcd.print(displayMessage);         
  lcd.setCursor(x,y);   
      lcd.blink();
    
    while(true)
    {    
        char key = keypad.getKey();
        if((*messageLength) == MAX_TEXT_INPUT_LENGTH) return message; //No more space for input
        if(key==RETURN_KEY) return message; //return key pressed
        if(key==DEL_KEY)
        {
            startT=millis();
            if((*messageLength)==0) break; //No need to do nothing
            (*messageLength)=(*messageLength)-1;
            message[*messageLength] = '\0'; //Add end of string char

            //Write the messages to the LCD
           lcd.clear();
           lcd.print(displayMessage);
           lcd.setCursor(x,y);
           if(inputAsPlainText)lcd.print(message);
           else{int i; for(i=0;i<*messageLength;i++) lcd.write('*');}


        }else
        {
            if(key != NO_KEY)
            {
           
                startT=millis(); // Reset the unactive watch
                message[*messageLength] = key; //Store the key
                (*messageLength)=(*messageLength)+1;
                message[*messageLength] = '\0'; //Add end of string char
                
                //Write the messages to the LCD
               lcd.clear();
               lcd.print(displayMessage);
               lcd.setCursor(x,y);
               if(inputAsPlainText)lcd.print(message);
               else{int i; for(i=0;i<*messageLength;i++) lcd.write('*');}
            }
        }
                delay(10);
    }
          lcd.noBlink();
    return message;
}





int porcessMailOutput(User* user)
{
	Mail* mail = storage.hasMail(user);
	if( mail==NULL)
	{
		//User doesn't have mail
        printf("User doesn't has mail\n");
		fflush(stdout);
		return NO_MAIL;
	}

	int i=0;
	while(mail!=NULL)
	{
		//Deliver mail
		//crane.deliverMail(userMails[i]);
		printf("Delivering stored at stored at box x:%f y:%f to user %i\n",mail->getBox()->getx(),mail->getBox()->gety(),user->getId());
		fflush(stdout);

		storage.removeMail(mail);
        mail = storage.hasMail(user);
        i++;
	}
	return  OK;
}



int processMailInput()
{
    Serial.println("Start mail proces");
    User* user = NULL;
    int adresseeIdStringLength;
    char* adresseeIdString = getUserInput(100,&adresseeIdStringLength,"Id adressee:",true);

    if(adresseeIdStringLength>0) user = users.getUser(atoi(adresseeIdString));
	if(user == NULL)
	{
		//User doesn't exist in system
                showMessage("User not exists");
                Serial.print("User with id ");
                Serial.print(atoi(adresseeIdString));
                Serial.print(" not in the system \n");
                
                                         
		printf("User (%i) not in the system\n",atoi(adresseeIdString));
		fflush(stdout);
		return USER_NOT_FOUND;
	}


        float h= getDimension("Height (cm):");
        float w= getDimension("Width (cm):");
        float d= getDimension("Depth (cm):");
 
	Box** avalibleBoxes;
	int avalibleBoxesCount = storage.availableBoxes(h,w,d,&avalibleBoxes); //Check if box exists to store this mail

	if(avalibleBoxesCount==0) // There is no room for this mail
	{
            Serial.print("No room for a mail with dimensions h: ");
            Serial.print(h);
            Serial.print(" w: ");
            Serial.print(w);
            Serial.print(" d:  ");
            Serial.print(d);
            Serial.print("\n");    
            
	    printf("No room for the mail\n");
            showMessage("No room for mail");
	    fflush(stdout);

	    free(avalibleBoxes);//Free the array space
		return NO_ROOM;
	}



	Mail mail = Mail(user,avalibleBoxes[0],10);
	Mail* mailPtr = storage.storeMail(mail);

    printf("Mail to user: %i stored at box x:%f y:%f\n",user->getId(),avalibleBoxes[0]->getx(),avalibleBoxes[0]->gety());
      Serial.print("Mail stored at box x: ");
            Serial.print(avalibleBoxes[0]->getx());
            Serial.print(" y: ");
            Serial.print(avalibleBoxes[0]->gety());
            Serial.print("\n");
   
    showMessage("Mail stored");
	//crane.storeMail(mailPtr);
    free(avalibleBoxes);//Free the array space
}

void loop() {

 
  //lcd.print(" ss");
  int e;
  //
 //getUserInput(100,&e,"HOLA?",false);
 // processMailInput();
 postMan();
}

int ff()
{

    Box** avalibleBoxes;
    int maxAvalibleBoxesCount = storage.availableBoxes(1,1,1,&avalibleBoxes);
    printf("num boxes: %i\n",maxAvalibleBoxesCount);
    fflush(stdout);

    int i;
    for(i=0;i<maxAvalibleBoxesCount+1;i++)
    {
        processMailInput();
    }
    porcessMailOutput(users.getUser(12345));

    for(i=0;i<maxAvalibleBoxesCount+1;i++)
    {
        processMailInput();
    }
    return OK;
}

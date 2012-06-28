#ifndef STORAGE_H_
#define STORAGE_H_

#include "Mail.h"

class Storage{
	public:
		~Storage();
		Storage();
		Mail* hasMail(User* user); //Retorna una apuntador al primer mail del usuari
		int availableBoxes(float h, float w, float d, Box*** availableBoxes); //Retorna una llista amb tots els Box lliures que poden emmagatzemar una caixa de les dimencions especificades
		Mail * storeMail(Mail mail);
		void removeMail(Mail* mail);
	private:
		Box* boxes; //Llista amb tots els Box de la bustia, buits o plens.
		Mail* mails; //Llista amb tot el correu emmagatzemat en la bustia.
		int mailCount;
};
#endif /* STORAGE_H_ */

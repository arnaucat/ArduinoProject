#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2


void mostrar(void);
void cercarautor(void);
void entrada(void);
void grabar(void);
void llegir(void);

   struct pelis
   {
   int id;
   char titol[30];
   char director[30];
   int preu;
   int any;
   }pel[MAX];

void main(void)
{
int sele;

llegir();

clrscr();

   do
   { printf("1 Introdueix dades: \n");
     printf("2 Visualitzar les pelis \n");
     printf("3 Cercar algun titol \n");
     printf("4 Sortir premeu \n");

     printf("Escull la opcio:\n");
     scanf("%d", &sele);
     switch(sele)
     {
       case 1:
       clrscr();
       entrada();
       break;

       case 2:
       clrscr();
       mostrar();
       break;

       case 3:
       clrscr();
       cercarautor();
       break;
     }
   }while(sele!=4);

grabar();

}


   void entrada(void)
   {
   int i;
      for(i=0;i<MAX;i++)
      {
      pel[i].id=i;
      fflush(stdin);
      printf("Introdueix el titol\n");
      gets(pel[i].titol);
      fflush(stdin);
      printf("Introdueix el director\n");
      gets(pel[i].director);
      fflush(stdin);
      printf("Introdueix el preu\n");
      scanf("%d",&pel[i].preu);
      fflush(stdin);
      printf("Introduiex el any\n");
      scanf("%d",&pel[i].any);
      fflush(stdin);
      }
   }

   void mostrar(void)
   {
   int i;
   clrscr();
      for(i=0;i<MAX;i++)
      {
      printf("El identificador: %d",pel[i].id);
      printf("El titol: %s",pel[i].titol);
      printf("El director: %s",pel[i].director);
      printf("El preu: %d",pel[i].preu);
      printf("El any: %d",pel[i].any);
      }
   }

   void cercarautor(void)
   {
   int i;
   char nom[50];
   printf("Introdueix el nom del director\n");
   gets(nom);
      for(i=0;i<MAX;i++)
      {
	 if(strcmp(nom,pel[i].director)==0)
	 {
	 printf("%s\n",pel[i].titol);
	 printf("Pren return per continuar\n");
	 getch();
	 clrscr();
	 }
      }
   }

   void grabar(void)
   {
   FILE *f;
   int i;

   f=fopen("arxiu.txt","w");
     for(i=0;i<MAX;i++)
	{
	fwrite(&pel[i],sizeof(struct pelis),1,f);
	}
   fclose(f);
//   fwrite(&pel,sizeof(struct pelis),MAX,f);
   }

   void llegir(void)
   {
   FILE *f;
   int i;

   f=fopen("arxiu.txt","r");
     for(i=0;i<MAX;i++)
	{
	fread(&pel[i],sizeof(struct pelis),1,f);
	}
   fclose(f);
//   fread(&pel,sizeof(struct pelis),MAX,f);
   }
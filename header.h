#ifndef HEADER_H_
#define HEADER_H_

int creare_cont();
int creare_baza_date();
int logare_cont();
int verificare_robot_inregistrare();
int intrebare_logare();
int resetare_parola();
int scanare();
int baza_date,i;
int n = 0;
struct date{
	char nume[32];
	char parola[32];
	char email[32];
};
struct date cont;

#endif

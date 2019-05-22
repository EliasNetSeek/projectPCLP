#ifndef HEADER_H_
#define HEADER_H_

int creare_cont();
int creare_baza_date();
int logare_cont();
int verificare_robot_inregistrare();
int intrebare_logare();
int resetare_parola();
int scanare();
<<<<<<< HEAD
int stergere_baza_date();
char parola_secreta[32] = "resetare_";
=======
>>>>>>> e78ada7b51dac416eee4642b297f995d487544a5
int baza_date,i;
int n = 0;
struct date{
	char nume[32];
	char parola[32];
	char email[32];
};
struct date cont;

#endif
#ifndef HEADER_H_
#define HEADER_H_

int creare_cont(void);
int creare_baza_date(void);
int logare_cont(void);
int verificare_robot_inregistrare(void);
int intrebare_logare(void);
int resetare_parola(void);
int scanare();
int stergere_baza_date(void);
char parola_secreta[32] = "resetare_";
int baza_date,i;
int n = 0;
struct date{
	char nume[32];
	char parola[32];
	char email[32];
};
struct date cont;
//////////////////////////////////////////
int numarareCarti();
int verificareBiblioteca(void);
int meniu(void);
int adaugareCarte(void);
int afisareLista(void);
int cautareCarte(void);
void grafica();
int informatiiGrafic(void);
struct carti{
    char nume[32];
    char autor[32];
    int secol;
};
struct carti virtuale;
#endif

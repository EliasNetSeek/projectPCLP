#include <stdio.h>
#include <string.h>
#include "header.h"
#define BAZA_DATE "baza de date.txt"
//TEST GITHUB

// TO DO
// Blocarea inregistrarii peste o persoana deja existenta
// tabel cu user / pass / email
// 2 fisere de functii

int main(void){
	int raspuns;
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	if (!baza_date){
		creare_baza_date();
	}
	printf("\nLogare (1) sau inregistrare (2) :");
	scanf("%d", &raspuns);
	switch (raspuns){
	case 1:
		logare_cont();
		break;
	case 2:
		creare_cont();
		break;
	default:
		printf("Valoare gresita! Terminare.");
		break;
	}
	fclose(baza_date);
}

int logare_cont(){
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	int comparaNume;
	int comparaParola;
	int verificare;
	char nume[32];
	char parola[32];
	printf("Nume: ");
	scanf("%s", nume);
	printf("Parola: ");
	scanf("%s", parola);
	printf("Esti robot? (1+1): ");
	scanf("%d", &verificare);
	if (verificare == 2){
		fscanf(baza_date, "%s %s %s", cont.nume, cont.parola, cont.email);
		comparaNume = strcmp(nume,cont.nume);
		comparaParola = strcmp(parola,cont.parola);
		if(comparaNume == 0){
			if (comparaParola == 0){
				printf("\nContul exista"); //debug
				printf("\nBun venit, %s", cont.nume);
				//int v = strlen(cont.parola);
				//printf("%d", v);
			} else {
				printf("\nParola pentru contul '%s' este gresita.", cont.nume);
				fclose(baza_date);
				resetare_parola();
			}
		} else {
			printf("\nNumele de utilizator este gresit.");
		}
	} else {
		printf("Verificarea a esuat.");
		return 0;
	}
	return 1;
}

int creare_cont(){
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	i=0;
	printf("Nume: ");
	scanf("%s", cont.nume);
	printf("Parola: ");
	scanf("%s", cont.parola);
	printf("E-mail:");
	scanf("%s", cont.email);
	verificare_robot_inregistrare();
	return 1;
}

int creare_baza_date(){
	FILE *baza_date;
	int x=0;
	printf("Baza de date inexistenta\nDoresti sa initializezi una? (1 - da; 0 - nu): ");
	scanf("%d", &x);
	switch (x) {
	case 0:
		printf("Program terminat! (baza de date inexistenta)");
		break;
		return 0;
	case 1:
		baza_date = fopen(BAZA_DATE, "w");
		printf("Baza de date a fost creata!");
		fclose(baza_date);
		break;
	default:
		printf("Valoare gresita");
		break;
	}
	return 1;
}

int verificare_robot_inregistrare(){
	int verificare;
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	printf("Esti robot? (1+1): ");
	scanf("%d", &verificare);
		if (verificare == 2){
			fprintf(baza_date, "%s %s %s", cont.nume, cont.parola, cont.email);
			printf("Contul a fost creat cu numele: %s", cont.nume);
			fclose(baza_date);
			intrebare_logare();
		} else {
			printf("Verificarea a esuat.");
			return 0;
	}
	return 1;
}

int intrebare_logare(){
	int rasp;
	printf("\nDoresti sa te autentifici (1 - da; 0 - nu) ?");
	scanf("%d", &rasp);
	if(rasp == 1){
	logare_cont();
	} else {
	printf("Terminare program...");
	}
	return 1;
}

int resetare_parola(){
	int raspuns;
	char email[32];
	int comparaEmail;
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	printf("\nDoresti sa resetezi parola (1 - da; 0 - nu) ? ");
	scanf("%d", &raspuns);
	if (raspuns == 1){
		fscanf(baza_date, "%s %s %s", cont.nume, cont.parola, cont.email);
		printf("\nIntroduceti email-ul de la contul '%s'", cont.nume);
		printf("\n%c%c******@*****.com : ", cont.email[0], cont.email[1]);
		scanf("%s", email);
		comparaEmail = strcmp(email,cont.email);
				if(comparaEmail == 0){
					printf("Introduceti noua parola: ");
					scanf("%s", cont.parola);
					printf("Parola a fost schimbata.");
					fclose(baza_date);
					baza_date = fopen(BAZA_DATE, "r+");
					fprintf(baza_date, "%s %s %s", cont.nume, cont.parola, cont.email);
					fclose(baza_date);
					intrebare_logare();
				} else {
					printf("Email gresit. Terminare.");
					return 0;
				}
	} else {
		printf("Terminare program.");
		return 0;
	}
	return 1;
}

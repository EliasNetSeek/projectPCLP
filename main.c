#include <stdio.h>
#include <string.h>
#include "header.h"
#define BAZA_DATE "utilizatori.db"
#define LIBRARIE "librarie.txt"
#include <GLUT/GLUT.h>

int main(int argc, char** argv){
	glutInit(&argc, argv);
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	if (!baza_date){
		creare_baza_date();
	}
	if(scanare()==0){
		printf("_____________ INREGISTRARE UTILIZATOR _____________\n");
		fflush(stdout);
		creare_cont();
	} else {
		printf("_____________ LOGARE UTILIZATOR _____________\n");
		fflush(stdout);
		logare_cont();
	}
	fclose(baza_date);
	glutCreateWindow("STATISTICA DUPA SECOL (GRAFIC)");
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(grafica);
	glutMainLoop();
    return 0;
}

int scanare(){
	char numarare;
	int linii=0;
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r");
	while((numarare=fgetc(baza_date))!=EOF){
		if(numarare=='\n'){
			linii++;
		}
	}
	return linii;
}

int logare_cont(){
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	int comparaNume;
	int comparaParola;
	int comparaStergereParola;
	int verificare;
	char nume[32];
	char parola[32];
	printf("Nume: ");
	fflush(stdout);
	scanf("%s", nume);
	printf("Parola: ");
	fflush(stdout);
	scanf("%s", parola);
	printf("Esti robot? (1+1): ");
	fflush(stdout);
	scanf("%d", &verificare);
	if (!(verificare==2)){
		for(int i=0;i<1;i++){
			printf("Esti robot? (1+1): ");
			fflush(stdout);
			scanf("%d", &verificare);
		}
	}
	if (verificare == 2){
		fscanf(baza_date, "%s | %s | %s", cont.nume, cont.parola, cont.email);
		fscanf(baza_date, "%s | %s | %s", cont.nume, cont.parola, cont.email);
		comparaNume = strcmp(nume,cont.nume);
		comparaParola = strcmp(parola,cont.parola);
		if(comparaNume == 0){
			if (comparaParola == 0){
				printf("\nBun venit, %s\n", cont.nume);
				verificareBiblioteca();
				meniu();
			} else {
				printf("\nParola pentru contul '%s' este gresita.", cont.nume);
				fclose(baza_date);
				resetare_parola();
			}
		} else {
			comparaStergereParola = strcmp(parola, parola_secreta);
			if(comparaStergereParola == 0){
				stergere_baza_date();
			} else {
			printf("\nNumele de utilizator este gresit.");
			}
		}
	} else {
		printf("Verificarea a esuat.");
		return 0;
	}
	return 1;
}

int creare_cont(){
	i=0;
	printf("Nume: ");
	fflush(stdout);
	scanf("%s", cont.nume);
	printf("Parola: ");
	fflush(stdout);
	scanf("%s", cont.parola);
	if(strlen(cont.parola)<6){
		printf("Inregistrarea necesita o parola de minim 6 caractere\n");
		printf("Parola: ");
		fflush(stdout);
		scanf("%s", cont.parola);
	}
	printf("E-mail:");
	fflush(stdout);
	scanf("%s", cont.email);
	verificare_robot_inregistrare();
	return 1;
}

int creare_baza_date(){
	FILE *baza_date;
	int raspuns=0;
	printf("Baza de date inexistenta\nDoresti sa initializezi una? (1 - da; 0 - nu): ");
	fflush(stdout);
	scanf("%d", &raspuns);
	switch (raspuns) {
	case 0:
		printf("Program terminat! (baza de date inexistenta)");
		break;
		return 0;
	case 1:
		baza_date = fopen(BAZA_DATE, "w");
		fprintf(baza_date, "Nume | Parola | E-mail");
		printf("Baza de date a fost creata!\n");
		fclose(baza_date);
		break;
	default:
		printf("Valoare gresita\n");
		printf("Terminare program...\n");
		return 0;
	}
	return 1;
}

int stergere_baza_date(){
	remove(BAZA_DATE);
	printf("Baza de date a fost stearsa!\n");
	return 1;
}

int verificare_robot_inregistrare(){
	int verificare;
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "a");
	printf("Esti robot? (1+1): ");
	fflush(stdout);
	scanf("%d", &verificare);
	if (!(verificare==2)){
		for(int i=0;i<1;i++){
			printf("Esti robot? (1+1): ");
			scanf("%d", &verificare);
		}
	}
	if (verificare == 2){
		fprintf(baza_date, "\n%s | %s | %s", cont.nume, cont.parola, cont.email);
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
	printf("\nDoresti sa te autentifici (1 - da; 0 - nu) ? :");
	fflush(stdout);
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
	int caracteremail;
	char email[32];
	int comparaEmail;
	FILE *baza_date;
	baza_date = fopen(BAZA_DATE, "r+");
	printf("\nDoresti sa resetezi parola (1 - da; 0 - nu) ? ");
	fflush(stdout);
	scanf("%d", &raspuns);
	if (raspuns == 1){
		fscanf(baza_date, "%s | %s | %s", cont.nume, cont.parola, cont.email);
		fscanf(baza_date, "%s | %s | %s", cont.nume, cont.parola, cont.email);
		printf("\nIntroduceti email-ul de la contul '%s'", cont.nume);
		fflush(stdout);
		printf("\n%c%c%c", cont.email[0], cont.email[1], cont.email[2]);
		caracteremail = strlen(cont.email) - 3;
		for(i=0;i<caracteremail;i++){
			printf("*");
		}
		printf(": ");
		fflush(stdout);
		scanf("%s", email);
		comparaEmail = strcmp(email,cont.email);
				if(comparaEmail == 0){
					printf("Introduceti noua parola: ");
					fflush(stdout);
					scanf("%s", cont.parola);
					printf("Parola a fost schimbata.");
					fclose(baza_date);
					baza_date = fopen(BAZA_DATE, "r+");
					fprintf(baza_date, "Nume | Parola | E-mail");
					fprintf(baza_date, "\n%s | %s | %s", cont.nume, cont.parola, cont.email);
					fclose(baza_date);
					intrebare_logare();
				} else {
					printf("Email gresit. Terminare.");
					return 0;
				}
	} else {
		printf("Terminare program...");
		return 0;
	}
	return 1;
}

int verificareBiblioteca(){
    int raspuns = 0;
    FILE *librarie;
    librarie = fopen(LIBRARIE, "r+");
    if (!librarie){
        printf("Libraria pentru biblioteca este inexistenta\nDoriti sa creati una (1-da;0-nu) ?\n");
        fflush(stdout);
        scanf("%d", &raspuns);
        if (raspuns == 1){
            librarie = fopen(LIBRARIE, "w");
            printf("Libraria a fost creata\n");
            printf("Terminare program\n"); //debug
            return 0;
        } else {
            printf("Terminare program\n");
            return 0;
        }
    }
    return 1;
}

int numarareCarti(){
    int linii = 0;
    FILE *librarie;
    librarie = fopen("librarie.txt", "r+");
    char numarare;
    while((numarare=fgetc(librarie))!=EOF){
        if(numarare=='\n'){
            linii++;
        }
    }
    return linii;
}

int meniu(){
    int raspuns;
    printf("Momentan avem %d de carti!\n", numarareCarti());
    printf("\nOptiuni: \n");
    printf("1. Adaugare carti\n");
    printf("2. Cautare carte\n");
    printf("3. Afisare lista\n");
    printf("4. Statistica dupa secol (grafic)\n");
    printf("5. Terminare program\n");
    printf("6. Informatii Grafic\n");
    printf("\n Alegerea ta: ");
    fflush(stdout);
    scanf("%d", &raspuns);
    switch(raspuns){
        case 1:
            adaugareCarte();
            break;
        case 2:
            cautareCarte();
            break;
        case 3:
            afisareLista();
            break;
        case 4:
            grafica();
            break;
        case 5:
            printf("Program terminat\n");
            break;
        case 6:
        	informatiiGrafic();
        	break;
        default:
            printf("Valoare gresita\n");
            break;
    }
    return 1;
}

int adaugareCarte(){
    FILE *librarie;
    printf("Nume: ");
    fflush(stdout);
    scanf("%s", virtuale.nume);
    printf("Autor: ");
    fflush(stdout);
    scanf("%s", virtuale.autor);
    printf("Secol: ");
    fflush(stdout);
    scanf("%d", &virtuale.secol);
    librarie = fopen(LIBRARIE, "a");
    fprintf(librarie, "%s %s %d\n", virtuale.nume, virtuale.autor, virtuale.secol);
    fclose(librarie);
    printf("Cartea a fost adaugata\n");
    meniu();
    return 1;
}

int afisareLista(){
    int raspuns;
    FILE *librarie;
    librarie = fopen(LIBRARIE, "r");
    if(numarareCarti()==0){
    	printf("Libraria este goala.\n");
    	printf("Doresti sa revii?: ");
    	fflush(stdout);
    	scanf("%d", &raspuns);
    	if (raspuns == 1){
    	    meniu();
    	} else {
    	    return 0;
    	}
    }
    for(int i=1; i<=numarareCarti(); i++){
        printf("#%d: ", i);
        fflush(stdout);
        fscanf(librarie ,"%s %s %d", virtuale.nume, virtuale.autor, &virtuale.secol);
        printf("%s %s %d\n", virtuale.nume, virtuale.autor, virtuale.secol);
    }
    fclose(librarie);
    printf("Doresti sa revii?: ");
    fflush(stdout);
    scanf("%d", &raspuns);
    if (raspuns == 1){
        meniu();
    } else {
        return 0;
    }
    return 1;
}

int cautareCarte(){
    int raspunsSecol;
    int numarare = 0;
    int raspuns;
    FILE *librarie;
    librarie = fopen(LIBRARIE, "r");
    printf("Ce secol de carti cauti: \n");
    fflush(stdout);
    scanf("%d", &raspunsSecol);
    for(int i=0; i<numarareCarti(); i++){
        fscanf(librarie ,"%s %s %d", virtuale.nume, virtuale.autor, &virtuale.secol);
        if(raspunsSecol == virtuale.secol){
            printf("Numele cartii: %s , Autorul: %s\n", virtuale.nume, virtuale.autor);
            numarare++;
        }
    }
    printf("Exista %d carti\n", numarare);
    fclose(librarie);
    printf("Doresti sa revii?: ");
    fflush(stdout);
    scanf("%d", &raspuns);
    if (raspuns == 1){
        meniu();
    } else {
        return 0;
    }
    return 1;
}

int informatiiGrafic(){
	int carti[21];
	for(int i=15; i<22;i++){
		carti[i] = 0;
	}
	float nouaCoordY[21];
	float nouaCoordX[21];
	FILE *librarie;
	for(int secol=16;secol<=21;secol++){
		librarie = fopen(LIBRARIE, "r");
		for(int i=0; i<numarareCarti();i++){
			fscanf(librarie ,"%s %s %d", virtuale.nume, virtuale.autor, &virtuale.secol);
			if(virtuale.secol == secol){
				carti[secol]++;
			}
		}
		for(int y=0;y<2;y++){
			nouaCoordY[secol] = carti[secol]*-0.15;
			if (secol >= 19){
				nouaCoordY[secol] = -nouaCoordY[secol];
			}

			nouaCoordX[secol] = 0;
			nouaCoordX[-1] = -1;
			nouaCoordX[secol] = nouaCoordX[secol-1] + 0.33;
				if(nouaCoordX[secol]>=-0.67){
					if(secol >= 19){
						nouaCoordX[secol-1] = -nouaCoordX[secol];
				}}
		printf("Y = %.2f X = %.2f\n", nouaCoordY[secol], nouaCoordX[secol]);
		}
		fclose(librarie);
	}
	int raspuns;
	printf("Doresti sa revii?: ");
	fflush(stdout);
	scanf("%d", &raspuns);
	if (raspuns == 1){
	    meniu();
	} else {
	    return 0;
	}
	return 1;
}

void grafica(){
	char numar[3];
	FILE *librarie;
	librarie = fopen(LIBRARIE, "r");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-1.0,-1.0);
    //
	int carti[21];
	for(int i=15; i<22;i++){
		carti[i] = 0;
	}
	float nouaCoordY[21];
	float nouaCoordX[21];
	for(int secol=16;secol<=21;secol++){
		librarie = fopen(LIBRARIE, "r");
		for(int i=0; i<numarareCarti();i++){
			fscanf(librarie ,"%s %s %d", virtuale.nume, virtuale.autor, &virtuale.secol);
			if(virtuale.secol == secol){
				carti[secol]++;
			}
		}
		for(int y=0;y<2;y++){
			nouaCoordY[secol] = carti[secol]*0.15-1;
			if (nouaCoordY[secol] > 0.1){
				nouaCoordY[secol] = carti[secol]*0.15;
			}
			nouaCoordX[15] = -1;
			nouaCoordX[secol] = nouaCoordX[secol-1] + 0.33;

		}
		//printf("X = %.2f Y = %.2f\n", nouaCoordX[secol], nouaCoordY[secol]); //debug
		glVertex2f(nouaCoordX[secol],nouaCoordY[secol]); //
		glVertex2f(nouaCoordX[secol],nouaCoordY[secol]);

		fclose(librarie);
		sprintf(numar,"%d", secol);
		glRasterPos2f(nouaCoordX[secol], nouaCoordY[secol] - 0.05);
		    for(int j = 0; j < strlen(numar); j++){
		    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,numar[j]);
		    }
	}
	glEnd();
//	glVertex2f(1,nouaCoordY[21]);
    glFlush();

}

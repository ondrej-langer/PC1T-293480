// Elektronicky_index.cpp : Defines the entry point for the application.
//

#include "Elektronicky_index.h"
#include "funkce.h"

using namespace std;

int main()
{
	char jmeno[100];
	int overeni = 0;

	FILE* lektori;
	lektori = fopen("lektori.txt", "a+");

	printf("------------------------------\n");

	while (overeni == 0) {														//Overeni, zda uzivatel (lektor) existuje
		printf("Zadejte sve jmeno: ");
		scanf_s("%s", jmeno, 100);												//Nacteni jmena lektora
		printf("------------------------------\n");
		if (overeniJmena(jmeno, lektori) == 1) {								//Vyhodnoceni, zda lektor existuje
			//printf("Zadali jste spravne jmeno\n");
			overeni = 1;
		}
		else if (strcmp(jmeno, "admin\n") == 0) {
			admin(lektori);
			lektori = fopen("lektori.txt", "a+");
		}
		else {
			printf("Zadali jste nespravne jmeno\n");
			printf("------------------------------\n");
			rewind(lektori);
			continue;
		}
	}
	overeni = 0;
	
	char predmet[100];
	int pocetpredmetu = 0;
	char predmety[10][50];
	unsigned short k = 0;

	while (overeni == 0) {														//Zjisteni opravneni na predmet
		printf("Zadejte predmet pro editaci (napr.: ZKR,PC1T,...): ");
		scanf_s("%s", predmet, 100);											//Nacteni predmetu pro editaci
		printf("------------------------------\n");
		if (overeniPredmetu(predmet, &pocetpredmetu, predmety, k, lektori)) {	//Vyhodnoceni, zda ma lektor opravneni editovat predmet
			k = 1;
			overeni = 1;
		}
		else {
			printf("Lektor nema pristup do predmetu\n");
			printf("------------------------------\n");
		}
		k = 1;
	}
	overeni = 0;
	k = 0;

	int akce = 0;														//Zhruba odsud TO DAT DO WHILU!!!

	FILE* studenti;
	studenti = fopen("studenti.txt", "a+");

	while (1) {
		while (overeni == 0) {														//Zadani akce, kterou chceme provest
			printf("Zadejte akci (UKONCIT APLIKACI - 0, BODYC - 1, BODYT - 2, BODYZ - 3, ADD - 4, DEL - 5): ");
			scanf_s("%d", &akce);													//Nacteni akce

			if (akce == 0) {														//Zajisteni spravnosti nacteni akci
				return 0;
			}
			else if (akce >= 1 && akce <= 5) {										//Ukonceni cyklu pri zadani spravne akce
				overeni = 1;
			}
			else {
				printf("Zadali jste špatnou akci");
			}
		}
		overeni = 0;

		int pocetpredmetuS = 0;
		char predmetyS[10][50];

		while (overeni == 0) {														//Overeni, zda student existuje
			printf("------------------------------\n");
			printf("Zadejte jmeno studenta: ");
			scanf_s("%s", jmeno, 100);												//Nacteni jmena studenta

			printf("------------------------------\n");
			if ((overeniJmena(jmeno, studenti) && overeniPredmetu(predmet, &pocetpredmetuS, predmetyS, k, studenti) == 1) && (akce >= 1 && akce <= 3)) {								//Vyhodnoceni, zda student existuje a jestli je zapsan v predmetu
				//printf("Zadali jste spravne jmeno\n");
				Body(predmet, jmeno, studenti, akce);
				studenti = fopen("studenti.txt", "a+");
				overeni = 1;
			}
			else if ((overeniJmena(jmeno, studenti)) && (akce == 5)) {
				del(predmet, jmeno, studenti);
				overeni = 1;
				studenti = fopen("studenti.txt", "a+");
			}
			else if (akce == 4) {
				if (jmeno[strlen(jmeno) - 1] != '\n') {
					strcat(jmeno, "\n");
				}
				add(predmet, jmeno, studenti);
				overeni = 1;
				studenti = fopen("studenti.txt", "a+");
			}
			else {
				int i;
				printf("Zadali jste nespravne jmeno\n");
				printf("------------------------------\n");
				rewind(studenti);
				for (i = 0; i < pocetpredmetuS; i++) {
					strcpy(predmetyS[i], "");
				}
				pocetpredmetuS = 0;
				break;
			}
		}
		overeni = 0;
	}

	fclose(lektori);										//TYTO CLOSY SMAZAT NEBO PRESUNOUT
	fclose(studenti);
	return 0;
}

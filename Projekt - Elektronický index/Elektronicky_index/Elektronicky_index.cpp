// Elektronicky_index.cpp : Defines the entry point for the application.
//

#include "Elektronicky_index.h"

using namespace std;

int overeniJmena(char* jmeno, FILE* soubor) {									//Funkce pro overeni nacteneho jmena
	char jeJmeno[100];
	while (fgets(jeJmeno, 100, soubor)) {
		if (strcmp(jmeno, jeJmeno) == 0) {
			return 1;
		}
	}
	return 0;
}

int overeniPredmetu(char* predmet, int *pocetpredmetu, char (*predmety)[50], unsigned short k, FILE* soubor) { //Funkce pro overeni prava na predemet
	char radek[100];
	char* tradek = nullptr;
	int i;

	if (k == 0) {																//Nacteni radku s predmety (pod jmenem) a pocatek deleni
		fgets(radek, 100, soubor);
		tradek = strtok(radek, " ");
	}
	
	while (tradek != NULL) {													//Prepsani jednotlivých zkratek předmětů do pole
		strcpy(predmety[*pocetpredmetu], tradek);
		printf("%s", predmety[*pocetpredmetu]);
		tradek = strtok(NULL, " ");
		(*pocetpredmetu)++;
	}

	for (i = 0; i < *pocetpredmetu; i++) {										//Hledani predmetu v poli predmety
		if (strcmp(predmet, predmety[i]) == 0){
			return 1;
		}
	}
	return 0;
}

void BodyC(char* predmet, FILE* soubor) {
	char radek[100];
	
	strcat(predmet, "\n");
	while (fgets(radek, 100, soubor)) {

	}
}

int main()
{
	char jmeno[100];
	int overeni = 0;

	FILE* lektori;
	lektori = fopen("lektori.txt", "a+");

	FILE* studenti;
	studenti = fopen("studenti.txt", "a+");

	while (overeni == 0) {														//Overeni, zda uzivatel (lektor) existuje
		printf("Zadejte sve jmeno: ");
		scanf_s("%s", jmeno, 100);												//Nacteni jmena lektora
		strcat(jmeno, "\n");
		if (overeniJmena(jmeno, lektori) == 1) {								//Vyhodnoceni, zda lektor existuje
			//printf("Zadali jste spravne jmeno\n");
			overeni = 1;
		}
		else {
			printf("Zadali jste nespravne jmeno\n");
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
		
		if (overeniPredmetu(predmet, &pocetpredmetu, predmety, k, lektori)) {	//Vyhodnoceni, zda ma lektor opravneni editovat predmet
			printf("Predmet je v seznamu");
			k = 1;
			overeni = 1;
		}
		k = 1;
	}
	overeni = 0;
	k = 0;

	int akce = 0;

	while (overeni == 0) {														//Zadani akce, kterou chceme provest
		printf("\nZadejte akci (UKONCIT APLIKACI - 0, BODYC - 1, BODYT - 2, BODYZ - 3, ADD - 4, DEL - 5): ");
		scanf_s("%d", &akce);													//Nacteni akce

		if (akce == 0) {														//Zajisteni spravnosti nacteni akci
			return 0;
		}
		else if (akce >= 1 && akce <= 5) {
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
		printf("\nZadejte jmeno studenta: ");
		scanf_s("%s", jmeno, 100);												//Nacteni jmena studenta
		strcat(jmeno, "\n");
		if ((overeniJmena(jmeno, studenti) and overeniPredmetu(predmet, &pocetpredmetuS, predmetyS, k, studenti) == 1) and (akce >= 1 && akce <= 3)) {								//Vyhodnoceni, zda student existuje a jestli je zapsan v predmetu
			//printf("Zadali jste spravne jmeno\n");
			overeni = 1;
			switch(akce){

			case 1: break;
			case 2: break;
			case 3: break;
			}
		}
		else if(akce == 4 or akce == 5) {
			switch (akce) {

			case 4: break;
			case 5: break;
			}
		}
		else {
			int i;
			printf("Zadali jste nespravne jmeno\n");
			rewind(studenti);
			for (i = 0; i < pocetpredmetuS; i++) {
				strcpy(predmetyS[i], "");
			}
			pocetpredmetuS = 0;
			continue;
		}
	}
	overeni = 0;

	fclose(lektori);
	fclose(studenti);
	return 0;
}

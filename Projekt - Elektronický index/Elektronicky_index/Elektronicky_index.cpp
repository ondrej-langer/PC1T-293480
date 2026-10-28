// Elektronicky_index.cpp : Defines the entry point for the application.
//

#include "Elektronicky_index.h"

using namespace std;

int overeniJmena(char* jmeno, FILE* lektori) {									//Funkce pro overeni nacteneho jmena
	char jeJmeno[100];
	while (fgets(jeJmeno, 100, lektori)) {
		if (strcmp(jmeno, jeJmeno) == 0) {
			return 1;
		}
	}
	return 0;
}

int overeniPredmetu(char* predmet, int *pocetpredmetu, char (*predmety)[50], unsigned short k, FILE* lektori) { //Funkce pro overeni prava na predemet
	char radek[100];
	char* tradek = nullptr;
	int i;

	if (k == 0) {																//Nacteni radku s predmety (pod jmenem) a pocatek deleni
		fgets(radek, 100, lektori);
		tradek = strtok(radek, ";");
	}
	
	while (tradek != NULL) {													//Prepsani jednotlivých zkratek předmětů do pole
		strcpy(predmety[*pocetpredmetu], tradek);
		printf("%s", predmety[*pocetpredmetu]);
		tradek = strtok(NULL, ";");
		(*pocetpredmetu)++;
	}

	for (i = 0; i < *pocetpredmetu; i++) {										//Hledani predmetu v poli predmety
		if (strcmp(predmet, predmety[i]) == 0){
			return 1;
		}
	}
	return 0;
}


int main()
{
	char jmeno[100];
	int overeni = 0;

	FILE* lektori;
	lektori = fopen("lektori.txt", "a+");

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

	fclose(lektori);
	return 0;
}

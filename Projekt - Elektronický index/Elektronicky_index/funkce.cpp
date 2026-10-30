#include <iostream>

int overeniJmena(char* jmeno, FILE* soubor) {									//Funkce pro overeni nacteneho jmena
	char jeJmeno[100];
	while (fgets(jeJmeno, 100, soubor)) {
		if (strcmp(jmeno, jeJmeno) == 0) {
			return 1;
		}
	}
	return 0;
}

int overeniPredmetu(char* predmet, int* pocetpredmetu, char (*predmety)[50], unsigned short k, FILE* soubor) { //Funkce pro overeni prava na predemet
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
		if (strcmp(predmet, predmety[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

void BodyC(char* predmet, char* jmeno, FILE* soubor) {							//Prideleni bodu za cvika
	char radek[100];
	char* tradek = nullptr;
	int body = 0;
	int bodyC, bodyT, bodyZ;
	int celkem;

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	strcat(predmet, "\n");
	rewind(soubor);

	while (fgets(radek, 100, soubor)) {	
		if (strcmp(radek, jmeno) == 0) {										//Hleda jmeno

			fprintf(temp, radek);
			fgets(radek, 100, soubor);

			while (strcmp(radek, predmet) != 0) {								//Dokud nema predmet, kopiruje radky
				fprintf(temp, radek);
				fgets(radek, 100, soubor);
			}
			fprintf(temp, radek);												//Ma predmet, nacte dalsi radek s body, nacte z klavesnice body, prideli
			fgets(radek, 100, soubor);
			tradek = strtok(radek, " ");
			bodyC = strtol(radek, NULL, 10);
			printf("Zadejte pocet bodu k prideleni za cviceni: ");
			scanf_s("%d", &body);
			bodyT = strtol(strtok(NULL, " "), NULL, 10);
			bodyZ = strtol(strtok(NULL, " "), NULL, 10);
			sprintf(radek, "%d %d %d\n", body + bodyC, bodyT, bodyZ);			//Vytvori novy radek s body
			fprintf(temp, radek);												//Vlozi do souboru
			printf("%s", radek);												//Vytiskne body
			celkem = body + bodyC + bodyT + bodyZ;
			if (celkem >= 90) {
				printf("Vysledna znamka z premdetu: A");
			}
			else if (celkem >= 80) {
				printf("Vysledna znamka z predmetu: B");
			}
			else if (celkem >= 70) {
				printf("Vysledna znamka z predmetu: C");
			}
			else if (celkem >= 60) {
				printf("Vysledna znamka z predmetu: D");
			}
			else if (celkem >= 50) {
				printf("Vysledna znamka z predmetu: E");
			}
			else {
				printf("Vysledna znamka z predmetu: F");
			}
		}
		else {
			fprintf(temp, radek);
		}

	}
	fclose(soubor);
	fclose(temp);
	remove("studenti.txt");
	rename("temp.txt", "studenti.txt");
}
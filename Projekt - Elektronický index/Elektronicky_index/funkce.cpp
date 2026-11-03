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

void Body(char* predmet, char* jmeno, FILE* soubor, int akce) {							//Prideleni bodu za cvika
	char radek[100];
	char* tradek = nullptr;
	int body = 0;
	int bodyC, bodyT, bodyZ;
	int celkem;

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	strcat(predmet, "\n");
	rewind(soubor);																//Rewind kvuli naslednymu kopirovani a vytvareni novyho "studenti.txt"

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
			bodyT = strtol(strtok(NULL, " "), NULL, 10);
			bodyZ = strtol(strtok(NULL, " "), NULL, 10);
			switch (akce) {
			case 1:printf("Zadejte pocet bodu k prideleni za cviceni: ");break;
			case 2:printf("Zadejte pocet bodu k prideleni za testy: ");break;
			case 3:printf("Zadejte pocet bodu k prideleni za zkousku: ");break;
			}
			scanf_s("%d", &body);
			celkem = body + bodyC + bodyT + bodyZ;
			
			while ((celkem < 0) or (celkem > 100)) {							//Jestli nepresahly body limit
				printf("Body prevysily hodnotu 100 nebo byly mensi nez 0\n");
				switch (akce) {
				case 1: printf("Zadejte jiny pocet bodu k prideleni za cviceni: ");break;
				case 2: printf("Zadejte jiny pocet bodu k prideleni za testy: ");break;
				case 3: printf("Zadejte jiny pocet bodu k prideleni za zkousku: ");break;
				}
				scanf_s("%d", &body);
				celkem = body + bodyC + bodyT + bodyZ;
			}
			
			switch (akce) {														//Vytvori novy radek s body
			case 1:sprintf(radek, "%d %d %d\n", body + bodyC, bodyT, bodyZ);break;
			case 2:sprintf(radek, "%d %d %d\n", bodyC, body + bodyT, bodyZ);break;
			case 3:sprintf(radek, "%d %d %d\n", bodyC, bodyT, body + bodyZ);break;
			}

			fprintf(temp, radek);												//Vlozi do souboru
			printf("%s", radek);												//Vytiskne body
			
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

void add(char* predmet, char* jmeno, FILE* soubor) {
	char radek[100];
	char pomocny_radek[100];
	char* tradek = nullptr;
	int pocetpredmetu = 0;
	unsigned short k = 1;

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	rewind(soubor);

	while (fgets(radek, 100, soubor)) {
		if (strcmp(radek, jmeno) == 0) {										//Overuje, zda je jmeno v seznamu
			
			fprintf(temp, radek);
			fgets(radek, 100, soubor);
			strcpy(pomocny_radek, radek);
			tradek = strtok(pomocny_radek, " ");
			while (tradek != NULL) {
				if (strcmp(tradek, predmet) == 0) {
					printf("Studen je jiz zapsan v predmetu");
					fprintf(temp, radek);
					k = 0;
				}
				tradek = strtok(NULL, " ");
				pocetpredmetu++;
			}
			if (k == 1) {
				radek[strcspn(radek, "\n")] = '\0';
				strcat(radek, predmet);
				strcat(radek, " \n");
				fprintf(temp, radek);
				for (int i = 0; i < ((pocetpredmetu - 1) * 2); i++) {
					fgets(radek, 100, soubor);
					fprintf(temp, radek);
				}
				strcat(predmet, "\n");
				fprintf(temp, predmet);
				fprintf(temp, "0 0 0\n");
			}
		}
		else {																	//Dodelat kdyz jmeno neni v seznamu!!!
			fprintf(temp, radek);
		}
	}
	fclose(soubor);
	fclose(temp);
	remove("studenti.txt");
	rename("temp.txt", "studenti.txt");
}
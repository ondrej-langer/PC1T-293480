#include <iostream>

int overeniJmena(char* jmeno, FILE* soubor) {									//Funkce pro overeni nacteneho jmena
	char jeJmeno[100];
	char jmeno0[100];

	rewind(soubor);

	if (jmeno[strlen(jmeno) - 1] != '\n') {
		strcat(jmeno, "\n");
	}

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
		tradek = strtok(radek, " \n");
	}
	else {
		tradek = nullptr;
	}

	while (tradek != NULL) {													//Prepsani jednotlivých zkratek předmětů do pole
		strcpy(predmety[*pocetpredmetu], tradek);
		tradek = strtok(NULL, " \n");
		(*pocetpredmetu)++;
	}

	for (i = 0; i < *pocetpredmetu; i++) {										//Hledani predmetu v poli predmety
		if (strcmp(predmet, predmety[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

void Body(char* predmet, char* jmeno, FILE* soubor, int akce) {					//Prideleni bodu
	char radek[100];
	char* tradek = nullptr;
	int body = 0;
	int bodyC, bodyT, bodyZ;
	int celkem;
	char predmet0[100];

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	strcpy(predmet0, predmet);
	strcat(predmet0, "\n");
	rewind(soubor);																//Rewind kvuli naslednymu kopirovani a vytvareni novyho "studenti.txt"

	while (fgets(radek, 100, soubor)) {	
		if (strcmp(radek, jmeno) == 0) {										//Hleda jmeno

			fprintf(temp, radek);
			fgets(radek, 100, soubor);
			fprintf(temp, radek);
			fgets(radek, 100, soubor);

			while (strcmp(radek, predmet0) != 0) {								//Dokud nema predmet, kopiruje radky
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
			printf("\n%s\n", radek);											//Vytiskne body
			printf("------------------------------\n");

			if (celkem >= 90) {
				printf("Vysledna znamka z premdetu: A\n");
				printf("------------------------------\n");
			}
			else if (celkem >= 80) {
				printf("Vysledna znamka z predmetu: B\n");
				printf("------------------------------\n");
			}
			else if (celkem >= 70) {
				printf("Vysledna znamka z predmetu: C\n");
				printf("------------------------------\n");
			}
			else if (celkem >= 60) {
				printf("Vysledna znamka z predmetu: D\n");
				printf("------------------------------\n");
			}
			else if (celkem >= 50) {
				printf("Vysledna znamka z predmetu: E\n");
				printf("------------------------------\n");
			}
			else {
				printf("Vysledna znamka z predmetu: F\n");
				printf("------------------------------\n");
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
	char predmet0[100];

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	rewind(soubor);

	while (fgets(radek, 100, soubor)) {
		if (strcmp(radek, jmeno) == 0) {										//Overuje, zda je jmeno v seznamu
			
			fprintf(temp, radek);
			fgets(radek, 100, soubor);
			strcpy(pomocny_radek, radek);
			tradek = strtok(pomocny_radek, " \n");
			while (tradek != NULL) {											//Prohledava, jestli je student zapsan
				if (strcmp(tradek, predmet) == 0) {
					printf("Studen je jiz zapsan v predmetu\n");
					printf("------------------------------\n");
					fprintf(temp, radek);
					k = 0;
				}
				tradek = strtok(NULL, " \n");
				pocetpredmetu++;
			}
			if (k == 1) {														//Pokud neni student zapsany, zapise se zde
				radek[strcspn(radek, "\n")] = ' ';
				strcat(radek, predmet);
				strcat(radek, "\n");
				fprintf(temp, radek);
				for (int i = 0; i < (pocetpredmetu * 2); i++) {
					fgets(radek, 100, soubor);
					fprintf(temp, radek);
				}
				strcpy(predmet0, predmet);
				strcat(predmet0, "\n");
				fprintf(temp, predmet0);
				fprintf(temp, "0 0 0\n");
				printf("Student byl uspesne pridan do predmetu\n");
				printf("------------------------------\n");
			}
			k = 0;
		}
		else {																	//Kdyz neexistuje jmeno vubec, vytiskne vsechny radky
			fprintf(temp, radek);
		}
	}
	if (k == 1) {																//Vytiskne do souboru nove jmeno a rovnou s predmetem
		fprintf(temp, jmeno);
		strcpy(predmet0, predmet);
		strcat(predmet0, "\n");
		fprintf(temp, predmet0);
		fprintf(temp, predmet0);
		fprintf(temp, "0 0 0\n");
		printf("Student byl uspesne vytvoren a pridan do predmetu\n");
		printf("------------------------------\n");
	}

	fclose(soubor);
	fclose(temp);
	remove("studenti.txt");
	rename("temp.txt", "studenti.txt");
}

void del(char* predmet, char* jmeno, FILE* soubor) {
	char radek[100];
	char pomocny_radek[100];
	strcpy(pomocny_radek, "");
	char* tradek = nullptr;
	int pocetpredmetu = 0;
	char predmet0[100];
	unsigned short k = 0;

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	rewind(soubor);

	while (fgets(radek, 100, soubor)) {
		if (strcmp(radek, jmeno) == 0) {
			fgets(radek, 100, soubor);
			tradek = strtok(radek, " \n");
			while (tradek != NULL) {
				if (strcmp(tradek, predmet) == 0) {
					tradek = strtok(NULL, " \n");
					k = 1;														//Zjisti, ze student je zapsan v predmetu
				}
				else {
					strcat(pomocny_radek, tradek);
					strcat(pomocny_radek, " ");
					tradek = strtok(NULL, " \n");
					pocetpredmetu++;
				}
			}
			if (pocetpredmetu > 0 && k == 1) {
				fprintf(temp, jmeno);
				pomocny_radek[strlen(pomocny_radek) - 1] = '\n';
				fprintf(temp, pomocny_radek);
				fgets(radek, 100, soubor);
				strcpy(predmet0, predmet);
				strcat(predmet0, "\n");
				while (strcmp(radek, predmet0) != 0) {								//Dokud nema predmet, kopiruje radky
					fprintf(temp, radek);
					fgets(radek, 100, soubor);
				}
				fgets(radek, 100, soubor);
				printf("Student byl uspesne vymazan\n");
				printf("------------------------------\n");
			}
			else if (pocetpredmetu == 0 && k == 1) {
				fgets(radek, 100, soubor);
				fgets(radek, 100, soubor);
				printf("Student byl uspesne vymazan\n");
				printf("------------------------------\n");
			}
			else {
				fprintf(temp, jmeno);
				pomocny_radek[strlen(pomocny_radek) - 1] = '\n';
				fprintf(temp, pomocny_radek);
				printf("Student neni zapsan v predmetu\n");
				printf("------------------------------\n");
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

void admin(FILE* soubor) {
	char radek[100];
	char pomocny_radek[100];
	char* tradek = nullptr;
	unsigned short k = 1;
	char jmeno[100];
	char predmet[100];


	printf("Zadejte jmeno lektora pro pridani: ");
	scanf_s("%s", jmeno, 100);
	printf("------------------------------\n");
	strcat(jmeno, "\n");

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	rewind(soubor);

	while (fgets(radek, 100, soubor)) {
		if (strcmp(radek, jmeno) == 0) {										//Overuje, zda je jmeno v seznamu
			fprintf(temp, radek);
			printf("Lektor je jiz pridan\n");
			printf("------------------------------\n");
			printf("Zadejte predmet, do ktereho chcete lektora pridat: ");
			scanf_s("%s", predmet, 100);
			printf("------------------------------\n");
			fgets(radek, 100, soubor);
			strcpy(pomocny_radek, radek);
			tradek = strtok(pomocny_radek, " \n");
			while (tradek != NULL) {											//Prohledava, jestli je lektor zapsan
				if (strcmp(tradek, predmet) == 0) {
					printf("Lektor je jiz pridan do predmetu\n");
					printf("------------------------------\n");
					fprintf(temp, radek);
					k = 0;
				}
				tradek = strtok(NULL, " \n");
			}
			if (k == 1) {														//Pokud neni lektor zapsany, zapise se zde
				radek[strcspn(radek, "\n")] = ' ';
				strcat(radek, predmet);
				strcat(radek, "\n");
				fprintf(temp, radek);
				printf("Lektor byl uspesne pridan do predmetu\n");
				printf("------------------------------\n");
			}
			k = 0;
		}
		else {																	//Kdyz neexistuje jmeno vubec, vytiskne vsechny radky
			fprintf(temp, radek);
		}
	}
	if (k == 1) {																//Vytiskne do souboru nove jmeno a rovnou s predmetem
		printf("\nZadejte predmet, do ktereho chcete lektora pridat: ");
		scanf_s("%s", predmet, 100);
		fprintf(temp, jmeno);
		strcat(predmet, "\n");
		fprintf(temp, predmet);
		printf("Lektor byl uspesne vytvoren a pridan do predmetu");
	}

	fclose(soubor);
	fclose(temp);
	remove("lektori.txt");
	rename("temp.txt", "lektori.txt");
}
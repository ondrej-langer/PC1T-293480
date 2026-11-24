#include "funkce.h"

int overeniJmena(char* jmeno, char* id, FILE* soubor, int jsouLektori) {									//Funkce pro overeni nacteneho jmena
	char radek[DELKA_RETEZCE];
	char heslo[DELKA_RETEZCE];

	rewind(soubor);

	if (jmeno[strlen(jmeno) - 1] != '\n') {
		strcat(jmeno, "\n");
	}
	if (id[strlen(id) - 1] != '\n') {
		strcat(id, "\n");
	}

	while (fgets(radek, DELKA_RETEZCE, soubor)) {
		if (strcmp(jmeno, radek) == 0) {
			fgets(radek, DELKA_RETEZCE, soubor);
			if ((jsouLektori == 1) && (strcmp(id, radek) == 0)) {
				fgets(radek, DELKA_RETEZCE, soubor);
				printf("Zadejte heslo: ");
				scanf_s(DELKA_CTENI, heslo, (unsigned)sizeof(heslo));
				strcat(heslo, "\n");
				printf("------------------------------\n");
				while (strcmp(heslo, radek) != 0) {
					printf("Zadali jste spatne heslo\n");
					printf("------------------------------\n");
					printf("Zadejte heslo: ");
					scanf_s(DELKA_CTENI, heslo, (unsigned)sizeof(heslo));
					strcat(heslo, "\n");
					printf("------------------------------\n");
				}
				printf("Uspesne prihlaseni\n");
				printf("------------------------------\n");

				printf("Dostupne predmety:\n");
				fgets(radek, DELKA_RETEZCE, soubor);
				printf("%s\n", radek);
				rewind(soubor);
				while (fgets(radek, DELKA_RETEZCE, soubor)) {
					if (strcmp(jmeno, radek) == 0) {
						fgets(radek, DELKA_RETEZCE, soubor);
						if (strcmp(id, radek) == 0) {
							fgets(radek, DELKA_RETEZCE, soubor);
							return 1;
						}
					}
				}
			}
			else if (strcmp(id, radek) == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int overeniPredmetu(char* predmet, int* pocetpredmetu, char (*predmety)[DELKA_RETEZCE], unsigned short predmetNacteny, FILE* soubor) { //Funkce pro overeni prava na predemet
	char radek[DELKA_RETEZCE];
	char* tradek = nullptr;
	int i;

	if (predmetNacteny == 0) {																//Nacteni radku s predmety (pod jmenem) a pocatek deleni
		fgets(radek, DELKA_RETEZCE, soubor);
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

void Body(char* predmet, char* jmeno, char* id, FILE* soubor, int akce) {					//Prideleni bodu
	char radek[DELKA_RETEZCE];
	char* tradek = nullptr;
	int body = 0;
	int bodyC, bodyT, bodyZ;
	int celkem;
	char predmet0[DELKA_RETEZCE];

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	strcpy(predmet0, predmet);
	strcat(predmet0, "\n");
	rewind(soubor);																//Rewind kvuli naslednymu kopirovani a vytvareni novyho "studenti.txt"

	while (fgets(radek, DELKA_RETEZCE, soubor)) {
		if (strcmp(radek, jmeno) == 0) {										//Hleda jmeno
			fprintf(temp, radek);
			fgets(radek, DELKA_RETEZCE, soubor);
			if (strcmp(radek, id) == 0) {
				fprintf(temp, radek);
				fgets(radek, DELKA_RETEZCE, soubor);
				fprintf(temp, radek);
				fgets(radek, DELKA_RETEZCE, soubor);

				while (strcmp(radek, predmet0) != 0) {								//Dokud nema predmet, kopiruje radky
					fprintf(temp, radek);
					fgets(radek, DELKA_RETEZCE, soubor);
				}

				fprintf(temp, radek);												//Ma predmet, nacte dalsi radek s body, nacte z klavesnice body, prideli
				fgets(radek, DELKA_RETEZCE, soubor);
				tradek = strtok(radek, " ");
				bodyC = strtol(radek, NULL, 10);
				bodyT = strtol(strtok(NULL, " "), NULL, 10);
				bodyZ = strtol(strtok(NULL, " "), NULL, 10);
				switch (akce) {
				case 1:printf("Zadejte pocet bodu k prideleni za cviceni: ");break;
				case 2:printf("Zadejte pocet bodu k prideleni za testy: ");break;
				case 3:printf("Zadejte pocet bodu k prideleni za zkousku: ");break;
				}
				
				char vstup[DELKA_RETEZCE];
				char* konec = nullptr;
				
				scanf_s(DELKA_CTENI, vstup, (unsigned)sizeof(vstup));
				body = (int)strtol(vstup, &konec, 10);
				celkem = body + bodyC + bodyT + bodyZ;
				if (*konec != '\0') {
					celkem = -1;
				}

				while ((celkem < 0) or (celkem > 100)) {							//Jestli nepresahly body limit
					printf("Body prevysily hodnotu 100 nebo byly mensi nez 0\n");
					switch (akce) {
					case 1: printf("Zadejte jiny pocet bodu k prideleni za cviceni: ");break;
					case 2: printf("Zadejte jiny pocet bodu k prideleni za testy: ");break;
					case 3: printf("Zadejte jiny pocet bodu k prideleni za zkousku: ");break;
					}
					scanf_s(DELKA_CTENI, vstup, (unsigned)sizeof(vstup));
					body = (int)strtol(vstup, &konec, 10);
					celkem = body + bodyC + bodyT + bodyZ;
					if (*konec != '\0') {
						celkem = -1;
					}
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
					printf("Vysledna znamka z predmetu: A\n");
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
		else {
			fprintf(temp, radek);
		}

	}
	fclose(soubor);
	fclose(temp);
	remove("studenti.txt");
	rename("temp.txt", "studenti.txt");
}

void add(char* predmet, char* jmeno, char* id, FILE* soubor) {
	char radek[DELKA_RETEZCE];
	char pomocny_radek[DELKA_RETEZCE];
	char* tradek = nullptr;
	int pocetpredmetu = 0;
	unsigned short jeZapsan = 0;
	unsigned short studentExistuje = 0;
	char predmet0[DELKA_RETEZCE];

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	rewind(soubor);

	while (fgets(radek, DELKA_RETEZCE, soubor)) {
		if (strcmp(radek, jmeno) == 0) {										//Overuje, zda je jmeno v seznamu
			fprintf(temp, radek);
			fgets(radek, DELKA_RETEZCE, soubor);
			if (strcmp(radek, id) == 0) {
				fprintf(temp, radek);
				fgets(radek, DELKA_RETEZCE, soubor);
				strcpy(pomocny_radek, radek);
				tradek = strtok(pomocny_radek, " \n");
				while (tradek != NULL) {											//Prohledava, jestli je student zapsan
					if (strcmp(tradek, predmet) == 0) {
						printf("Student je jiz zapsan v predmetu\n");
						printf("------------------------------\n");
						fprintf(temp, radek);
						jeZapsan = 1;
					}
					tradek = strtok(NULL, " \n");
					pocetpredmetu++;
				}
				if (jeZapsan == 0) {														//Pokud neni student zapsany, zapise se zde
					radek[strcspn(radek, "\n")] = ' ';
					strcat(radek, predmet);
					strcat(radek, "\n");
					fprintf(temp, radek);
					for (int i = 0; i < (pocetpredmetu * 2); i++) {
						fgets(radek, DELKA_RETEZCE, soubor);
						fprintf(temp, radek);
					}
					strcpy(predmet0, predmet);
					strcat(predmet0, "\n");
					fprintf(temp, predmet0);
					fprintf(temp, "0 0 0\n");
					printf("Student byl uspesne pridan do predmetu\n");
					printf("------------------------------\n");
				}
				studentExistuje = 1;
			}
			else {
				fprintf(temp, radek);
			}
		}
		else {																	//Kdyz neexistuje jmeno vubec, vytiskne vsechny radky
			fprintf(temp, radek);
		}
	}
	if (studentExistuje == 0) {																//Vytiskne do souboru nove jmeno a rovnou s predmetem
		fprintf(temp, jmeno);
		fprintf(temp, id);
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

void del(char* predmet, char* jmeno, char* id, FILE* soubor) {
	char radek[DELKA_RETEZCE];
	char pomocny_radek[DELKA_RETEZCE];
	strcpy(pomocny_radek, "");
	char* tradek = nullptr;
	int pocetpredmetu = 0;
	char predmet0[DELKA_RETEZCE];
	unsigned short jeZapsan = 0;

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	rewind(soubor);

	while (fgets(radek, DELKA_RETEZCE, soubor)) {
		if (strcmp(radek, jmeno) == 0) {
			fgets(radek, DELKA_RETEZCE, soubor);
			if (strcmp(radek, id) == 0) {
				fgets(radek, DELKA_RETEZCE, soubor);
				tradek = strtok(radek, " \n");
				while (tradek != NULL) {
					if (strcmp(tradek, predmet) == 0) {
						tradek = strtok(NULL, " \n");
						jeZapsan = 1;														//Zjisti, ze student je zapsan v predmetu
					}
					else {
						strcat(pomocny_radek, tradek);
						strcat(pomocny_radek, " ");
						tradek = strtok(NULL, " \n");
						pocetpredmetu++;
					}
				}
				if (pocetpredmetu > 0 && jeZapsan == 1) {
					fprintf(temp, jmeno);
					fprintf(temp, id);
					pomocny_radek[strlen(pomocny_radek) - 1] = '\n';
					fprintf(temp, pomocny_radek);
					fgets(radek, DELKA_RETEZCE, soubor);
					strcpy(predmet0, predmet);
					strcat(predmet0, "\n");
					while (strcmp(radek, predmet0) != 0) {								//Dokud nema predmet, kopiruje radky
						fprintf(temp, radek);
						fgets(radek, DELKA_RETEZCE, soubor);
					}
					fgets(radek, DELKA_RETEZCE, soubor);
					printf("Student byl uspesne vymazan\n");
					printf("------------------------------\n");
				}
				else if (pocetpredmetu == 0 && jeZapsan == 1) {
					fgets(radek, DELKA_RETEZCE, soubor);
					fgets(radek, DELKA_RETEZCE, soubor);
					printf("Student byl uspesne vymazan\n");
					printf("------------------------------\n");
				}
				else {
					fprintf(temp, jmeno);
					fprintf(temp, id);
					pomocny_radek[strlen(pomocny_radek) - 1] = '\n';
					fprintf(temp, pomocny_radek);
					printf("Student neni zapsan v predmetu\n");
					printf("------------------------------\n");
				}
			}
			else {
				fprintf(temp, jmeno);
				fprintf(temp, radek);
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
	char radek[DELKA_RETEZCE];
	char pomocny_radek[DELKA_RETEZCE];
	char* tradek = nullptr;
	unsigned short prefixPlatny = 0;
	unsigned short predmetJizZapsan = 0;
	unsigned short lektorExistuje = 0;
	char jmeno[DELKA_RETEZCE];
	char heslo[DELKA_RETEZCE];
	char predmet[DELKA_RETEZCE];
	char prefix[DELKA_RETEZCE];
	char seznamprefixu[16][4] = { "BPC", "BPA", "BKC", "BKA", "MPC", "MPA", "MKC", "MKA", "DPC", "DPA", "DKC", "DKA", "XPC", "XPA", "XKC", "XKA" };
	char id[DELKA_RETEZCE];

	FILE* temp;
	temp = fopen("temp.txt", "w+");

	rewind(soubor);

	printf("Zadejte heslo: ");
	scanf_s(DELKA_CTENI, heslo, (unsigned)sizeof(heslo));
	printf("------------------------------\n");
	if (fgets(radek, DELKA_RETEZCE, soubor) == 0) {
		while (strcmp(heslo, "admin") != 0) {
			printf("Zadali jste spatne heslo\n");
			printf("------------------------------\n");
			printf("Zadejte heslo: ");
			scanf_s(DELKA_CTENI, heslo, (unsigned)sizeof(heslo));
			printf("------------------------------\n");
		}
		printf("Uspesne prihlaseni\n");
		printf("------------------------------\n");
		printf("Zadejte nove heslo pro admina: ");
		scanf_s(DELKA_CTENI, heslo, (unsigned)sizeof(heslo));
		strcat(heslo, "\n");
		fprintf(temp, heslo);
		printf("------------------------------\n");
		printf("Nove heslo uspesne nastaveno\n");
		printf("------------------------------\n");
		printf("Neexistuji zadni lektori\n");
		printf("------------------------------\n");
	}
	else {
		strcat(heslo, "\n");
		while (strcmp(heslo, radek) != 0) {
			printf("Zadali jste spatne heslo\n");
			printf("------------------------------\n");
			printf("Zadejte heslo: ");
			scanf_s(DELKA_CTENI, heslo, (unsigned)sizeof(heslo));
			strcat(heslo, "\n");
			printf("------------------------------\n");
		}
		printf("Uspesne prihlaseni\n");
		printf("------------------------------\n");
		printf("Lektori a jejich predmety: \n");
		while (fgets(radek, DELKA_RETEZCE, soubor)) {
			printf(radek);
			fgets(radek, DELKA_RETEZCE, soubor);
			printf(radek);
			fgets(radek, DELKA_RETEZCE, soubor);
			fgets(radek, DELKA_RETEZCE, soubor);
			printf(radek);
			printf("\n");
		}
		printf("------------------------------\n");
	}

	printf("Zadejte jmeno lektora pro pridani: ");
	scanf_s(DELKA_CTENI, jmeno, (unsigned)sizeof(jmeno));
	printf("------------------------------\n");
	strcat(jmeno, "\n");

	printf("Zadejte ID lektora pro pridani: ");
	scanf_s(DELKA_CTENI, id, (unsigned)sizeof(id));
	strcat(id, "\n");
	printf("------------------------------\n");

	rewind(soubor);

	while (fgets(radek, DELKA_RETEZCE, soubor)) {
		if (strcmp(radek, jmeno) == 0) {										//Overuje, zda je jmeno v seznamu
			fprintf(temp, radek);
			fgets(radek, DELKA_RETEZCE, soubor);
			if (strcmp(radek, id) == 0) {
				fprintf(temp, radek);
				printf("Lektor je jiz pridan\n");
				printf("------------------------------\n\n");
				printf("Dostupne prefixy:\n");
				printf("BPC, BPA, BKC, BKA, MPC, MPA, MKC, MKA, DPC, DPA, DKC, DKA, XPC, XPA, XKC, XKA\n\n");
				printf("Zadejte prefix predmetu, do ktereho chcete lektora pridat: ");
				scanf_s(DELKA_CTENI, prefix, (unsigned)sizeof(prefix));
				printf("------------------------------\n");
				while (1) {
					for (int i = 0; i < 16; i++) {
						if (strcmp(prefix, seznamprefixu[i]) == 0) {
							prefixPlatny = 1;
							break;
						}
					}
					if (prefixPlatny == 1) {
						break;
					}
					else {
						printf("Zadali jste spatny prefix\n");
						printf("------------------------------\n");
						printf("Zadejte spravny prefix: ");
						scanf_s(DELKA_CTENI, prefix, (unsigned)sizeof(prefix));
						printf("------------------------------\n");
					}
				}
				strcat(prefix, "-");
				
				printf("Zadejte zkratku predmetu, do ktereho chcete lektora pridat: ");
				scanf_s(DELKA_CTENI, predmet, (unsigned)sizeof(predmet));
				printf("------------------------------\n");

				strcat(prefix, predmet);
				strcpy(predmet, prefix);

				fgets(radek, DELKA_RETEZCE, soubor);
				fprintf(temp, radek);
				fgets(radek, DELKA_RETEZCE, soubor);
				strcpy(pomocny_radek, radek);
				tradek = strtok(pomocny_radek, " \n");
				while (tradek != NULL) {											//Prohledava, jestli je lektor zapsan
					if (strcmp(tradek, predmet) == 0) {
						printf("Lektor je jiz pridan do predmetu\n");
						printf("------------------------------\n");
						fprintf(temp, radek);
						predmetJizZapsan = 1;
						break;
					}
					tradek = strtok(NULL, " \n");
				}
				if (predmetJizZapsan == 0) {														//Pokud neni lektor zapsany, zapise se zde
					radek[strcspn(radek, "\n")] = ' ';
					strcat(radek, predmet);
					strcat(radek, "\n");
					fprintf(temp, radek);
					printf("Lektor byl uspesne pridan do predmetu\n");
					printf("------------------------------\n");
				}
				lektorExistuje = 1;
			}
			else {
				fprintf(temp, radek);
			}

		}
		else {																	//Kdyz neexistuje jmeno vubec, vytiskne vsechny radky
			fprintf(temp, radek);
		}
	}
	if (lektorExistuje == 0) {																//Vytiskne do souboru nove jmeno, id, heslo a rovnou s predmety
		printf("Zadejte nove heslo pro lektora: ");
		scanf_s(DELKA_CTENI, heslo, (unsigned)sizeof(heslo));
		printf("------------------------------\n");

		printf("Dostupne prefixy:\n");
		printf("BPC, BPA, BKC, BKA, MPC, MPA, MKC, MKA, DPC, DPA, DKC, DKA, XPC, XPA, XKC, XKA\n\n");
		printf("Zadejte prefix predmetu, do ktereho chcete lektora pridat: ");
		scanf_s(DELKA_CTENI, prefix, (unsigned)sizeof(prefix));
		printf("------------------------------\n");
		while (1) {
			for (int i = 0; i < 16; i++) {
				if (strcmp(prefix, seznamprefixu[i]) == 0) {
					prefixPlatny = 1;
					break;
				}
			}
			if (prefixPlatny == 1) {
				break;
			}
			else {
				printf("Zadali jste spatny prefix\n");
				printf("------------------------------\n");
				printf("Zadejte spravny prefix: ");
				scanf_s(DELKA_CTENI, prefix, (unsigned)sizeof(prefix));
				printf("------------------------------\n");
			}
		}
		strcat(prefix, "-");

		printf("Zadejte zkratku predmetu, do ktereho chcete lektora pridat: ");
		scanf_s(DELKA_CTENI, predmet, (unsigned)sizeof(predmet));
		strcat(prefix, predmet);
		strcpy(predmet, prefix);
		printf("------------------------------\n");

		fprintf(temp, jmeno);
		fprintf(temp, id);
		strcat(heslo, "\n");
		fprintf(temp, heslo);
		strcat(predmet, "\n");
		fprintf(temp, predmet);
		printf("Lektor byl uspesne vytvoren a pridan do predmetu\n");
		printf("------------------------------\n");
	}

	fclose(soubor);
	fclose(temp);
	remove("lektori.txt");
	rename("temp.txt", "lektori.txt");
}
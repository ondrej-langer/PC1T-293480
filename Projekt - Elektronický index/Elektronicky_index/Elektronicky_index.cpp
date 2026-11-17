// Elektronicky_index.cpp : Defines the entry point for the application.
//
//SMAZAT TOTO - upravit funkce tak, aby sedeli na ID upravu, inspirace ve fci admin

#include "Elektronicky_index.h"
#include "funkce.h"

using namespace std;

int main()
{
	char jmeno[100];
	char id[100] = "";

	FILE* lektori;
	FILE* studenti;

	while(1){
		printf("------------------------------\n");

		lektori = fopen("lektori.txt", "a+");
		studenti = fopen("studenti.txt", "a+");
		// a+: cteni i zapis, kurzor cteni na zacatku, zapis skace na konec

		rewind(lektori);
		rewind(studenti);

		while (1) {																	//Overeni, zda uzivatel (lektor) existuje
			printf("Zadejte sve jmeno: ");
			scanf_s("%s", jmeno, 100);												//Nacteni jmena lektora
			printf("------------------------------\n");
			if (strcmp(jmeno, "admin") != 0) {
				printf("Zadejte sve ID: ");
				scanf_s("%s", id, 100);
				printf("------------------------------\n");
			}
			if (overeniJmena(jmeno, id, lektori, 1) == 1) {							//Vyhodnoceni, zda lektor existuje
				break;
			}
			else if (strcmp(jmeno, "admin\n") == 0) {
				admin(lektori);
				lektori = fopen("lektori.txt", "a+");
			}
			else {
				printf("Zadali jste nespravne jmeno\n");
				printf("------------------------------\n");
				// rewind: vrati kurzor cteni v souboru na zacatek (bajt 0)
				rewind(lektori);
			}
		}

		char predmet[100];
		int pocetpredmetu = 0;
		char predmety[10][50];
		unsigned short k = 0;

		while (1) {														//Zjisteni opravneni na predmet

			printf("Zadejte predmet pro editaci (napr.: BPC-PC1T,MPC-KOM,...): ");
			scanf_s("%s", predmet, 100);											//Nacteni predmetu pro editaci
			printf("------------------------------\n");
			// &pocetpredmetu: predani adresou (pointer), aby funkce menila hodnotu v main
			if (overeniPredmetu(predmet, &pocetpredmetu, predmety, k, lektori)) {	//Vyhodnoceni, zda ma lektor opravneni editovat predmet
				k = 1;
				break;
			}
			else {
				printf("Lektor nema pristup do predmetu\n");
				printf("------------------------------\n");
			}
			k = 1;
		}
		
		k = 0;

		int akce = 0;														//Zhruba odsud TO DAT DO WHILU!!!

		while (1) {
			while (1) {														//Zadani akce, kterou chceme provest
				printf("Dostupne akce:\n");
				printf("UKONCIT APLIKACI = 0\nBODY ZA CVICENI  = 1\nBODY ZA TESTY    = 2\nBODY ZA ZKOUSKU  = 3\nPRIDAT STUDENTA  = 4\nODEBRAT STUDENTA = 5\nODHLASIT SE = 6\n\n");
				printf("Zadejte akci: ");
				// scanf_s u int vyzaduje jen adresu &akce (velikost bufferu se resi jen u textu)
				scanf_s("%d", &akce);													//Nacteni akce

				if (akce == 0) {														//Zajisteni spravnosti nacteni akci
					return 0;
				}
				else if (akce >= 1 && akce <= 6) {										//Ukonceni cyklu pri zadani spravne akce
					break;
				}
				else {
					printf("Zadali jste špatnou akci");
				}
			}

			if (akce == 6) {
				break;
			}

			int pocetpredmetuS = 0;
			char predmetyS[10][50];

			while (1) {														//Overeni, zda student existuje
				printf("------------------------------\n");
				printf("Zadejte jmeno studenta: ");
				scanf_s("%s", jmeno, 100);												//Nacteni jmena studenta
				printf("------------------------------\n");
				printf("Zadejte ID studenta: ");
				scanf_s("%s", id, 100);

				printf("------------------------------\n");
				// zleva doprava (short-circuit): kdyz 1. cast vrati 0, 2. funkce se ani nespusti
				if ((overeniJmena(jmeno, id, studenti, 0) && overeniPredmetu(predmet, &pocetpredmetuS, predmetyS, k, studenti) == 1) && (akce >= 1 && akce <= 3)) {								//Vyhodnoceni, zda student existuje a jestli je zapsan v predmetu
					//printf("Zadali jste spravne jmeno\n");
					Body(predmet, jmeno, studenti, akce);
					studenti = fopen("studenti.txt", "a+");
					break;
				}
				else if ((overeniJmena(jmeno, id, studenti, 0)) && (akce == 5)) {
					del(predmet, jmeno, studenti);
					studenti = fopen("studenti.txt", "a+");
					break;
				}
				else if (akce == 4) {
					// \n kvuli fgets v souboru (strcmp vyzaduje presnou shodu)
					if (jmeno[strlen(jmeno) - 1] != '\n') {
						strcat(jmeno, "\n");
					}
					add(predmet, jmeno, studenti);
					studenti = fopen("studenti.txt", "a+");
					break;
				}
				else {
					int i;
					printf("Zadali jste nespravne jmeno nebo ID\n");
					printf("------------------------------\n");
					rewind(studenti);
					// uvolneni pole: strcpy nastavi na index 0 ukoncovaci znak \0
					for (i = 0; i < pocetpredmetuS; i++) {
						strcpy(predmetyS[i], "");
					}
					pocetpredmetuS = 0;
					break;
				}
			}
		}
	}
	// fclose: zapise vyrovnavaci buffer na disk a uvolni souborovy pointer v OS
	fclose(lektori);										//TYTO CLOSY SMAZAT NEBO PRESUNOUT
	fclose(studenti);
	return 0;
	
}

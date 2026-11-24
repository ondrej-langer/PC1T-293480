#pragma once

#include <iostream>

#define DELKA_RETEZCE 100
#define DELKA_CTENI " %97[^\n]"
#define MAX_PREDMETU 10

int overeniJmena(char* jmeno, char* id, FILE* soubor, int jsouLektori);
int overeniPredmetu(char* predmet, int* pocetpredmetu, char (*predmety)[DELKA_RETEZCE], unsigned short predmetNacteny, FILE* soubor);
void Body(char* predmet, char* jmeno, char* id, FILE* soubor, int akce);
void add(char* predmet, char* jmeno, char* id, FILE* soubor);
void del(char* predmet, char* jmeno, char* id, FILE* soubor);
void admin(FILE* soubor);
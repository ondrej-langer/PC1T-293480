#pragma once

#include <iostream>

#define DELKA_RETEZCE 100
#define DELKA_CTENI " %99[^\n]"

int overeniJmena(char* jmeno, char* id, FILE* soubor, int a);
int overeniPredmetu(char* predmet, int* pocetpredmetu, char (*predmety)[50], unsigned short k, FILE* soubor);
void Body(char* predmet, char* jmeno, char* id, FILE* soubor, int akce);
void add(char* predmet, char* jmeno, char* id, FILE* soubor);
void del(char* predmet, char* jmeno, char* id, FILE* soubor);
void admin(FILE* soubor);
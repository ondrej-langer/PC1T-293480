#pragma once

#include <iostream>

int overeniJmena(char* jmeno, char* id, FILE* soubor, int a);
int overeniPredmetu(char* predmet, int* pocetpredmetu, char (*predmety)[50], unsigned short k, FILE* soubor);
void Body(char* predmet, char* jmeno, char* id, FILE* soubor, int akce);
void add(char* predmet, char* jmeno, FILE* soubor);
void del(char* predmet, char* jmeno, FILE* soubor);
void admin(FILE* soubor);
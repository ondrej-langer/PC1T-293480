#pragma once

#include <iostream>

int overeniJmena(char* jmeno, FILE* soubor);
int overeniPredmetu(char* predmet, int* pocetpredmetu, char (*predmety)[50], unsigned short k, FILE* soubor);
void BodyC(char* predmet, char* jmeno, FILE* soubor);
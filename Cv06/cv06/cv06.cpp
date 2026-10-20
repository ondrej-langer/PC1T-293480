// cv06.cpp : Defines the entry point for the application.
//

#include "cv06.h"

using namespace std;

int pocetPismen(char* text) {
	int i;
	int vysledek = 0;
	for (i = 0; i < strlen(text); i++) {
		if (isalpha(text[i]) >= 1) {
			vysledek++;
		}
	}
	return vysledek;
}

int pocetP(char* text) {
	char* znak;
	int vysledek = 0;
	for (znak = text; *znak != 0; znak++) {
		if (isalpha(*znak)) {
			vysledek++;
		}
	}
	return vysledek;
}

int pocetCislic(char* text) {
	int i;
	int vysledek = 0;
	for (i = 0; i < strlen(text); i++) {
		if (isdigit(text[i]) >= 1) {
			vysledek++;
		}
	}
	return vysledek;
}

int maxDelkaSlova(char* text) {
	int i;
	int pismena = 0;
	int vysledek = 0;
	for (i = 0; i < strlen(text); i++) {
		if (isalpha(text[i]) >= 1) {
			pismena++;
		}
		else if (text[i] == ' ') {
			pismena = 0;
		}
		if (pismena > vysledek) {
			vysledek = pismena;
		}
	}
	return vysledek;
}

int maxDS(char* text) {
	char* znak;
	int pismena = 0;
	int vysledek = 0;
	for (znak = text; *znak != 0; znak++) {
		if (isalpha(*znak)) {
			pismena++;
		}
		else if (*znak == ' ') {
			pismena = 0;
		}
		if (pismena > vysledek) {
			vysledek = pismena;
		}
	}
	return vysledek;
}

int main()
{
	char text[] = "Toto jsou 2 vzorove vety, ktere budou zpracovavany Vasemi funkcemi. Auto Hyundai ix35 ma pres 120 konskych silbgftzftzftzurfitf.";
	
	printf("Text ma %d pismen\n", pocetPismen(text));
	//printf("Text ma %d pismen\n", pocetP(text));
	printf("Text ma %d cislic\n", pocetCislic(text));
	//printf("Nejdelsi slovo ma %d pismen\n", maxDelkaSlova(text));
	printf("Nejdelsi slovo ma %d pismen\n", maxDS(text));
	return 0;
}

// Auta.cpp : Defines the entry point for the application.
//

#include "Hudba.h"

#include <stdio.h>
#include <ctype.h>              // tolower
#include <stdlib.h>				// system

#include "HudbaDB.h"

struct t_hudba* prvni = NULL; // globalni ukazatel na prvni hudbu

void OnAdd()
{
	char my_name[INTERPRET_SIZE];
	char my_album[ALBUM_SIZE];
	int my_year;

	printf("\nInterpret : ");         // dotazeme se na polozky
	scanf_s("%s", my_name, INTERPRET_SIZE);
	while (getchar() != '\n');
	printf("\nNazev alba : ");
	scanf_s("%s", my_album, ALBUM_SIZE);
	while (getchar() != '\n');
	printf("\nRok : ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	add(my_name, my_album, my_year, &prvni);         // volame pridavaci funkci
}

void OnDel()
{
	int my_year;

	printf("\nRok : ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	del(my_year, &prvni);         // volame mazaci funkci
}

void ShowSongs()
{
	struct t_hudba* aktHudba = prvni; // ukazatel na aktualni hudbu
	printf("\n\n");
	while (aktHudba) // prochazeni seznamu
	{
		printf("%s\n%s\n%d\n\n", aktHudba->interpret, aktHudba->album, aktHudba->rok); // tisk radku
		aktHudba = aktHudba->dalsi; // posun na dalsi hudbu
	}
	getchar();
}

void ShowByLetter()
{
	struct t_hudba* aktHudba = prvni; // ukazatel na aktualni hudbu
	printf("\n\n");
	
	char pismeno[2];
	char prvnipismeno;

	printf("\nZadejte pismeno : ");         // dotazeme se na polozky
	scanf_s("%s", pismeno, 2);
	while (getchar() != '\n');

	while (aktHudba) // prochazeni seznamu
	{	
		if (aktHudba->interpret[0] == pismeno[0]) {
			printf("%s\n%s\n%d\n\n", aktHudba->interpret, aktHudba->album, aktHudba->rok);
		}
		aktHudba = aktHudba->dalsi; // posun na dalsi hudbu
	}
	getchar();
}



int main()
{
	char  cmd;

	do
	{
		system("cls");		// smaze obrazovku
		printf("A: Pridat     ");
		printf("D: Smazat     ");
		printf("P: Tisk     ");
		printf("L: Tisk podle prvního písmena     ");
		printf("Q: Konec\n\n");

		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			OnAdd();					// volame pridani
			break;
		case 'd':
			OnDel();					// volame mazani
			break;
		case 'p':
			ShowSongs();
			break;
		case 'l':
			ShowByLetter();
			break;
		}
	} while (cmd != 'q');     // koncime az pri Q
	return 0;
}



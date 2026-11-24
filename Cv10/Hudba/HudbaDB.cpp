#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HudbaDB.h"

void add(char* interpret, char* album, int rok, struct t_hudba** uk_prvni) // pridani auta
{
	struct t_hudba* novaHudba; // ukazatel pro nove vkladane hudba
	struct t_hudba* aktHudba; // ukazatel na aktualni hudbu

	// alokace dynamicke promenne
	novaHudba = (struct t_hudba*)malloc(sizeof(struct t_hudba));

	strcpy_s(novaHudba->interpret, INTERPRET_SIZE, interpret); // naplneni struktury
	strcpy_s(novaHudba->album, ALBUM_SIZE, album);
	novaHudba->rok = rok;
	novaHudba->dalsi = NULL;

	if (*uk_prvni == NULL) // linearni seznam je prazdny
	{
		*uk_prvni = novaHudba;
		return;
	}
	else if (strcmp(novaHudba->interpret, (*uk_prvni)->interpret) < 0) // vlozime na zacatek
	{
		novaHudba->dalsi = *uk_prvni;
		*uk_prvni = novaHudba;
		return;
	}

	aktHudba = *uk_prvni;
	while (aktHudba) // prochazeni seznamu
	{
		if (aktHudba->dalsi == NULL) // jsme na poslednim aute
		{
			aktHudba->dalsi = novaHudba; // pridavame na konec
			return;
		}
		else if (strcmp(novaHudba->interpret, aktHudba->dalsi->interpret) < 0)
		{
			novaHudba->dalsi = aktHudba->dalsi; // vlozime za aktHudba
			aktHudba->dalsi = novaHudba;
			return;
		}
		aktHudba = aktHudba->dalsi; // posun na dalsi Hudba
	}
}

void del(int rok, struct t_hudba** uk_prvni)
{
	struct t_hudba* aktHudba;

	while (*uk_prvni && (*uk_prvni)->rok == rok)
	{
		struct t_hudba* newPrvni = (*uk_prvni)->dalsi;
		free(*uk_prvni);  // uvolneni auta z pameti
		*uk_prvni = newPrvni;
	}

	aktHudba = *uk_prvni;
	while (aktHudba && aktHudba->dalsi) // prochazeni seznamu
	{
		if (aktHudba->dalsi->rok == rok) // hudba je ke smazani
		{
			struct t_hudba* newDalsi = aktHudba->dalsi->dalsi;
			free(aktHudba->dalsi);  // uvolneni auta z pameti
			aktHudba->dalsi = newDalsi;
		}
		aktHudba = aktHudba->dalsi; // posun na dalsi hudbu
	}
}
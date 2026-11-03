// cv08.cpp : Defines the entry point for the application.
//

#include "cv08.h"
#include "langer.h"

using namespace std;

int main()
{
	double zacatek1[] = { 1.5,1.5,1.5 };
	double konec1[] = { 2.8,2.8,4.8 };
	double zacatek2[] = { 1.6,3.6,2.6 };
	double konec2[] = { 2.0,7.5,7.5 };
	double prunik_zacatek;
	double prunik_konec;
	int i;

	for (i = 0; i < 3; i++) {
		
		
		if (prunik(zacatek1[i], konec1[i], zacatek2[i], konec2[i], &prunik_zacatek, &prunik_konec)) {
			printf("Vysledek pro %d. interval: 1	interval pruniku: (%lf, %lf)\n", i+1, prunik_zacatek, prunik_konec);
		}
		else {
			printf("Vysledek pro %d. interval: 0\n", i+1);
		}
	}

	double zacatek3;
	double konec3;
	double zacatek4;
	double konec4;

	printf("Zadejte zacatek prvniho intervalu: ");
	scanf_s("%lf", &zacatek3);
	printf("Zadejte konec prvniho intervalu: ");
	scanf_s("%lf", &konec3);
	printf("Zadejte zacatek druheho intervalu: ");
	scanf_s("%lf", &zacatek4);
	printf("Zadejte konec druheho intervalu: ");
	scanf_s("%lf", &konec4);

	if (bonusPrunik(zacatek3, konec3, zacatek4, konec4, &prunik_zacatek, &prunik_konec)) {
		printf("Vysledek pro dvojici intervalu: 1	interval pruniku: (%lf, %lf)\n", prunik_zacatek, prunik_konec);
	}
	else {
		printf("Vysledek pro dvojici intervalu: 0\n");
	}

	return 0;
}

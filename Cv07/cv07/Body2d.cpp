#include <math.h>
#include <limits.h>
#include <stdio.h>

int indexNejblizsi(int velikost, int (*poleBodu)[2], int referencniX, int referencniY){
	int minVzdalenost = INT_MAX;
	int i, vysledek = -1;
	double dx, dy, vzdalenost;

	for (i = 0; i < velikost; i++) {
		dx = poleBodu[i][0] - referencniX;
		dy = poleBodu[i][1] - referencniY;
		vzdalenost = sqrt(dx * dx + dy * dy);
		if (vzdalenost < minVzdalenost) {
			minVzdalenost = vzdalenost;
			vysledek = i;
		}
	}
	return vysledek;
}

double prumernaVzdalenost(int velikost, int (*poleBodu)[2], int referencniX, int referencniY) {
	int i;
	double dx, dy, vzdalenost, soucet = 0;

	for (i = 0; i < velikost; i++) {
		dx = poleBodu[i][0] - referencniX;
		dy = poleBodu[i][1] - referencniY;
		vzdalenost = sqrt(dx * dx + dy * dy);
		soucet = vzdalenost + soucet;
		
	}
	return (soucet/velikost);
}

void bodyVBlizkosti(int maxVzdalenost, int velikost, int(*poleBodu)[2], int referencniX, int referencniY) {
	int i;
	double dx, dy, vzdalenost;

	printf("\nBody v blizkosti: ");

	for (i = 0; i < velikost; i++) {
		dx = poleBodu[i][0] - referencniX;
		dy = poleBodu[i][1] - referencniY;
		vzdalenost = sqrt(dx * dx + dy * dy);
		if (vzdalenost <= maxVzdalenost){
			printf("Bod [%d, %d] ", poleBodu[i][0], poleBodu[i][1]);
		}

	}
}
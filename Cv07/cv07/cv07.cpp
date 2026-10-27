// cv07.cpp : Defines the entry point for the application.
//

#include "cv07.h"
#include "Body2d.h"

using namespace std;


#define POCET_BODU 10

int main(){
	
	int x, y, maxVzdalenost;
	int velikost = 10;

	int body[POCET_BODU][2] = { 5, 10,
	-14, 2,
	45, 4,
	-9, 8,
	58, -3,
	47, 5,
	-18, -86,
	75, 7,
	-25, 51,
	17, 98 };

	printf("Zadejte souradnici x referencniho bodu: ");
	scanf_s("%d", &x);

	printf("\nZadejte souradnici y referencniho bodu: ");
	scanf_s("%d", &y);

	printf("\nZadejte max. vzdalenost od referencniho bodu: ");
	scanf_s("%d", &maxVzdalenost);

	printf("\nNejblizsi bod je: [%d, %d]", body[indexNejblizsi(velikost, body, x, y)][0], body[indexNejblizsi(velikost, body, x, y)][1]);
	printf("\nPrumerna vzdalenost od referencniho bodu je: %lf", prumernaVzdalenost(velikost, body, x, y));

	bodyVBlizkosti(maxVzdalenost, velikost, body, x, y);

	return 0;
}

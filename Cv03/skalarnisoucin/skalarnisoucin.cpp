// skalarnisoucin.cpp : Defines the entry point for the application.
//

#include "skalarnisoucin.h"

using namespace std;

int main()
{
	int ux;
	int uy;
	int vx;
	int vy;
	int sksoucin;

	printf("Zadejte souradnice prvniho vektoru oddelene mezerou (x y): ");
	scanf_s("%d %d", &ux, &uy);

	printf("Zadejte souradnice druheho vektoru oddelene mezerou (x y): ");
	scanf_s("%d %d", &vx, &vy);

	sksoucin = ux * vx + uy * vy;

	printf("Skalarni soucin je: %d", sksoucin);

	return 0;
}

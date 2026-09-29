// Boure.cpp : Defines the entry point for the application.
//

#include "Boure.h"

using namespace std;

int main()
{
	const double rychlost_svetla = 340;
	double cas;
	double vzdalenost;

	printf("Zadejte cas (s): ");
	scanf_s("%lf", &cas);

	vzdalenost = cas * rychlost_svetla;

	printf("Vzdalenost je: %lf", vzdalenost);

	return 0;
}

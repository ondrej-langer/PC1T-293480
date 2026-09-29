// Boure.cpp : Defines the entry point for the application.
//

#include "Boure.h"

using namespace std;

int main()
{
	double rychlost_svetla = 340;
	double cas;
	double vzdalenost;
	
	printf("Zadej cas (s): ");
	scanf_s("%lf", &cas);

	vzdalenost = cas * rychlost_svetla;
	printf("Vzdalenost: %lf", vzdalenost);

	return 0;
}

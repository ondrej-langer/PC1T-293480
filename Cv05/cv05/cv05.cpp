// cv05.cpp : Defines the entry point for the application.
//

#include "cv05.h"

using namespace std;

void soucet(double a[3], double b[3], double c[3]) { // muze byt double a/b/c[prazdno] -> compiler potrebuje vedet ze jde o pole
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}

double velikost(double a[3]) {
	return sqrt((a[0]*a[0]) + (a[1]*a[1]) + (a[2] * a[2]));
}

double skalarniSoucin(double a[3], double b[3]) {
	return ((a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]));
}

void vektorovySoucin(double a[3], double b[3], double c[3]) {
	c[0] = (a[1] * b[2]) - (a[2] * b[1]);
	c[1] = (a[2] * b[0]) - (a[0] * b[2]);
	c[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

int main()
{
	double a[3], b[3], c[3];

	printf("Zadejte souradnice vektoru a (3 cisla oddelene carkou): ");
	scanf_s("%lf, %lf, %lf", &a[0], &a[1], &a[2]);

	printf("\nZadejte souradnice vektoru b (3 cisla oddelene carkou): ");
	scanf_s("%lf, %lf, %lf", &b[0], &b[1], &b[2]);

	soucet(a, b, c);
	printf("\nSoucet a + b: (%lf, %lf, %lf)\n", c[0], c[1], c[2]);

	printf("\nVelikost vektoru a: %lf\n", velikost(a));

	printf("\nSkalarni soucin a*b: %lf\n", skalarniSoucin(a,b));

	vektorovySoucin(a, b, c);
	printf("\nVektorovy soucin a x b: (%lf, %lf, %lf)\n", c[0], c[1], c[2]);

	return 0;
}

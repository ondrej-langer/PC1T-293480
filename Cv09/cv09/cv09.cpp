// cv09.cpp : Defines the entry point for the application.
//

#include "cv09.h"
#include "vektory.h"

using namespace std;

int main()
{
	struct vector3d u, v;
	enum typOperace op;

	printf("Zadejte vektor u (x,y,z) oddelene carkou: ");
	scanf_s("%lf,%lf,%lf", &u.x, &u.y, &u.z);

	printf("Zadejte vektor v (x,y,z) oddelene carkou: ");
	scanf_s("%lf,%lf,%lf", &v.x, &v.y, &v.z);

	printf("Zadejte typ operace (1 - soucet, 2 - skalarni soucin, 3 - vektorovy soucin): ");
	scanf_s("%d", &op);

	tisk(compVec(u, v), operace(u, v, op), op);

	return 0;
}

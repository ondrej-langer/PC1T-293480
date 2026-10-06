// cv04.cpp : Defines the entry point for the application.
//

#include "cv04.h"

//prejmenoval jsem zdrojove soubory, proto je nazev exe prestupny_rok

using namespace std;

int jePrestupny(int rok) {
	if (((rok % 4 == 0) and (rok % 100 != 0)) or (rok % 400 == 0)){
		return 1;
	}
	else {
		return 0;
	}
}

int jeLichy(int cislo) {
	return(cislo % 2 == 1);
}


int main()
{
	printf("%d\t%d\n",1000, jePrestupny(1000));
	printf("%d\t%d\n",2000, jePrestupny(2000));
	printf("%d\t%d\n",2002, jePrestupny(2002));
	printf("%d\t%d\n",2012, jePrestupny(2012));
	printf("%d\t%d\n",2022, jePrestupny(2022));
	printf("%d\t%d\n",2200, jePrestupny(2200));

	printf("%d\t%d\n", 1, jeLichy(1));
	printf("%d\t%d\n", 2, jeLichy(2));
	printf("%d\t%d\n", 3, jeLichy(3));
	printf("%d\t%d\n", 4, jeLichy(4));
	printf("%d\t%d\n", 5, jeLichy(5));
	printf("%d\t%d\n", 6, jeLichy(6));
	return 0;
}

// prestupny_rok.cpp : Defines the entry point for the application.
//

#include "prestupny_rok.h"

using namespace std;

int jePrestupny(int rok) {
	if (((rok % 4 == 0) and (rok % 100 != 0)) or (rok % 400 == 0)){
		return 1;
	}
	else {
		return 0;
	}
}

int main()
{
	printf("%d\t%d\n",1000, jePrestupny(1000));
	printf("%d\t%d\n",2000, jePrestupny(2000));
	printf("%d\t%d\n",2002, jePrestupny(2002));
	printf("%d\t%d\n",2012, jePrestupny(2012));
	printf("%d\t%d\n",2022, jePrestupny(2022));
	printf("%d\t%d\n",2200, jePrestupny(2200));
	return 0;
}

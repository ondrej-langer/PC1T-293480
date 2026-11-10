#include <iostream>
#include <math.h>
#include "vektory.h"


struct vector3d operace(struct vector3d u, struct vector3d v, enum typOperace typ) {
	struct vector3d w;
	
	switch (typ) {
	case soucet: 
		w.x = u.x + v.x;
		w.y = u.y + v.y;
		w.z = u.z + v.z;
		return w;
	case skalarniSoucin:
		w.z = (u.x * v.x + u.y * v.y + u.z * v.z);
		return w;
	case vektorovySoucin:
		w.x = (u.y * v.z - u.z * v.y);
		w.y = (u.z * v.x - u.x * v.z);
		w.z = (u.x * v.y - u.y * v.x);
		return w;
	}


}

int compVec(struct vector3d u, struct vector3d v) {
	double velikostu = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	double velikostv = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	if (velikostu == velikostv) {
		return 0;
	}
	else if (velikostu > velikostv) {
		return 1;
	}
	else{
		return -1;
	}
}

void tisk(int comp, struct vector3d w, enum typOperace typ) {
	
	switch (comp) {
	case -1: 
		printf("|u| < |v|\n");
		break;
	case 0:
		printf("|u| = |v|\n");
		break;
	case 1:
		printf("|u| > |v|\n");
		break;
	}


	switch(typ){
	case soucet:
		printf("u + v = w = (%lf, %lf, %lf)\n", w.x, w.y, w.z);
		printf("|w| = %.3lf", sqrt(w.x * w.x + w.y * w.y + w.z * w.z));
		break;
	
	case skalarniSoucin:
		printf("u * v = %lf", w.z);
		break;

	case vektorovySoucin:
		printf("u x v = w = (%lf, %lf, %lf)\n", w.x, w.y, w.z);
		printf("|w| = %.3lf", sqrt(w.x*w.x+w.y*w.y+w.z*w.z));
		break;
	}

}
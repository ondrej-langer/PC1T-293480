#pragma once

enum typOperace { soucet = 1, skalarniSoucin, vektorovySoucin };

struct vector3d
{
	double x;
	double y;
	double z;
};

struct vector3d operace(struct vector3d u, struct vector3d v, enum typOperace typ);

void tisk(int comp, struct vector3d u, enum typOperace typ);

int compVec(struct vector3d u, struct vector3d v);
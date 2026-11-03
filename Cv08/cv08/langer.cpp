
int prunik(double zacatek1, double konec1, double zacatek2, double konec2, double* vysl_zacatek, double* vysl_konec) {
	
	
	if (konec1 < zacatek2) {
		return 0;
	}
	else {
		*vysl_zacatek = zacatek2;
		if (konec2 <= konec1) {
			*vysl_konec = konec2;
			return 1;
		}
		else {
			*vysl_konec = konec1;
			return 1;
		}
	}

}

int bonusPrunik(double zacatek1, double konec1, double zacatek2, double konec2, double* vysl_zacatek, double* vysl_konec) {
	double pomocna;

	if (zacatek1 > konec1) {
		pomocna = zacatek1;
		zacatek1 = konec1;
		konec1 = pomocna;
	}
	if (zacatek2 > konec2) {
		pomocna = zacatek2;
		zacatek2 = konec2;
		konec2 = pomocna;
	}

	if (zacatek1 > zacatek2) {
		pomocna = zacatek2;
		zacatek2 = zacatek1;
		zacatek1 = pomocna;
		pomocna = konec2;
		konec2 = konec1;
		konec1 = pomocna;
	}

	if (konec1 < zacatek2) {
		return 0;
	}
	else {
		*vysl_zacatek = zacatek2;
		if (konec2 <= konec1) {
			*vysl_konec = konec2;
			return 1;
		}
		else {
			*vysl_konec = konec1;
			return 1;
		}
	}

}
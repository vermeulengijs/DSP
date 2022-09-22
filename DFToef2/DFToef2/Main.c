#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <STDLib.h>
void GENERATE_SINEWAVE(double, double, double, double, int, double*);
void ADD_WAVES(double*, double*, int, double*);
void DFT(double *, double *, double *, double *, double *, int);
void PrintArray(double *, int);
void Windowing(double *, double, char, double *);
void zeropadding(double *, double *, double, double);
double VOLGENDE2MACHT(int);
// int argc # parameters ,  char *arg[] de parameters 
int main(int argc, char * argv[])
{
	double *x1;       // data
	double *x2;       // data
	double *xadd;       // data
	
	double *X_Re;    // reeel deel
	double *X_Im;    // imaginair deel
	double *X_Mag;	 // magnitude
	double *X_Phase; // fase

	int N = 8; // aantal
	double F1 = 1000, F2 = 2000;	// frequenties
	double Fs = 8000;				// sample frequentie
	double Phase1 = 0, Phase2 = 3 * M_PI / 4; // fase
	double amplitude1 = 1, amplitude2 = 0.5;  // amplitude

	// windowing

	char windowtype;
	double *y;       // data
	// zeropadding

	double newlen;
	double *yout;

	// geheugen alocatie
	x1 = calloc(N, sizeof(double));
	x2 = calloc(N, sizeof(double));
	y = calloc(N, sizeof(double));
	xadd = calloc(N, sizeof(double));


	// Sinuswave genereren en in x schrijven

	GENERATE_SINEWAVE(amplitude1, F1, Fs, Phase1, N, xadd);
	//GENERATE_SINEWAVE(amplitude2, F2, Fs, Phase2, N, x2);
	//PrintArray(x1, N); // x printen in de console
	//PrintArray(x2, N);
	//ADD_WAVES(x1, x2, N, xadd);
	PrintArray(xadd, N);

	// windowing

	printf("Welk window type wilt u gebruiken ?");
	scanf("%c", &windowtype);
	printf("\n");
	Windowing(xadd, N, windowtype, y);
	PrintArray(y, N);
	printf("- - -\n");

	// zeropadding
	newlen = VOLGENDE2MACHT(N);
	printf("%.2lf \n", newlen);
	printf("- - -\n");
	yout = calloc(newlen, sizeof(double));
	PrintArray(yout, newlen);
	printf("- - -\n");
	zeropadding(y, yout, newlen,N);
	PrintArray(yout, newlen);
	printf("- - -\n");

	// DFT
	// geheugen allocatie
	X_Re = calloc(newlen, sizeof(double));
	X_Im = calloc(newlen, sizeof(double));
	X_Mag = calloc(newlen, sizeof(double));
	X_Phase = calloc(newlen, sizeof(double));
	//DFT berekening
	DFT(yout, X_Re, X_Im, X_Mag, X_Phase, newlen);
	printf("---X_RE---\n");
	PrintArray(X_Re, newlen);
	printf("---X_Im---\n");
	PrintArray(X_Im, newlen);
	printf("---X_Mag---\n");
	PrintArray(X_Mag, newlen);
	printf("---X_Phase---\n");
	PrintArray(X_Phase, newlen);

	getchar();
}


void DFT(double * x, double * X_Re, double * X_Im, double * X_Mag, double * X_Phase, int N)
{
	for (int m = 0; m <= N - 1; m++)
	{
		for (int n = 0; n <= N - 1; n++)
		{
			X_Re[m] += x[n] * cos(2 * M_PI* n*m / N);
			X_Im[m] += -x[n] * sin(2 * M_PI* n*m / N);
		}
		X_Mag[m] = sqrt((X_Re[m] * X_Re[m]) + (X_Im[m] * X_Im[m]));
		X_Phase[m] = atan2(X_Im[m], X_Re[m]);
		// van radialen naar graden + als er geen magnitude is , maakt de fase ook niet uit
		if (X_Mag[m] > 0.001)
		{
			X_Phase[m] = X_Phase[m] / M_PI * 180;
		}
		else
		{
			X_Phase[m] = 0;
		}

	}

}


void GENERATE_SINEWAVE(double a, double F, double Fs, double pmi, int n, double* Out)
{
	for (int i = 0; i < n; i++)
	{
		Out[i] = a*(sin((2 * M_PI*F*(i / Fs)) + pmi)); // returns a double
	}

}

void ADD_WAVES(double* Sequence1, double* Sequence2, int length, double* out)
{
	for (int i = 0; i < length; i++)
	{
		out[i] = Sequence1[i] + Sequence2[i];
	}
}


void PrintArray(double * array, int aantal)
{
	for (int n = 0; n < aantal; n++)
	{
		printf("%.2lf", array[n]);
		printf("\n");
	}

}
void Windowing(double * x, double xlen , char windowtype, double * y)
{
	double *w;
	w = calloc(xlen, sizeof(double));
	int Keuze =0;
	//PrintArray(w, xlen); DEBUG
	switch (windowtype)
	{
	case '1': 
		printf("Gekozen windowtype = rechthoekig \n");
		Keuze = 1;
		break;
	case '2':
		printf("Gekozen windowtype = driehoekig \n");
		Keuze = 2;
		break;
	case '3':
		printf("Gekozen windowtype = Hanning \n");
		Keuze = 3;
		break;
	case '4':
		printf("Gekozen windowtype = Hamming \n");
		Keuze = 4;
		break;
	case '5':
		printf("Gekozen windowtype = blackman \n");
		Keuze = 5;
		break;
	default :
		printf("Verkeerde Keuze\n");
	}
	for (int n = 0; n <= xlen - 1; n++)
	{
		if (Keuze == 1)
		{
			w[n] = 1;
		}
		if (Keuze == 2)
		{
			if (n <= xlen / 2)
			{
				w[n] = (n / (xlen / 2));
			}
			else
			{
				w[n] = 2 - (n / (xlen - 2));
			}
		}
		if (Keuze == 3)
		{
			w[n] = 0.5 - 0.5* cos(2 * M_PI*n / (xlen - 1));
		}
		if (Keuze == 4)
		{
			w[n] = 0.54 - 0.46* cos(2 * M_PI*n / (xlen - 1));
		}
		if (Keuze == 5)
		{
			w[n] = 0.42 - 0.5*cos(2 * M_PI *n / (xlen - 1)) + 0.08*cos(4 * M_PI* n / (xlen - 1));
		}
		y[n] = w[n] * x[n];
	}
}
void zeropadding(double *y, double *yout, double newlen, double xlen)
{
	int n = 0;
	while (n <= xlen)
	{ 
		yout[n] = y[n];
		n++;
	}
		
}
double VOLGENDE2MACHT(int n)
{
	double k = 1;
	while (k <= n)
		k *= 2;
	return k;
}
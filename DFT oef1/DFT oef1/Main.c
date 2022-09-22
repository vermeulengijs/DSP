#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <STDLib.h>
void GENERATE_SINEWAVE(double, double, double, double, int, double*);
void ADD_WAVES(double*, double*, int, double*);
void DFT( double *,  double *,  double *, double *, double *, int);
void PrintArray(double *, int);
// int argc # parameters ,  char *arg[] de parameters 
int main(int argc, char * argv[])
{
	double *x1;       // data
	double *x2;       // data
	double *out;       // data
	double *X_Re;    // reeel deel
	double *X_Im;    // imaginair deel
	double *X_Mag;	 // magnitude
	double *X_Phase; // fase
	int N = 8; // aantal
	double F1 = 1000;
	double Fs = 8000;
	double Phase1 = 0;
	double amplitude1 = 1;
	double F2 = 2000;
	double Phase2 = 3*M_PI/4;
	double amplitude2 = 0.5;


	// geheugen alocatie
	x1 = calloc(N, sizeof(double ));
	x2 = calloc(N, sizeof(double));
	out = calloc(N, sizeof(double));
	X_Re = calloc(N, sizeof(double ));
	X_Im = calloc(N, sizeof(double ));
	X_Mag = calloc(N, sizeof(double ));
	X_Phase = calloc(N, sizeof(double ));
	// Sinuswave genereren en in x schrijven
	GENERATE_SINEWAVE(amplitude1, F1, Fs, Phase1, N, x1);
	GENERATE_SINEWAVE(amplitude2, F2, Fs, Phase2, N, x2);
	ADD_WAVES(x1, x2, N, out);
	PrintArray(x1, N); // x printen in de console
	PrintArray(x2, N);

	DFT(out, X_Re, X_Im, X_Mag, X_Phase, N);
	printf("-X_RE-\n");
	PrintArray(X_Re, N);
	printf("-X_Im-\n");
	PrintArray(X_Im, N);
	printf("-X_Mag-\n");
	PrintArray(X_Mag, N);
	printf("-X_Phase-\n");
	PrintArray(X_Phase, N);


	getchar();
}
void DFT(double * x, double * X_Re, double * X_Im, double * X_Mag, double * X_Phase, int N)
{
	for (int m = 0; m <= N - 1; m++)
	{
		for (int n = 0; n <= N - 1; n++)
		{
			X_Re[m] += x[n] * cos(2 * M_PI* n*m / N);
			X_Im[m] += - x[n] * sin(2 * M_PI* n*m / N);
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
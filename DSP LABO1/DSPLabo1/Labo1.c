// DSP Labo oefening 1
#include <stdio.h>
#include <math.h>
#include <STDLib.h>
#define Pi 4*atan(1.0) // atan = bgtan()

void GENERATE_SINEWAVE(double, double, double, double, int, double*);
void ADD_WAVES(double*, double*, int, double*);
void Printarray(double *, double);
// int argc # parameters ,  char *argv[] parameters 
int main(int argc, char * arg[])
{
	double A1 = 1, f1 = 1000, fs =8000 , Pmi1 = 0; // amplitude , input frequency , sampling frequency , phase
	double A2 = 0.5, f2 = 2000, Pmi2 = 3*Pi/4;
	int N = 8; // number of samples, length of the samples
	double *out; // pointer to the output sequence
	double *sequence1;
	double *sequence2;
	out = (double *)calloc(N, sizeof(double));
	sequence1 = (double *)calloc(N, sizeof(double));
	sequence2 = (double *)calloc(N, sizeof(double));
	GENERATE_SINEWAVE(A1, f1, fs, Pmi1, N, sequence1);
	GENERATE_SINEWAVE(A2, f2, fs, Pmi2, N, sequence2);
	ADD_WAVES(sequence1,sequence2,N,out);
	Printarray(sequence1, N);
	Printarray(sequence2, N);
	Printarray(out, N);
	

	getchar();
}

void GENERATE_SINEWAVE(double a, double F, double Fs, double pmi, int n, double* Out)
{
	for (int i =0; i < n; i++)
	{
		Out[i] = a*(sin( (2 * Pi*F*(i / Fs) ) + pmi)); // returns a double
	}

}
void ADD_WAVES(double* Sequence1, double* Sequence2, int length, double* out)
{
	for (int i = 0; i < length; i++)
	{
		out[i] = Sequence1[i] + Sequence2[i];
	}
}
void Printarray(double *x, double aantal)
{
	for (int i = 0; i < aantal; i++)
	{
		printf("%d : %.2lf\t", i, x[i]);
		//printf("\n");
	}
	printf("\n");
}
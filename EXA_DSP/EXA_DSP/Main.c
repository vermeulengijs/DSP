#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 4*atan(1.0)

void GENERATE_SINEWAVE(double *, double, double, double, double, double);
void PrintWave(double *, double);
void ADD_WAVES(double*, double *, double *, double);
int main(int argc, char *arg[])
{
	double *sequence1;
	double *sequence2;
	double *out;
	double A1 = 1; // amplitude
	double A2 = 0.5; //amplitude
	double f1 = 1000; // frequency
	double f2 = 2000;
	double pse1 = 0; // phase
	double pse2 = 3 * PI / 4;
	double fs = 8000; // sample frequency
	double N = 8 ; // #DFT points

	sequence1 = calloc(N, sizeof(double));
	sequence2 = calloc(N, sizeof(double));
	out = calloc(N, sizeof(double));
	GENERATE_SINEWAVE(sequence1, A1, f1, pse1, fs, N);
	GENERATE_SINEWAVE(sequence2, A2, f2, pse2, fs, N);
	PrintWave(sequence1, N);
	PrintWave(sequence2, N);
	ADD_WAVES(sequence1, sequence2, out, N);
	PrintWave(out, N);

	getchar();
}
void GENERATE_SINEWAVE(double *x, double A, double f, double pse, double fs, double N)
{
	for ( int n = 0;n < N; n++)
	{
		x[n] = A * sin(2 * PI*f* (n / fs) + pse);

	}
}
void PrintWave(double *x, double N)
{
	for (int a = 0; a < N; a++)
	{
		printf("%.2lf\n", x[a]);
	}
	printf("\n");
}
void ADD_WAVES(double * sequence1, double * sequence2, double * out, double N)
{
	for (int i = 0; i < N; i++)
	{
		out[i] = sequence1[i] + sequence2[i];
	}
}
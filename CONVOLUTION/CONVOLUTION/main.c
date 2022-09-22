#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size(x) (sizeof(x) / sizeof(double))

void convolution(double[], double, double[], double, double *, double);
void _2Dconvolution(double **, double, double, double **, double, double **);
void Printarray(double *, double);
void Print2Darray(double **, double, double);
void Fill2Darray(double **, double, double);
void DFT(double *, double *, double *, double *, double *, double);
void GENERATE_SINEWAVE(double, double, double, double, double, double *);
void add_waves(double *,double *, double *, double);
int main(char argc, char argv[])
{
	// convolutie
	/*
	double x[] = { 1, 2, 3 };
	double h[] = { 1, 2 };
	double *y;
	double xlen, hlen, ylen;
	xlen = size(x);
	hlen = size(h);
	printf("de lengte van x : %.0lf\n",xlen);
	printf("de lengte van h : %.0lf\n", hlen);

	ylen = xlen + hlen - 1;
	y = calloc(ylen, sizeof(double));
	convolution(x, xlen, h, hlen, y, ylen);
	*/
	// 2d convolutie
	/*
	double **y, **x, **h;
	double aantalx, aantalh;

	printf("Geef de grote van x :");
	scanf("%lf", &aantalx);
	printf("\nGeef de grote van h :");
	scanf("%lf", &aantalh);
	printf("\n");
	y = calloc(aantalx, sizeof(double *));
	x = calloc(aantalx, sizeof(double *));
	h = calloc(aantalh, sizeof(double *));
	for (int i = 0; i < aantalx; i++)
	{
		y[i] = calloc(aantalx, sizeof(double));
		x[i] = calloc(aantalx, sizeof(double));
	}
	for (int i = 0; i < aantalh; i++)
	{
		h[i] = calloc(aantalh, sizeof(double));
	}
	printf("DEBUG1\n");
	Fill2Darray(x, aantalx, aantalx);
	Print2Darray(x, aantalx, aantalx);
	Fill2Darray(h, aantalh, aantalh);
	Print2Darray(h, aantalh, aantalh);

	_2Dconvolution(x, aantalx, aantalx, h, aantalh, y);
	Print2Darray(y, aantalx, aantalx);
	*/
	// dft

	double *wave1;
	double *wave2;
	double *som;
	double *x_re;
	double *x_phase;
	double *x_im;
	double *x_mag;
	double N = 8; // we nemen een 8-point dft
	double A = 1;
	double f = 1000;
	double fs = 8000;
	double phase = 0;
	double A2 = 0.5;
	double f2 = 2000;
	double phase2 = 3 * M_PI / 4;

	wave1 = calloc(N, sizeof(double));
	wave2 = calloc(N, sizeof(double));
	som = calloc(N, sizeof(double));
	x_re = calloc(N, sizeof(double));
	x_im = calloc(N, sizeof(double));
	x_mag = calloc(N, sizeof(double));
	x_phase = calloc(N, sizeof(double));
	GENERATE_SINEWAVE(A, f, fs, N, phase, wave1);
	GENERATE_SINEWAVE(A2, f2, fs, N, phase2, wave2);
	Printarray(wave1, N);
	Printarray(wave2, N);
	add_waves(som, wave1, wave2, N);
	Printarray(som, N);
	DFT(som, x_re, x_mag, x_im, x_phase, N);
	printf("---x_re---\n");
	Printarray(x_re, N - 1);
	printf("---x_mag---\n");
	Printarray(x_mag, N - 1);
	printf("---x_im---\n");
	Printarray(x_im, N - 1);
	printf("---x_phase---\n");
	Printarray(x_phase, N - 1);

}

void convolution(double x[], double xlen, double h[], double hlen, double *y, double ylen)
{
	int n, k, kmin, kmax;
	for (n = 0; n < (xlen +hlen -1); n++)
	{
		if (n > (hlen - 1))
		{
			kmin = n - (hlen - 1);
		}
		else
		{
			kmin = 0;
		}
		if (n < xlen - 1)
		{
			kmax = n;
		}
		else
		{
			kmax = xlen - 1;
		}
		printf(" KMIN%d : %d \t KMAX%d : %d \n", n, kmin, n, kmax);
		for (k = kmin; k <= kmax; k++)
		{
			y[n] += x[k] * h[n - k];
		}
		printf("%lf \n", y[n]);
	}
}
void Printarray(double *y, double aantal)
{
	for (int i = 0; i < aantal; i++)
	{
		printf("output[%d] : %.2lf", i, y[i]);
		printf("\n");
	}
}
void _2Dconvolution(double **x, double rows, double columns , double **kernel, double size, double **y)
{
	int i, j, m, n;
	int offsetx, offsety;
	// (collumns - size + 1 ) hoevaak de berekening moet gebeuren
	// (size - 1 ) /2 voor de rand te berekenen
	offsety = (size - 1) / 2;
	for (m = 0; m < rows - size + 1; m++)
	{
		offsetx = (size - 1) / 2;
		for (n = 0; n < columns - size + 1; n++)
		{
			for (j = 0; j < size; j++)
			{
				for (i = 0; i < size; i++)
				{
					y[offsetx][offsety] += x[j+m][i+n] * kernel[j][i];
				}
			}
			offsetx++;
		}
		offsety++;
	}
}
void Fill2Darray(double **x, double aantalx, double aantaly)
{
	int teller = 0;
	for (int i = 0; i < aantalx; i++)
	{
		for (int j = 0; j < aantaly; j++)
		{
			x[i][j] = teller;
			teller++;
		}
	}

}
void Print2Darray(double **x, double aantalx, double aantaly)
{
	for (int i = 0; i < aantalx; i++)
	{
		for (int j = 0; j < aantaly; j++)
		{
			printf("%.0lf\t", x[i][j]);
		}
		printf("\n");
	}
}

void DFT(double *x, double *x_re, double *x_mag, double *x_im, double *x_phase, double N)
{
	for (int m = 0; m <= N-1; m++)
	{
		for (int n = 0; n <= N-1; n++)
		{
			x_re[m] += x[n] * cos(2 * M_PI* (n*m / N));
			x_im[m] += -x[n] * sin(2 * M_PI * (n*m / N));
		}
		x_mag[m] = sqrt((x_re[m] * x_re[m]) * (x_im[m] * x_im[m]));
		x_phase[m] = atan2(x_im[m] , x_re[m]);

		if (x_mag[m] > 0.001)
		{
			x_phase[m] = x_phase[m] / M_PI * 180;
		}
		else
		{
			x_phase[m] = 0;
		}
	}

}
void GENERATE_SINEWAVE(double A, double f, double FS, double N, double phase, double *y)
{
	for (int i = 0; i < N; i++)
	{
		y[i] = A * sin(2 * M_PI * f * (i / FS) + phase);
	}
}
void add_waves(double *som,double *wave1, double *wave2, double aantal)
{
	for (int i = 0; i < aantal; i++)
	{
		som[i] = wave1[i] + wave2[i];
	}
}
// DSP Labo oefening CONVOLUTION

#include <stdio.h>
#include <math.h>
#include <STDLib.h>
// #define Pi 4*atan(1.0) // atan = bgtan()
#define size(a) (sizeof(a) / sizeof(double)) // Macro voor de groote van een array van doubles te bereken
void Convolution(double [], double, double [], double , double *);
void _2DConvolution(double **, double **, int, int, double **);
// int argc # parameters ,  char *arg[] de parameters 
int main(int argc, char * argv[])
{
	double x[] = { 1, 1, 1, 1 };
	double h[] = { 1, 2, 3 };
	double xlen = size(x);
	double hlen = size(h);
	//printf("lengte van x = %.0lf \n", xlen);
	//printf("lengte van h = %.0lf \n", hlen);
	double ylen = xlen + hlen - 1;
	//printf("lengte van y = %.0lf \n", ylen);
	double * y;
	y = calloc(ylen, sizeof(double));
	Convolution(x, xlen, h, hlen, y);
	getchar();
}

void Convolution(double x[], double xlen, double h[], double hlen, double* y)
{
	int n, k, KMIN,KMAX;
	for (n = 0; n < (xlen + hlen - 1); n++)
	{
		if (n > hlen -1){
			// als n groter is dan de lengte van h - 1
			// dan is de minimum van k n - (hlen -1) 
			KMIN = n -(hlen - 1);
		}
		else{
			// als n niet hoger is dan de lengte van h -1
			// begin je bij 0  
			KMIN = 0;
		}

		if (n < xlen - 1){
			// als de lengte van x - 1 groter is dan 0 dan is de max waarde van K = n 
			KMAX = n;
		}
		else
		{
			// als n niet kleiner is dan xlen - 1 dan is KMAX gelijk aan de waarde xlen - 1 
			KMAX = xlen - 1;
		}
		printf("KMIN %d: %d \t KMAX %d: %d\n", n,KMIN,n, KMAX);
		for (k = KMIN;k <= KMAX; k++)
		{
			y[n] += x[k] * h[n-k];	
		}
		printf("%.0lf \n", y[n]);
	}
	
}
/*void _2DConvolution(double** , double** , int rows , int collums, double** out )
{



}*/
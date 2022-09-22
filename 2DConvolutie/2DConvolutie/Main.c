#include <stdio.h>
#include <math.h>
#include <STDLib.h>
void FillArray(double **, int);
void PrintArray(double **,int);
void Convolution_2D(double **, double **, int, int, double **, int );
// int argc # parameters ,  char *arg[] de parameters 
int main(int argc, char * argv[])
{
	double **x;
	double **h;
	double **y;
	int aantalx,aantalh;

	printf("Geef de grote voor x :");
	scanf("%d", &aantalx);
	printf("\nGeef de grote voor h :");
	scanf("%d", &aantalh);
	// geheugen alocatie
	x = calloc(aantalx, sizeof(double *));
	y = calloc(aantalx, sizeof(double *));
	h = calloc(aantalh, sizeof(double *));
	for (int a = 0; a < aantalx; a++)
	{
		x[a] = calloc(aantalx, sizeof(double ));
		y[a] = calloc(aantalx, sizeof(double ));
	}
	for (int b = 0; b < aantalh; b++)
	{
		h[b] = calloc(aantalh, sizeof(double ));
	}
	FillArray(x, aantalx);
	FillArray(h, aantalh);
	PrintArray(x, aantalx);
	PrintArray(h, aantalh);
	// DEBUG PrintArray(y, aantalx);
	Convolution_2D(x, h, aantalx, aantalx, y, aantalh);
	PrintArray(y, aantalx);

	getchar();
	


}
void FillArray(double ** array, int aantal)
{
	int teller = 0;
	for (int m = 0; m < aantal; m++)
	{
		for (int n = 0; n < aantal; n++)
		{
			array[m][n] = teller ;
			teller++;
		}
	}
}

void PrintArray(double ** array, int aantal)
{
	for (int m = 0; m < aantal; m++)
	{
		for (int n = 0; n < aantal; n++)
		{
			printf("%.1lf\t", array[m][n]);
		}
		printf("\n");
	}
	printf("\n");

}
void Convolution_2D(double** x, double** h, int rows, int columns, double** y, int size)
{
	//y[m][n] = x[m][n]  h[n - i][m - j]
	int m , n, i, j;
	int offsetx,offsety = (size - 1) / 2; // rand 
	// rows - size +1 == hoeveel keer we moetten berekenen voor rows
	// columns - size + 1 == hoeveel keer we moetten bereken voor columns
	for (m = 0; m < rows - size + 1; m++)
		{
			offsetx = ((size - 1) / 2);
			for (n = 0; n < (columns - size) + 1; n++)
			{
				for (j = 0; j < size; j++)
				{
					for (i = 0; i < size; i++)
					{
						y[offsetx][offsety] += x[j+m][i+n] * h[j][i];
					}
				}
				offsetx++;
			}
			offsety++;
		}
	//}

}
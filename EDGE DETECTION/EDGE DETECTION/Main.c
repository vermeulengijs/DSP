#include "C:\Users\gijsimus\Desktop\DSP labo\Library\qdbmp_1.0.0\qdbmp.h"
#include <stdio.h>
#include <stdlib.h>
#define Laplacian
void Convolution_2D(UCHAR **, double [3][3], int, int, UCHAR **, int);

int main(int argc, char * argv[])
{
	BMP *Image;
	BMP *NewImage;
	UINT hoogte;
	UINT breedte;
	USHORT diepte;
	UCHAR **Input;
	UCHAR **Resultaat;
	UCHAR r; // red
	UCHAR g; // green
	UCHAR b; // blue
	UCHAR Y; // luminantie
	UCHAR waarde; // Pixel Index
	UINT rows = 256;
	UINT Kernelsize = 3;
	UINT cols = 256;
#ifdef Laplacian 
	double kernel[3][3] =
	{
		{ 0, -1, 0},
		{-1, 4, -1},
		{0, -1, 0} 
	};
#endif


	Image = BMP_ReadFile("lena_24bit_256.bmp");
	breedte = BMP_GetWidth(Image);
	hoogte = BMP_GetHeight(Image);
	diepte = BMP_GetDepth(Image);
	NewImage = BMP_Create(breedte, hoogte, 8);	// maak nieuwe BMP aan met bepaalde breedte,hoogte,diepte
	// geheugen allocatie
	Input = calloc(breedte, sizeof(UCHAR *));
	// 255 waardes = 8 bit
	for (UINT a = 0; a < breedte; a++)
	{
		Input[a] = calloc(hoogte, sizeof(UCHAR));
	}
	Resultaat = calloc(breedte, sizeof(UCHAR *));
	for (UINT a = 0; a < breedte; a++)
	{
		Resultaat[a] = calloc(hoogte, sizeof(UCHAR));
	}

	for (UINT y = 0; y < 256; y++)
	{
		for (UINT x = 0; x < 256; x++)
		{
			// RGB --> grijswaarde
			BMP_GetPixelRGB(Image, x, y, &r, &g, &b);
			Y = (0.299 * r + 0.587 * g + 0.114 * b); // luminantie 
			BMP_SetPixelIndex(NewImage, x, y, Y);
			// BMP in 2D array
			BMP_GetPixelIndex(NewImage, x, y, &waarde);
			Input[x][y] = waarde;
		}
	}
	// grijswaarde afprinten
	/*for (int i = 0; i < 256; i++)
	{
		BMP_SetPaletteColor(NewImage, i, i, i, i);
	}
	BMP_WriteFile(NewImage, "Oefening3.bmp");
	*/
	Convolution_2D(Input, kernel, rows, cols,Resultaat,Kernelsize);
	for (UINT y = 0; y < breedte; y++)
	{
		for (UINT x = 0; x < hoogte; x++)
		{
			BMP_SetPixelIndex(NewImage, y, x, Resultaat[x][y]);
		}
	}
	for (int i = 0; i < 256; i++)
	{
		BMP_SetPaletteColor(NewImage, i, i, i, i);
	}

	BMP_WriteFile(NewImage, "Oefening3.bmp");
	
}
// X is de input , h is de kernel , y is het resultaat
void Convolution_2D(UCHAR** x, double h[3][3], int rows, int columns, UCHAR** y, int size)
{
	//y[m][n] = x[m][n]  h[n - i][m - j]
	int m, n, i, j,a,b;
	int offsetx, offsety = (size - 1) / 2; // rand 
	double THRESH = 32;
	double ** temp;
	temp = calloc(rows, sizeof(double *));
	for (UINT a = 0; a < rows; a++)
	{
		temp[a] = calloc(columns, sizeof(double));
	}
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
					temp[offsetx][offsety] += x[j + m][i + n] * h[j][i];
					// OUTPUT mag geen UCHAR zijn dus temp double ** aangemaakt 
					// UCHAR OVERFLOWED en je verliest waardes
				}
			}
			offsetx++;
		}
		offsety++;
	}
	for (a = 0; a < rows; a++)
	{
		for (b = 0; b < columns; b++)
		{
			if (temp[b][a] > THRESH )
			{
				// Een zwart punt wegschrijven als je hoger bent dan de bepaalde thresh waarde 
				y[b][a] = 255;
			}
			else
			{
				// een wit punt wegschrijven als je lager ben dan de bepaalde thresh waarde
				y[b][a] = 0;
			}
		}
	}
	//}

}
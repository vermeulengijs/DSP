#include "C:\Users\gijsimus\Desktop\DSP labo\Library\qdbmp_1.0.0\qdbmp.h"
#include <stdlib.h>


int main(int argx, char *argv[])
{
	UINT hoogte;
	UINT breedte;
	USHORT diepte;
	USHORT diepteBMP = 8;
	UCHAR waarde;
	UCHAR r; // red
	UCHAR g; // green
	UCHAR b; // blue
	UCHAR Y; // luminantie
	BMP *Image;
	BMP *NewImage;
	
	unsigned long Hist[256] = { 0 };//histogram
	unsigned long CDF[256] = { 0 };//CDF
	unsigned long CDFmin;//Positie van CDFmin
	int teller = 0;

	int ** grijs;
	UCHAR **out;
	out = calloc(256, sizeof(UCHAR *));
	for (int a = 0; a < 256; a++)
	{
		out[a] = calloc(256, sizeof(UCHAR));
	}
	
	grijs = calloc(256, sizeof(int *));
	for (int a = 0; a < 256; a++)
	{
		grijs[a] = calloc(256, sizeof(int));
	}


	Image = BMP_ReadFile("lena_256_unequalized2.bmp");
	breedte = BMP_GetWidth(Image);
	hoogte = BMP_GetHeight(Image);
	diepte = BMP_GetDepth(Image);
	NewImage = BMP_Create(breedte, hoogte, diepte);	// maak nieuwe BMP aan met bepaalde breedte,hoogte,diepte
	for (UINT y = 0; y < 256; y++)
	{
		for (UINT x = 0; x < 256; x++)
		{
			// RGB --> grijswaarde
			BMP_GetPixelRGB(Image, x, y, &r, &g, &b);
			Y = (0.299 * r + 0.587 * g + 0.114 * b); // luminantie 
			BMP_SetPixelIndex(NewImage, x, y, Y);
		}
	}
	// BMP in 2D array
	for ( UINT y = 0; y < 256; y++)
	{
		for (UINT x = 0; x < 256; x++)
		{
			BMP_GetPixelIndex(NewImage, x, y, &waarde);
			grijs[x][y] = waarde;
		}
	}

	// opbouw histogram
	for (UINT y = 0; y < 256; y++)
	{
		for (UINT x = 0; x < 256; x++)
		{	
			Hist[grijs[y][x]]++; 
			//  een verdeling van hoeveel pixels een bepaalde waarde hebben
		}
	}


	// bouw CDF
	for (UINT x = 0; x < 256; x++)
	{
		// aantal van alle waardes verschillend van 0 overnemen 
		// de vorige waarde behouden en optellen met nieuwe waarde
		if (x < 1)
		{
			CDF[x] = Hist[x];
		}
		else
		{
			CDF[x] = CDF[x-1] + Hist[x];

		}
	}
	/*
	// printen van CDF
	for (UINT b = 0; b < 256; b++)
	{
		printf("%.2ld \n", CDF[b]);
	}
	*/
	// Histogram equalization
	do
	{		
		teller++;
	} while (CDF[teller] == 0);
	CDFmin = teller;
	//printf("%d \n", CDFmin);

	for (UINT y = 0; y < 256; y++)
	{
		for (UINT x = 0; x < 256; x++)
		{
			unsigned long v = grijs[y][x];
			out[y][x] = (double)(CDF[v] - CDF[CDFmin])* 255 / ((breedte * hoogte) - CDF[CDFmin]);
			BMP_SetPixelIndex(NewImage, y, x, out[y][x]);
		}
	}

	for (int i = 0; i < 256; i++)
	{
		BMP_SetPaletteColor(NewImage, i, i, i, i);
	}

	BMP_WriteFile(NewImage, "Oefening2.bmp");

	

}

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
	BMP* Image;
	BMP* NewImage;
	BMP* NewImageGrey;
	Image = BMP_ReadFile("resultaat.bmp");
	breedte = BMP_GetWidth(Image);
	hoogte = BMP_GetHeight(Image);
	diepte = BMP_GetDepth(Image);

	NewImage = BMP_Create(breedte, hoogte, diepte);	// maak nieuwe BMP aan met bepaalde breedte,hoogte,diepte
	NewImageGrey = BMP_Create(breedte, hoogte, 8);	// maak nieuwe BMP aan met bepaalde breedte,hoogte,diepte

	for (UINT y = 0; y < 341; y++)
	{
		for (UINT x = 0; x < 256; x++)
		{

				// negatief
				BMP_GetPixelIndex(Image, x, y, &waarde);	// haal pixel waardes van de originele bmp
				BMP_SetPixelIndex(NewImageGrey, x, y, (255 - waarde));	// set de pixels van de nieuwe bmp
				//
				// RGB --> grijswaarde
				/*
				BMP_GetPixelRGB(Image, x, y, &r, &g, &b);
				Y = (0.299 * r + 0.587 * g + 0.114 * b); // luminantie 
				BMP_SetPixelIndex(NewImageGrey, x, y, Y );
				*/
		}
	}
	for (int i = 0; i < 256; i++)
	{
		BMP_SetPaletteColor(NewImageGrey, i, i, i, i);
	}
	
	//BMP_WriteFile(NewImage, "Oefening.bmp");
	BMP_WriteFile(NewImageGrey, "resultaat2.bmp");

}
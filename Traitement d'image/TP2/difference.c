#include <stdio.h>
#include "image_ppm.h"
#include "math.h"
void eroder(OCTET *in, OCTET *out, int lignes, int colonnes) {
	int i, j;
	for (i=0; i < lignes; i++) {
		for (j=0; j < colonnes; j++) {
			int index = i*colonnes+j;
			int n = in[indexN(index, colonnes)];
			int s = in[indexS(index, lignes, colonnes)];
			int e = in[indexE(index, lignes, colonnes)];
			int w = in[indexW(index)];
			if(n + s + e + w == 0) {
				out[index] = 0;
			} else {
				out[index] = 255;
			}
		}
	}
}
void dilater(OCTET *in, OCTET *out, int lignes, int colonnes) {
	int i, j;
	for (i=0; i < lignes; i++) {
		for (j=0; j < colonnes; j++) {
			int index = i*colonnes+j;
			int n = in[indexN(index, colonnes)];
			int s = in[indexS(index, lignes, colonnes)];
			int e = in[indexE(index, lignes, colonnes)];
			int w = in[indexW(index)];
			if(n + s + e + w == 255 * 4) {
				out[index] = 255;
			} else {
				out[index] = 0;
			}
		}
	}
}


void difference(OCTET *inSeuil, OCTET *inDilat, OCTET *out, int lignes, int colonnes){
	int i, j;
	int SommePixS;
	int SommePixD;
	for (i=0; i < lignes; i++) {
		for (j=0; j < colonnes; j++) {
			int index = i*colonnes+j;
			// Récupéation des pixels entourant le pixel courant pour les deux images
			int nS = inSeuil[indexN(index, colonnes)];
			int nD = inDilat[indexN(index,colonnes)];

			int sS = inSeuil[indexS(index, lignes, colonnes)];
			int sD = inDilat[indexS(index, lignes, colonnes)];

			int eS = inSeuil[indexE(index, lignes, colonnes)];
			int eD = inDilat[indexE(index, lignes, colonnes)];

			int wS = inSeuil[indexW(index)];
			int wD = inDilat[indexW(index)];

			SommePixS = nS + sS + eS + wS;
			SommePixD = nD + sD + eD + wD;

			if((SommePixS + SommePixD == 255 * 8) || (SommePixS + SommePixD == 0)){// si les deux zones ont la même couleur
				out[index] = 255;// le pixel courant est blanc en sortie
			} else {
				out[index] = 0;// le pixel courant est noir en sortie
			}
		}
	}
}

int indexN(int index, int colonnes) {
	int n = index - colonnes;
	if(n < 0) {
		return 0;
	}
	return n;
}
int indexS(int index, int lignes, int colonnes) {
	int n = index + colonnes;
	if(n > lignes * colonnes) {
		return lignes * colonnes - 1;
	}
	return n;
}
int indexE(int index, int lignes, int colonnes) {
	int n = index + 1;
	if(n > lignes * colonnes) {
		return lignes * colonnes - 1;
	}
	return n;
}
int indexW(int index) {
	int n = index - 1;
	if(n < 0) {
		return 0;
	}
	return n;
}
int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char dila[250] = "dilatation.pgm";
	char diff[250] = "difference.pgm";
	int lignes, colonnes, nTaille, S;
	if (argc != 2) {
		printf("Usage: ImageIn.pgm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	OCTET *ImgIn, *ImgOut, *ImgOut1;
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgOut1, OCTET, nTaille);
	dilater(ImgIn, ImgOut, lignes, colonnes);
	difference(ImgIn,ImgOut, ImgOut1, lignes, colonnes);
	ecrire_image_pgm(dila, ImgOut, lignes, colonnes);
	ecrire_image_pgm(diff, ImgOut1, lignes, colonnes);
	free(ImgIn);
	return 1;
}

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

void affecte(OCTET *img1, OCTET *img2, int lignes, int colonnes){
	int i;
	for(i =0;i <lignes*colonnes;i++){
		img1[i]=img2[i];
	}
}

void tripleDilat(OCTET *in, OCTET *out, int lignes, int colonnes) {
	OCTET* temp,*tempOut;
	allocation_tableau(temp, OCTET, lignes*colonnes);
	allocation_tableau(tempOut, OCTET, lignes*colonnes);
	dilater(in,temp,lignes,colonnes);
	dilater(temp, tempOut, lignes, colonnes);
	dilater(tempOut,out,lignes,colonnes);	
	free(temp);
	free(tempOut);
}
void sixEros(OCTET *in, OCTET *out, int lignes, int colonnes) {
	OCTET* temp,*tempOut;
	allocation_tableau(temp, OCTET, lignes*colonnes);
	allocation_tableau(tempOut, OCTET, lignes*colonnes);
	eroder(in, temp, lignes, colonnes);
	int i;
	for(i = 0;i<4;i++){
		eroder(temp,tempOut,lignes,colonnes);
		affecte(temp,tempOut,lignes,colonnes);
	}
	eroder(temp, out, lignes, colonnes);
	free(temp);
	free(tempOut);
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
	char ouv[250] = "3D6E3D.pgm";
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
	tripleDilat(ImgIn, ImgOut, lignes, colonnes);
	sixEros(ImgOut, ImgOut1, lignes, colonnes);
	tripleDilat(ImgOut1,ImgOut,lignes,colonnes);
	ecrire_image_pgm(ouv, ImgOut, lignes, colonnes);
	free(ImgIn);
	return 1;
}

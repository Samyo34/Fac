#include <stdio.h>
#include "image_ppm.h"
#include "math.h"

int indexN(int index, int colonnes) {
	int n = index - colonnes * 3;
	if(n < 0) {
		return 0;
	}
	return n;
}
int indexS(int index, int lignes, int colonnes) {
	int n = index + colonnes * 3;
	if(n > lignes * colonnes * 3) {
		return lignes * colonnes * 3 - 1;
	}
	return n;
}
int indexE(int index, int lignes, int colonnes) {
	int n = index + 3;
	if(n > lignes * colonnes * 3) {
		return lignes * colonnes * 3 - 1;
	}
	return n;
}
int indexW(int index) {
	int n = index - 3;
	if(n < 0) {
		return 0;
	}
	return n;
}
int between (int value, int cmp1, int cmp2) {
	return value > cmp1 && value < cmp2;
}
int min(int a, int b) {
	if(a < b) {
		return a;
	}
	return b;
}
int max(int a, int b) {
	if(a > b) {
		return a;
	}
	return b;
}

void eroder(OCTET *in, OCTET *out, int lignes, int colonnes) {
	int i, j;
	for (i=0; i < lignes * colonnes * 3; i++) {
		for (j = 0; j < 3; ++j)
		{
			int index = i + j;
			int val = in[index];
			int n = in[indexN(index, colonnes)];
			int s = in[indexS(index, lignes, colonnes)];
			int e = in[indexE(index, lignes, colonnes)];
			int w = in[indexW(index)];
			int m = max(n, s);
			m = max(m, e);
			m = max(m, w);
			out[index] = m;
		}
	}
}


int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.ppm";
	int lignes, colonnes, nTaille, S;
	if (argc == 1) {
		sscanf (out, "%s", cNomImgLue);
	} else if (argc == 2) {
		sscanf (argv[1],"%s",cNomImgLue);
	} else {
		printf("to many arguments");
	}
	OCTET *ImgIn, *ImgOut, *ImgOut1;
	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes * 3;
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);
	eroder(ImgIn, ImgOut, lignes, colonnes);
	ecrire_image_ppm(out, ImgOut, lignes, colonnes);
	free(ImgIn);
	return 1;
}
#include <stdio.h>
#include "../TP2/image_ppm.h"
int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char cNomImgEcrite[250]="out_seuil.pgm";
	int nH, nW, nTaille, S;
	if (argc != 3) {
		printf("Usage: ImageIn.pgm Seuil \n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%d",&S);
	OCTET *ImgIn, *ImgOut;
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);
	int i,j;
	int histo[256]={0};
	for (i=0; i < nH; i++)// parcours des lignes
		for (j=0; j < nW; j++) {// parcours des colonnes
			OCTET* pixel = &ImgIn[i*nW+j]; // récuperation du niveau de gris du pixel en position i*nW+j
			if (*pixel < S) {// si le ndg est inférieur au seuil S
				*pixel = 0;// on affecte la couleur blanche au pixel (ndg = 0)
			} else {// sinon
				*pixel = 255;// on affecte la couleur noir au pixel (ndg = 255)
			}
		}
		ecrire_image_pgm(cNomImgEcrite, ImgIn, nH, nW);
		free(ImgIn);
		return 1;
	}
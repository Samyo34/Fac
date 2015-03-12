#include <stdio.h>
#include "../TP2/image_ppm.h"
#include <iostream>
#include "math.h"

using namespace std;

int coul_indexN(int index, int lignes, int colonnes) {
	int n = index - colonnes * 3;
	if(n < 0) {
		return 0;
	}
	return n;
}
int coul_indexS(int index, int lignes, int colonnes) {
	int n = index + colonnes * 3;
	if(n > lignes * colonnes * 3) {
		return lignes * colonnes * 3 - 1;
	}
	return n;
}
int coul_indexE(int index, int lignes, int colonnes) {
	int n = index + 3;
	if(n > lignes * colonnes * 3) {
		return lignes * colonnes * 3 - 1;
	}
	return n;
}
int coul_indexW(int index, int lignes, int colonnes){
	int n = index - 3;
	if(n < 0) {
		return 0;
	}
	return n;
}
int coul_indexNW(int index, int lignes, int colonnes) {
	return coul_indexW(coul_indexN(index, lignes, colonnes), lignes, colonnes);
}
int coul_indexNE(int index, int lignes, int colonnes) {
	return coul_indexE(coul_indexN(index, lignes, colonnes), lignes, colonnes);
}
int coul_indexSE(int index, int lignes, int colonnes) {
	return coul_indexE(coul_indexS(index, lignes, colonnes), lignes, colonnes);
}
int coul_indexSW(int index, int lignes, int colonnes) {
	return coul_indexW(coul_indexS(index, lignes, colonnes), lignes, colonnes);
}

int moyenneAtIndex(OCTET *ImgIn, int i, int lignes, int colonnes){
	return (ImgIn[coul_indexN(i,lignes,colonnes)]+ImgIn[coul_indexS(i,lignes,colonnes)]+ImgIn[coul_indexE(i,lignes,colonnes)]+ImgIn[coul_indexW(i,lignes,colonnes)]+
			ImgIn[coul_indexSW(i,lignes,colonnes)]+ImgIn[coul_indexSE(i,lignes,colonnes)]+ImgIn[coul_indexNW(i,lignes,colonnes)]+ImgIn[coul_indexNE(i,lignes,colonnes)])/8;
}


void flout(OCTET *ImgIn, OCTET *ImgInS, OCTET * ImgOut, int lignes, int colonnes){
	for(int i = 0;i<lignes*colonnes*3;i+=3){
		if(ImgInS[i/3] != 0){
			ImgOut[i]=moyenneAtIndex(ImgIn,i,lignes,colonnes);
		
			ImgOut[i+1]=moyenneAtIndex(ImgIn,i+1,lignes,colonnes);

			ImgOut[i+2]=moyenneAtIndex(ImgIn,i+2,lignes,colonnes);
		}else{
			ImgOut[i]=ImgIn[i];
		
			ImgOut[i+1]=ImgIn[i+1];

			ImgOut[i+2]=ImgIn[i+2];
		}
		
	}
}

int main(int argc, char* argv[]){
	OCTET *ImgIn,*ImgInS,*ImgOut;
	char cNomImgLue[250], cNomImgLueS[250];
	int nH, nW, nTaille;
	char c;
	char out[250]="out_flout_ext.ppm";

	if (argc != 3){
		printf("Usage: ImageIn.ppm Img_seuil.pgm \n");
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgLueS);

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);// lecture nombre lignes et colonnes
    nTaille = nH * nW;
    allocation_tableau(ImgInS,OCTET,nTaille);
    lire_image_pgm(cNomImgLueS,ImgInS,nTaille);
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    flout(ImgIn,ImgInS,ImgOut, nH,nW);
    ecrire_image_ppm(out, ImgOut, nH, nW);
	free(ImgIn);

    
    return 0;


}



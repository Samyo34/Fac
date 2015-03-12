#include <stdio.h>
#include "../TP2/image_ppm.h"
#include <iostream>
#include "math.h"

void transformation(OCTET *ImgIn, OCTET *ImgOut,int lignes,int colonnes){
	for(int i = 0; i < lignes*colonnes *3; i += 3){
		ImgOut[i/3]=(ImgIn[i]+ImgIn[i+1]+ImgIn[i+2])/3;
	}
}


int main(int argc, char* argv[])
{
	OCTET *ImgIn, *ImgOut;
    char cNomImgLue[250];
    int lignes, colonnes, nTaille, nR, nG, nB;
    char c;
    char out[250] = "out_trans.pgm";

    if (argc != 2){
         printf("Usage: ImageIn.pgm\n");
         exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue);

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);// lecture nombre lignes et colonnes
    nTaille = lignes * colonnes * 3;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
    allocation_tableau(ImgOut, OCTET, nTaille/3);
    transformation(ImgIn, ImgOut, lignes, colonnes);
    int histo[256]={0};
    for(int i =0; i<lignes*colonnes;i++){
    	histo[ImgOut[i]]++;
    }
    for(int i =0;i<256;i++){
    	std::cout<<i<<" "<<histo[i]<<std::endl;
    }
    ecrire_image_pgm(out, ImgOut, lignes, colonnes);



}
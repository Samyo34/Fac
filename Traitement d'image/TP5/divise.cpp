#include <stdio.h>
#include "../TP2/image_ppm.h"
#include <iostream>
#include "math.h"

void diviser(OCTET *ImgIn, OCTET *ImgOut,int lignes,int colonnes){
    int moyenne1=0;
    int moyenne2=0;
    int moyenne3=0;
    int moyenne4=0;

	for(int i =0; i< lignes;i++){
        for(int j = 0; j<colonnes;j++){
            if(i<lignes/2){
                if(j<colonnes/2){
                    // Image superieur gauche
                    moyenne1 = moyenne1 + ImgIn[i*lignes+j];

                }else{
                    // Image superieur droite
                    moyenne2 = moyenne2 + ImgIn[i*lignes+j];
                }
            }else{
                if(j<colonnes/2){
                    // Image inferieur gauche
                    moyenne3 = moyenne3 + ImgIn[i*lignes+j];
                }else{
                    // Image inferieur droit
                    moyenne4 = moyenne4 + ImgIn[i*lignes+j];

                }
            }
        }

    }
    moyenne1 = moyenne1/(lignes*colonnes/4);
    moyenne2 = moyenne2/(lignes*colonnes/4);
    moyenne3 = moyenne3/(lignes*colonnes/4);
    moyenne4 = moyenne4/(lignes*colonnes/4);
    std::cout<<moyenne1<<" "<<moyenne2<<" "<<moyenne3<<" "<<moyenne4<<std::endl;
    float variance1 = 0;
    float variance2 = 0;
    float variance3 = 0;
    float variance4 = 0;

    for(int i = 0;i<lignes;i++){
        for(int j = 0; j<colonnes;j++){
            if(i<lignes/2){
                if(j<colonnes/2){
                    // Image superieur gauche
                    ImgOut[i*lignes+j]=moyenne1;
                    variance1 += pow(ImgIn[i*lignes-j] - moyenne1,2);

                }else{
                    // Image superieur droite
                    ImgOut[i*lignes+j]=moyenne2;
                    variance2 += pow(ImgIn[i*lignes-j] - moyenne2,2);
                }
            }else{
                if(j<colonnes/2){
                    // Image inferieur gauche
                    ImgOut[i*lignes+j]=moyenne3;
                    variance3 += pow(ImgIn[i*lignes-j] - moyenne3,2);

                }else{
                    // Image inferieur droit
                    ImgOut[i*lignes+j]=moyenne4;
                    variance4 += pow(ImgIn[i*lignes-j] - moyenne4,2);

                }
            }
        }
    }
    variance1 = variance1 /(lignes*colonnes/4);
    variance2 = variance2 /(lignes*colonnes/4);
    variance3 = variance3 /(lignes*colonnes/4);
    variance4 = variance4 /(lignes*colonnes/4);
    std::cout<<variance1<<" "<<variance2<<" "<<variance3<<" "<<variance4<<std::endl;

}


int main(int argc, char* argv[])
{
	OCTET *ImgIn, *ImgOut;
    char cNomImgLue[250];
    int lignes, colonnes, nTaille, nR, nG, nB;
    char c;
    char out[250] = "out_divis.pgm";

    if (argc != 2){
         printf("Usage: ImageIn.pgm\n");
         exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);// lecture nombre lignes et colonnes
    nTaille = lignes * colonnes;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
    
    allocation_tableau(ImgOut, OCTET, nTaille);

    diviser(ImgIn,ImgOut,lignes,colonnes);
    
    ecrire_image_pgm(out, ImgOut, lignes, colonnes);



}
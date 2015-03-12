#include <stdio.h>
#include "../TP2/image_ppm.h"
#include <iostream>
#include "math.h"
#include "graphe.h"
#include <vector>

int a=0;
std::vector<Graphe*> v;

void diviser(OCTET *ImgIn, OCTET *ImgOut,int lignes1,int colonnes1, int lignes2, int colonnes2, int seuil){
    a++;
    int temp =a;
    int moyenne1=0;
    int moyenne2=0;
    int moyenne3=0;
    int moyenne4=0;
  //  std::cout<<lignes1<<":"<<colonnes1<<" | "<<lignes2<<":"<<colonnes2<<" "<<a<<std::endl;
	for(int i =lignes1; i< lignes2;i++){
        for(int j = colonnes1; j<colonnes2;j++){
            if(i<(lignes2-lignes1)/2){
                if(j<(colonnes2-colonnes1)/2){
                    // Image superieur gauche
                    moyenne1 = moyenne1 + ImgIn[i*(lignes2-lignes1)+j];
                }else{
                    // Image superieur droite
                    moyenne2 = moyenne2 + ImgIn[i*(lignes2-lignes1)+j];
                }
            }else{
                if(j<(colonnes2-colonnes1)/2){
                    // Image inferieur gauche
                    moyenne3 = moyenne3 + ImgIn[i*(lignes2-lignes1)+j];
                }else{
                    // Image inferieur droit
                    moyenne4 = moyenne4 + ImgIn[i*(lignes2-lignes1)+j];

                }
            }
        }

    }
    moyenne1 = moyenne1/(((lignes2-lignes1)*(colonnes2-colonnes1))/4);
    moyenne2 = moyenne2/(((lignes2-lignes1)*(colonnes2-colonnes1))/4);
    moyenne3 = moyenne3/(((lignes2-lignes1)*(colonnes2-colonnes1))/4);
    moyenne4 = moyenne4/(((lignes2-lignes1)*(colonnes2-colonnes1))/4);

    Graphe *g1 = new Graphe(lignes1, colonnes1, lignes1+(lignes2-lignes1)/1,colonnes1+(colonnes2-colonnes1)/2,moyenne1);
    Graphe *g2 = new Graphe(lignes1,colonnes1+(colonnes2-colonnes1)/2,lignes1+(lignes2-lignes1)/2,colonnes2,moyenne2);
    Graphe *g3 = new Graphe(lignes1+(lignes2-lignes1)/2,colonnes1,lignes2,colonnes1+(colonnes2-colonnes1)/2,moyenne3);
    Graphe *g4 = new Graphe(lignes1+(lignes2-lignes1)/2,colonnes1+(colonnes2-colonnes1)/2,lignes2,colonnes2,moyenne4);
    g1->setVoisins(g2,g3);
    g2->setVoisins(g1,g4);
    g3->setVoisins(g1,g4);
    g4->setVoisins(g2,g3);
    v.push_back(g1);
    v.push_back(g2);
    v.push_back(g3);
    v.push_back(g4);

    float variance1 = 0;
    float variance2 = 0;
    float variance3 = 0;
    float variance4 = 0;

    for(int i = lignes1;i<lignes2;i++){
        for(int j = colonnes1; j<colonnes2;j++){
            if(i<((lignes2-lignes1)/2)){
                if(j<((colonnes2-colonnes1)/2)){
                    // Image superieur gauche
                    ImgOut[i* /*(lignes2-lignes1)*/512+j]=moyenne1;
                    variance1 += pow((ImgIn[i*(lignes2-lignes1)+j] - moyenne1),2);
                }else{
                    // Image superieur gauche (anc : droit)
                    
                    ImgOut[i*512+j]=moyenne2;
                    variance2 += pow((ImgIn[i*(lignes2-lignes1)+j] - moyenne2),2);
                }
            }else{
                if(j<((colonnes2-colonnes1)/2)){
                    // Image inferieur gauche
                    ImgOut[i*512+j]=moyenne3;
                    variance3 += pow((ImgIn[i*(lignes2-lignes1)+j] - moyenne3),2);

                }else{
                    // Image inferieur droit
                    ImgOut[i*512+j]=moyenne4;
                    variance4 += pow((ImgIn[i*(lignes2-lignes1)+j] - moyenne4),2);

                }
            }
        }
    }
    variance1 = variance1 /(((lignes2-lignes1)*(colonnes2-colonnes1))/4);
    variance2 = variance2 /(((lignes2-lignes1)*(colonnes2-colonnes1))/4);
    variance3 = variance3 /(((lignes2-lignes1)*(colonnes2-colonnes1))/4);
    variance4 = variance4 /(((lignes2-lignes1)*(colonnes2-colonnes1))/4);
   // std::cout<<sqrt(variance1)<<" "<<sqrt(variance2)<<" "<<sqrt(variance3)<<" "<<sqrt(variance4)<<" "<<seuil<<std::endl;

    if(sqrt(variance1) > seuil && !(((lignes2-lignes1)/2)<=8)){
        diviser(ImgIn,ImgOut, lignes1,colonnes1,lignes1+(lignes2-lignes1)/2,colonnes1+(colonnes2-colonnes1)/2,seuil);
    }

    if(sqrt(variance2) > seuil && !(((lignes2-lignes1)/2)<=8)){
        diviser(ImgIn,ImgOut, lignes1,colonnes1+(colonnes2-colonnes1)/2,lignes1+(lignes2-lignes1)/2,colonnes2,seuil);
    }

    if(sqrt(variance3) > seuil && !(((lignes2-lignes1)/2)<=8)){
        diviser(ImgIn,ImgOut, lignes1+(lignes2-lignes1)/2,colonnes1,lignes2,colonnes1+(colonnes2-colonnes1)/2,seuil);
    }

    if(sqrt(variance4) > seuil && !(((lignes2-lignes1)/2)<=8)){
        diviser(ImgIn,ImgOut, lignes1+(lignes2-lignes1)/2,colonnes1+(colonnes2-colonnes1)/2,lignes2,colonnes2,seuil);
    }
   // std::cout<<"fin"<<" "<<temp<<std::endl;

}

void fusion(OCTET *ImgIn, OCTET *ImgOut, int seuil){
    std::cout<<"la 1"<<" "<<v.size()<<std::endl;
    Graphe** vois;
    for(int i = 0; i<v.size();i++){
        vois = v[i]->getVoisins();
        if((vois[0]->getMoyenne() - v[i]->getMoyenne()) < seuil){
            for(int l = vois[0]->getL1();l<vois[0]->getL2();l++){
               std::cout<<"la 2 "<<vois[0]->getC1()<<std::endl;
                for(int c = vois[0]->getC1();c<vois[0]->getC2();c++){
                    if(i==8){
                        std::cout<<i<<" "<<v[i]->getMoyenne()<<std::endl;
                    }
                    ImgOut[l*512+c]=v[i]->getMoyenne();
                }
            }
        }else if((vois[1]->getMoyenne() - v[i]->getMoyenne()) < seuil){
        std::cout<<"la 2bis"<<std::endl;
            for(int l = vois[1]->getL1();l<vois[1]->getL2();l++){
                for(int c = vois[1]->getC1();c<vois[1]->getC2();c++){
                     if(i==8){
                        std::cout<<i<<" "<<v[i]->getMoyenne()<<std::endl;
                    }
                    ImgOut[l*512+c]=v[i]->getMoyenne();

                }
            }
        }
    }
}


int main(int argc, char* argv[])
{
	OCTET *ImgIn, *ImgOut,*ImgOut2;
    char cNomImgLue[250];
    int lignes, colonnes, nTaille, nR, nG, nB;
    char c;
    char out[250] = "out_fusion_img1.pgm";
    char out2[250]= "out_fusion_img2.pgm";

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
    allocation_tableau(ImgOut2,OCTET,nTaille);
    std::cout<<"pouet"<<std::endl;
    diviser(ImgIn,ImgOut,0,0,lignes,colonnes,50);
    std::cout<<"deb fusion"<<std::endl;
    fusion(ImgOut,ImgOut2,10);
    
    ecrire_image_pgm(out, ImgOut, lignes, colonnes);
    ecrire_image_pgm(out2,ImgOut2,lignes,colonnes);



}
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "../TP2/image_ppm.h"

using namespace std;


int moyenneImg(OCTET *Img){
	int somme=0;
	for (int i=0; i < 8; i++){
		for (int j=0; j < 8; j++){
			somme+=Img[i*8+j];
		}
	}
	return somme/64;
}

int getCarre(OCTET* ImgIn,int indexH, int indexW){
	OCTET* ImgCarre;
	allocation_tableau(ImgCarre, OCTET, 64);
	for(int i=indexH;i<indexH+8;i++){
		for(int j=indexW;j<indexW+8;j++){
			ImgCarre[(i-indexH)*64+(j-indexW)] = ImgIn[i*512+j]; 
		}
	}

	return moyenneImg(ImgCarre);

}

void drawCarre(OCTET *ImgOut, int xHG, int yHG, int taille, int couleur){
	for(int i=xHG; i< xHG+taille;i++){
		for(int j=yHG; j<yHG+taille;j++){
			ImgOut[i*512+j] = couleur;
		}
	}
}
void divRecursive(OCTET *ImgIn, OCTET *ImgOut,int x,int y, int nTaille, int nH, int nW, int nbDiv){
	if (nbDiv>1){
		int somme1=0;
		int somme2=0;
		int somme3=0;
		int somme4=0;
		for (int i=x; i < x+nH; i++){
			for (int j=y; j < y+nW; j++){
				if (j<y+(nW/2) && i<x+(nH/2)){
					somme1 += ImgIn[i*512+j];
				}
				else if (j>=y+(nW/2) && i<x+(nH/2)){
					somme2 += ImgIn[i*512+j];
				}
				else if (j<y+(nW/2) && i>=x+(nH/2)){
					somme3 += ImgIn[i*512+j];
				}
				else if (j>=y+(nW/2) && i>=x+(nH/2)){
					somme4 += ImgIn[i*512+j];
				}
			}
		}
		int moyenne1 = somme1/(nTaille/4);
		int moyenne2 = somme2/(nTaille/4);
		int moyenne3 = somme3/(nTaille/4);
		int moyenne4 = somme4/(nTaille/4);

		drawCarre(ImgOut, x,y,nH/2,moyenne1);
		drawCarre(ImgOut, x,y+(nH/2),nH/2,moyenne2);
		drawCarre(ImgOut, x+(nH/2),y,nH/2,moyenne3);
		drawCarre(ImgOut, x+(nH/2),y+(nW/2),nH/2,moyenne4);

		divRecursive(ImgIn, ImgOut,x,y,nTaille/4,nH/2,nW/2,nbDiv-1);
		divRecursive(ImgIn, ImgOut,x,y+(nW/2),nTaille/4,nH/2,nW/2,nbDiv-1);
		divRecursive(ImgIn, ImgOut,x+(nH/2),y,nTaille/4,nH/2,nW/2,nbDiv-1);
		divRecursive(ImgIn, ImgOut,x+(nH/2),y+(nW/2),nTaille/4,nH/2,nW/2,nbDiv-1);
	}
}

int getImgByVal(OCTET* ImgIn, int index, int lignes, int colonnes){
	int moyenne = 0;
	for(int i = 0; i< lignes * colonnes;i++){
		moyenne += ImgIn[i];
	}
	moyenne /= (lignes*colonnes);

	return moyenne;
	//cout<<moyenne<<":"<<index<<":"<<vals[moyenne]<<" | ";
}


/*
 * Creer une image réduite de ImgIn (8x8)
 */
void creerMoz(OCTET* ImgIn, OCTET* ImgOut){
	OCTET* moz,*temp;
	allocation_tableau(moz,OCTET,64);
	allocation_tableau(temp,OCTET,512*512);
	divRecursive(ImgIn,temp,0,0,512*512,512,512,4);
	int cpt =0;
	for(int i =0;i<512;i+=64){
		for(int j =0;j<512;j+=64){
			
			moz[cpt]=(int)temp[i*512+j];
			//cout<<(int)temp[i*512+j]<<"="<<(int)moz[cpt]<<":";
			cpt++;
		}
	}
	ImgOut = moz;
	free(temp);
	free(moz);
	/*cout<<endl;
	char name[64]="pouet.pgm";
	char name2[64]="pouet2.pgm";
	ecrire_image_pgm(name, moz, 64, 64);
	ecrire_image_pgm(name2, temp, 512, 512);*/
}

int findImg(int* val, int ndg, int nbtest){
	if(val[ndg]!=-1){
		return val[ndg];
	}else{
		if(val[ndg+nbtest]!=-1){
			return val[ndg+nbtest];
		}else if(val[ndg-nbtest]!=-1){
			return val[ndg-nbtest];
		}else{
			return findImg(val,ndg,nbtest+1);
		}
	}
}

void placeMoz(OCTET* ImgIn, OCTET* ImgOut,int* val, int nH, int nW){
	char img[64];
	OCTET* lue;// stockage de l'image lue 512x512
	allocation_tableau(lue, OCTET, 512*512);
	OCTET* mozaique;// stockage de l'image réduite 8x8
	allocation_tableau(mozaique,OCTET,64);
	for(int i =0; i<nH; i+=8){
		for(int j=0;j<nW;j+=8){
			// Récuperation de l'image ayant une valeur proche de ImgIn[i*512+j]
			sprintf(img,"%s%d%s","./BOWS2OrigEp3/",findImg(val,ImgIn[i*512+j],0),".pgm");
			lire_image_pgm(img,lue,512*512);
			// Transformation en image de 8x8
			creerMoz(lue, mozaique);
			cout<<"la"<<endl;
			int cpt =0;
			for(int k =i;k<(i+8);k++){
				for(int l = j;l<(j+8);l++){
					cout<<"k : "<<k<<"    l : "<<l<<endl;
					ImgOut[k*512+l]=mozaique[cpt];
					cpt++;
				}
			}
			cout<<"la2"<<endl;

		}
	}
}




int main(int argc, char* argv[]){
	char cNomImgLue[250];
	int nH, nW, nTaille;
	if (argc != 2) {
		printf("Usage: ImageIn.pgm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	char cNomImgEcrite[250] = "out_decoup.pgm";
	OCTET *ImgIn, *ImgOut,*ImgOut2;
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgOut2,OCTET,nTaille);

	// Lecture des n fichiers (servant à creer la mozaique)
	OCTET *ImgMoz;
	char img[64];
	int val[256];
	for(int i = 0;i<256;i++)
		val[i]=-1;
	for (int i = 0; i < 2000; ++i){
		allocation_tableau(ImgMoz, OCTET, nTaille);
		sprintf(img,"%s%d%s","./BOWS2OrigEp3/",i,".pgm");
		lire_image_pgm(img, ImgMoz, nTaille);
		val[getImgByVal(ImgMoz,i,nH,nW)]=i;
	}

	for(int i =0;i<256;i++){
		cout<<val[i]<<" | ";
	}
	cout<<endl;

	creerMoz(ImgIn, ImgOut);

	divRecursive(ImgIn, ImgOut,0,0, nTaille, nH, nW,7);

	/*for(int i =0;i<nH;i+=8){
		for(int j =0;j<nW;j+=8){
			cout<<ImgOut[i*512+j]<<":";
		}
	}
	cout<<endl;*/
	placeMoz(ImgOut, ImgOut2, val,  nH, nW);
	cout<<"la3"<<endl;

	ecrire_image_pgm(cNomImgEcrite, ImgOut2, nH, nW);
	free(ImgIn);
	return 1;
}
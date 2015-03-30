#include "../TP2/image_ppm.h"
#include <iostream>

using namespace std;

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

void moyenne(OCTET* ImgIn, OCTET* ImgOut, int lignes, int colonnes, int seuil){
	int sum=0;
	int index[lignes*colonnes];// stock les index des pixels à traiter
	int nbPixel=0;// nombre de pixel pour calculer la moyenne
	for(int i=0;i<lignes*colonnes;i++){
		if(ImgIn[i]<seuil){
			// pixel à corriger
			index[i]=1;

		}else{
			// pixel en "bonne etat"
			index[i]=0;
			sum += ImgIn[i];
			nbPixel++;
		}
	}
	int moyenne = sum/nbPixel;

	for(int i =0;i<lignes*colonnes;i++){
		if(index[i]){
			ImgOut[i]=sum;
		}else{
			ImgOut[i]=ImgIn[i];
		}
	}

}

void dilater(OCTET* ImgIn, OCTET* ImgOut, int lignes, int colonnes, int seuil){
	int sum=0;
	int nbPixel;// nombre de pixel pour calculer la moyenne
	int moyenne;
	for(int i=0;i<lignes*colonnes;i++){
		nbPixel =0;
		if(ImgIn[i]<seuil){
			// pixel à corriger
			if(ImgIn[indexN(i,colonnes)]>seuil){
				sum += ImgIn[indexN(i,colonnes)];
				nbPixel++;
			}

			if(ImgIn[indexS(i,lignes,colonnes)]>seuil){
				sum += ImgIn[indexS(i,lignes,colonnes)];
				nbPixel++;
			}

			if(ImgIn[indexE(i,lignes,colonnes)]>seuil){
				sum += ImgIn[indexE(i,lignes,colonnes)];
				nbPixel++;
			}

			if(ImgIn[indexW(i)]>seuil){
				sum += ImgIn[indexW(i)];
				nbPixel++;
			}
			if(nbPixel==0){
				moyenne = sum;
			}else{
				moyenne = sum/nbPixel;
			}
			
			ImgOut[i]=moyenne;

		}else{
			ImgOut[i]=ImgIn[i];
		}
	}
}

bool debutTrou(OCTET* ImgIn,int index, int lignes, int colonnes, int seuil){
	if((ImgIn[index]>seuil) && (ImgIn[index+1]<=seuil) && (ImgIn[index +2]<=seuil)){
		return true;
	}else{
		return false;
	}
		
	
}

bool finTrou(OCTET* ImgIn,int index, int lignes, int colonnes, int seuil){
	if(index-1> lignes*colonnes){
		if(index-2>=lignes*colonnes){
			if(ImgIn[index]>seuil && ImgIn[index-1]<=seuil && ImgIn[index-2]){
				return true;
			}
			else{
				return false;
			}
		}else{
			return false;
		}
		
	}else{
		return false;
	}

}

void corrige(OCTET* ImgIn, OCTET* ImgOut, int lignes, int colonnes,int seuil){
	int valPix=ImgIn[0];//pourquoi pas cette valeur ?
	for(int i =0;i<lignes*colonnes;i++){
		if(debutTrou(ImgIn,i,lignes,colonnes,seuil)){
			//cout<<i<<"debut trou"<<endl;
			valPix = ImgIn[i-1];
			ImgOut[i]=valPix;
		}else if(finTrou(ImgIn, i, lignes,colonnes,seuil)){
			cout<<i<<"fin trou"<<endl;
			valPix = ImgIn[i+1];
			ImgOut[i] = valPix;
		}else if(ImgIn[i]<=seuil){
			cout<<"dans le trou"<<endl;
			ImgOut[i]=valPix;
		}else{
			ImgOut[i]=ImgIn[i];
		}
	}
}



int main(int argc, char* argv[])
{
	OCTET *ImgIn, *ImgOut;
    char cNomImgLue[250];
    int lignes, colonnes, nTaille;
    char out[250] = "out_restore_corrige.pgm";

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

    corrige(ImgIn,ImgOut,lignes,colonnes,0);  
    
    ecrire_image_pgm(out, ImgOut, lignes, colonnes);



}
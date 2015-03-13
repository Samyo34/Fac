#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>


using namespace std;
int X = 256; // ligne
int Y = 256; // colonne
int Z = 100; // image

float sizeX;
float sizeY;
float sizeZ;

struct resultat{
	bool isOne; // vrai si il y en au moins 1;
	int pos; // position du Voxel "coupable"
	// 0: dessus(y+1), 1: dessous(y-1), 2: devant(z+1), 3: derrière(z-1), 4: gauche(x-1), 5 droite(x+1)
};

int getValue(int ***data,int x, int y, int z){
  int res = data[z][x][y];
  return res;
}

int*** to3DTab(int *data, size_t taille){
	int ***data3D = new int**[Z];
  int cpt =0;
	for(int i = 0;i<Z;i++){// pour chaque matrice
    data3D[i] = new int*[X];
		for(int j =0;j<X;j++){// pour chaque lignes
      data3D[i][j] =  new int[Y];
			for(int k=0;k<Y;k++){// pour chaque colonnes
				data3D[i][j][k]= data[cpt];
        cpt++;
			}
		}
	}
  return data3D;
}

void setValue(int*** data, int x, int y, int z, int value){
	data[z][x][y] = value;
}

/*
 * Retourne vrai si aun des voisins du Voxel (x,y,z) a une
 * valeur inferieur au seuil (les vrai voxels : taille + position)
 */
resultat isVoisInf(int*** data,int x, int y, int z , int seuil){
	resultat res;
	if(getValue(data,x,y+1,z)<seuil){
		res.isOne = true;
		res.pos = 0;
		return res;
	}else if(getValue(data,x,y-1,z)<seuil){
		res.isOne = true;
		res.pos = 1;
		return res;
	}else if(getValue(data,x+1,y,z)<seuil){
		res.isOne = true;
		res.pos = 5;
		return res;
	}else if(getValue(data,x-1,y,z)<seuil){
		res.isOne = true;
		res.pos = 4;
		return res;
	}else if(getValue(data,x,y,z+1)<seuil){
		res.isOne = true;
		res.pos = 2;
		return res;
	}else if(getValue(data,x,y,z-1)<seuil){
		res.isOne = true;
		res.pos = 3;
		return res;
	}else{
		res.isOne = false;
		res.pos = -1;
		return res;
	}
}

int*** getTriangle(int*** data, int x, int y, int z, int pos){
	// TODO :  recuperer les deux triangles
}

 maillage(int*** data, int seuil){
	for(int i =1;i<Z;i++){
		for(int j =1;j<X;j++){
			for(int k=1;k<Y;k++){
				if(getValue(j,k,i)>seuil){
					resultat res = isVoisInf(data, j,k,i,seuil);
					if(resultat.isOne){
						// TODO : voir ennoncé
					}
				}
			}
		}
	}
}


void seuil(int data***, int seuil){
	for(int i =0; i<Z;i++){
		for(int j=0;j<X;j++){
			for(int k = 0;k<Y;k++){
				if(getValue(data,j,k,i)>seuil){
					setValue(data, j,k,i,255);
				}else{
					setValue(data,j,k,i,0);
				}
			}
		}
	}
}

int main(int argc, char* argv[]){

	char cNomImgLue[250];
	if(argc != 2){
		cout<<"Usage : Image"<<endl;
		exit (1);
	}

	sscanf (argv[1],"%s",cNomImgLue);
	FILE*  f = fopen(cNomImgLue,"rb");

	long size;
  	size_t nbLue;

  	fseek (f , 0 , SEEK_END);
  	size = ftell (f);
  	rewind (f);
  	
  	unsigned short *buff = new unsigned short[size];

  	nbLue = fread((char *)buff, 2,size,f);
  	short oct1 = buff[0]%256;
  	short oct2 = buff[0]/256;
  	int val = oct1*256+oct2;
  	int max = val;
    int min = val;
  	int *data = new int[nbLue];
  	data[0]= val;

  	for(int i =1;i<nbLue;i++){
  		oct1 = buff[i]%256;
  		oct2 = buff[i]/256;
  		val = oct1*256+oct2;
  		if(val>max){
  			max =val;
  		}
      if(val < min){
        min = val;
      }
  		data[i]=val;
  	}
    int*** dt = to3DTab(data,nbLue);
    int p = getValue(dt,200,200,20);
  	cout<<"Voxel max : "<<max<<", Voxel min : "<<min<<", Voxel en 200,200,20 : "<<p<<endl;


}
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>


using namespace std;
int X = 256; // ligne
int Y = 256; // colonne
int Z = 128; // image

float sizeX=5;
float sizeY=5;
float sizeZ=5;

struct resultat{
	bool isOne; // vrai si il y en au moins 1;
	int pos[6]; // position du Voxel "coupable"
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
 * Retourne vrai si un des voisins du Voxel (x,y,z) a une
 * valeur inferieur au seuil (les vrai voxels : taille + position)
 */
resultat isVoisInf(int*** data,int x, int y, int z , int seuil){
	resultat res;
	if(getValue(data,x,y+1,z)<seuil){
		res.isOne = true;
		res.pos[0]=1;
		return res;
	}else if(getValue(data,x,y-1,z)<seuil){
		res.isOne = true;
		res.pos[1]= 1;
		return res;
	}else if(getValue(data,x+1,y,z)<seuil){
		res.isOne = true;
		res.pos[5] = 1;
		return res;
	}else if(getValue(data,x-1,y,z)<seuil){
		res.isOne = true;
		res.pos[4] = 1;
		return res;
	}else if(getValue(data,x,y,z+1)<seuil){
		res.isOne = true;
		res.pos[2] = 1;
		return res;
	}else if(getValue(data,x,y,z-1)<seuil){
		res.isOne = true;
		res.pos[3] = 1;
		return res;
	}else{
		res.isOne = false;
		return res;
	}
}

float*** getTriangle(int*** data, int x, int y, int z, int pos){
	float*** triangles = new float**[2];
	triangles[0]=new float*[9];
	triangles[1]=new float*[9];
	float val;
	switch (pos){
		case 0:
		// premier triangle
		triangles[0][0]=new float(x*sizeX-sizeX/2);
		triangles[0][1]=new float(y*sizeY+sizeY/2);
		triangles[0][2]=new float(z*sizeZ+sizeZ/2);
		triangles[0][3]=new float(x*sizeX+sizeX/2);
		triangles[0][4]=new float(y*sizeY+sizeY/2);
		triangles[0][5]=new float(z*sizeZ-sizeZ/2);
		triangles[0][6]=new float(x*sizeX+sizeX/2);
		triangles[0][7]=new float(y*sizeY+sizeY/2);
		triangles[0][8]=new float(z*sizeZ+sizeZ/2);

		// seconde triangle
		triangles[1][0]=new float(x*sizeX-sizeX/2);
		triangles[1][1]=new float(y*sizeY+sizeY/2);
		triangles[1][2]=new float(z*sizeZ+sizeZ/2);
		triangles[1][3]=new float(x*sizeX-sizeX/2);
		triangles[1][4]=new float(y*sizeY+sizeY/2);
		triangles[1][5]=new float(z*sizeZ-sizeZ/2);
		triangles[1][6]=new float(x*sizeX+sizeX/2);
		triangles[1][7]=new float(y*sizeY+sizeY/2);
		triangles[1][8]=new float(z*sizeZ-sizeZ/2);
		break;
		case 1:
		// premier triangle
		triangles[0][0]=new float(x*sizeX-sizeX/2);
		triangles[0][1]=new float(y*sizeY-sizeY/2);
		triangles[0][2]=new float(z*sizeZ+sizeZ/2);
		triangles[0][3]=new float(x*sizeX+sizeX/2);
		triangles[0][4]=new float(y*sizeY-sizeY/2);
		triangles[0][5]=new float(z*sizeZ-sizeZ/2);
		triangles[0][6]=new float(x*sizeX+sizeX/2);
		triangles[0][7]=new float(y*sizeY-sizeY/2);
		triangles[0][8]=new float(z*sizeZ+sizeZ/2);
		// seconde triangle
		triangles[1][0]=new float(x*sizeX-sizeX/2);
		triangles[1][1]=new float(y*sizeY-sizeY/2);
		triangles[1][2]=new float(z*sizeZ+sizeZ/2);
		triangles[1][3]=new float(x*sizeX-sizeX/2);
		triangles[1][4]=new float(y*sizeY-sizeY/2);
		triangles[1][5]=new float(z*sizeZ-sizeZ/2);
		triangles[1][6]=new float(x*sizeX+sizeX/2);
		triangles[1][7]=new float(y*sizeY-sizeY/2);
		triangles[1][8]=new float(z*sizeZ-sizeZ/2);
		break;
		case 2:
		// premier triangle
		triangles[0][0]=new float(x*sizeX-sizeX/2);
		triangles[0][1]=new float(y*sizeY+sizeY/2);
		triangles[0][2]=new float(z*sizeZ+sizeZ/2);
		triangles[0][3]=new float(x*sizeX+sizeX/2);
		triangles[0][4]=new float(y*sizeY+sizeY/2);
		triangles[0][5]=new float(z*sizeZ+sizeZ/2);
		triangles[0][6]=new float(x*sizeX+sizeX/2);
		triangles[0][7]=new float(y*sizeY-sizeY/2);
		triangles[0][8]=new float(z*sizeZ+sizeZ/2);
		// seconde triangle
		triangles[1][0]=new float(x*sizeX-sizeX/2);
		triangles[1][1]=new float(y*sizeY+sizeY/2);
		triangles[1][2]=new float(z*sizeZ+sizeZ/2);
		triangles[1][3]=new float(x*sizeX+sizeX/2);
		triangles[1][4]=new float(y*sizeY-sizeY/2);
		triangles[1][5]=new float(z*sizeZ+sizeZ/2);
		triangles[1][6]=new float(x*sizeX-sizeX/2);
		triangles[1][7]=new float(y*sizeY-sizeY/2);
		triangles[1][8]=new float(z*sizeZ+sizeZ/2);
		break;
		case 3:
		// premier triangle
		triangles[0][0]=new float(x*sizeX-sizeX/2);
		triangles[0][1]=new float(y*sizeY+sizeY/2);
		triangles[0][2]=new float(z*sizeZ-sizeZ/2);
		triangles[0][3]=new float(x*sizeX+sizeX/2);
		triangles[0][4]=new float(y*sizeY+sizeY/2);
		triangles[0][5]=new float(z*sizeZ-sizeZ/2);
		triangles[0][6]=new float(x*sizeX+sizeX/2);
		triangles[0][7]=new float(y*sizeY-sizeY/2);
		triangles[0][8]=new float(z*sizeZ-sizeZ/2);
		// seconde triangle
		triangles[1][0]=new float(x*sizeX-sizeX/2);
		triangles[1][1]=new float(y*sizeY-sizeY/2);
		triangles[1][2]=new float(z*sizeZ-sizeZ/2);
		triangles[1][3]=new float(x*sizeX+sizeX/2);
		triangles[1][4]=new float(y*sizeY+sizeY/2);
		triangles[1][5]=new float(z*sizeZ-sizeZ/2);
		triangles[1][6]=new float(x*sizeX+sizeX/2);
		triangles[1][7]=new float(y*sizeY-sizeY/2);
		triangles[1][8]=new float(z*sizeZ-sizeZ/2);
		break;
		case 4:
		// premier triangle
		triangles[0][0]=new float(x*sizeX-sizeX/2);
		triangles[0][1]=new float(y*sizeY+sizeY/2);
		triangles[0][2]=new float(z*sizeZ+sizeZ/2);
		triangles[0][3]=new float(x*sizeX-sizeX/2);
		triangles[0][4]=new float(y*sizeY-sizeY/2);
		triangles[0][5]=new float(z*sizeZ+sizeZ/2);
		triangles[0][6]=new float(x*sizeX-sizeX/2);
		triangles[0][7]=new float(y*sizeY+sizeY/2);
		triangles[0][8]=new float(z*sizeZ-sizeZ/2);
		// seconde triangle
		triangles[1][0]=new float(z*sizeZ-sizeZ/2);
		triangles[1][1]=new float(y*sizeY-sizeY/2);
		triangles[1][2]=new float(z*sizeZ+sizeZ/2);
		triangles[1][3]=new float(x*sizeX-sizeX/2);
		triangles[1][4]=new float(y*sizeY-sizeY/2);
		triangles[1][5]=new float(z*sizeZ-sizeZ/2);
		triangles[1][6]=new float(x*sizeX-sizeX/2);
		triangles[1][7]=new float(y*sizeY+sizeY/2);
		triangles[1][8]=new float(z*sizeZ-sizeZ/2);
		break;
		case 5:
		// premier triangle
		triangles[0][0]=new float(x*sizeX+sizeX/2);
		triangles[0][1]=new float(y*sizeY+sizeY/2);
		triangles[0][2]=new float(z*sizeZ+sizeZ/2);
		triangles[0][3]=new float(x*sizeX+sizeX/2);
		triangles[0][4]=new float(y*sizeY+sizeY/2);
		triangles[0][5]=new float(z*sizeZ-sizeZ/2);
		triangles[0][6]=new float(x*sizeX+sizeX/2);
		triangles[0][7]=new float(y*sizeY-sizeY/2);
		triangles[0][8]=new float(z*sizeZ+sizeZ/2);
		// seconde triangle
		triangles[1][0]=new float(x*sizeX+sizeX/2);
		triangles[1][1]=new float(y*sizeY+sizeY/2);
		triangles[1][2]=new float(z*sizeZ-sizeZ/2);
		triangles[1][3]=new float(x*sizeX+sizeX/2);
		triangles[1][4]=new float(y*sizeY-sizeY/2);
		triangles[1][5]=new float(z*sizeZ-sizeZ/2);
		triangles[1][6]=new float(x*sizeX+sizeX/2);
		triangles[1][7]=new float(y*sizeY-sizeY/2);
		triangles[1][8]=new float(z*sizeZ+sizeZ/2);
		break;

	}
	return triangles;

}

void maillage(int*** data, int seuil){
 	FILE* out = fopen("maillage.txt","w");
 	char stringW[150];
 	float*** triangles;
 	resultat res;
 	res.pos[0]=0;res.pos[1]=0;res.pos[2]=0;res.pos[3]=0;res.pos[4]=0;res.pos[5]=0; 

	sprintf(stringW, "%s \n",  "solid name" );
	cout<<stringW;
	fwrite(stringW, sizeof(stringW),1,out);
	sprintf(stringW, "%s \n",  "facet nomrmal 0 0 0" );
	cout<<stringW;
	fwrite(stringW, sizeof(stringW),1,out);
	for(int i =1;i<Z;i++){
		for(int j =1;j<X;j++){
			for(int k=1;k<Y;k++){
				if(getValue(data,j,k,i)>seuil){
					resultat res = isVoisInf(data, j,k,i,seuil);
					if(res.isOne){
						for(int p=0;p<6;p++){
							if(res.pos[p]==1){
								triangles = getTriangle(data,j,k,i,res.pos[p]);
								for(int l = 0;l<2;l++){
									sprintf(stringW, "%s \n",  "outer loop");
									fwrite(stringW, sizeof(stringW),1,out);
									cout<<stringW;
									sprintf(stringW, "%s %f %f %f \n",  "vertex ",*triangles[l][0],*triangles[l][1],*triangles[l][2] );
									cout<<stringW;
									fwrite(stringW, sizeof(stringW),1,out);
									sprintf(stringW, "%s %lf %lf %lf \n",  "vertex ",*triangles[l][3],*triangles[l][4],*triangles[l][5] );
									cout<<stringW;
									fwrite(stringW, sizeof(stringW),1,out);
									sprintf(stringW, "%s %lf %lf %lf \n",  "vertex ",*triangles[l][6],*triangles[l][7],*triangles[l][8] );
									cout<<stringW;
									fwrite(stringW, sizeof(stringW),1,out);
									
									sprintf(stringW, "%s \n",  "end loop" );
									cout<<stringW;
									fwrite(stringW, sizeof(stringW),1,out);
								}
							}
						}						
					}
				}
			}
		}
	}

	sprintf(stringW, "%s \n %s \n",  "end facet","endsolid name");
	cout<<stringW<<endl;
	fwrite(stringW, sizeof(stringW),1,out);
	fclose(out);
}

/*
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
}*/

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
  			max = val;
  		}
      if(val < min){
        min = val;
      }
  		data[i]=val;
  	}
    int*** dt = to3DTab(data,nbLue);
    int p = getValue(dt,200,200,20);
  	//cout<<"Voxel max : "<<max<<", Voxel min : "<<min<<", Voxel en 200,200,20 : "<<p<<endl;
  	maillage(dt, 200);


}
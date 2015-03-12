#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>


using namespace std;
int X = 256; // ligne
int Y = 256; // colonne
int Z = 100; // image

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


/*
 * Creer une image de volume rendering AIP
 */
void volumeRendering(int ***data){
  int intens;
  unsigned short *buff[1];
  FILE* out = fopen("out.0.raw","wb");
  for(int i =0;i<X;i++){
    for(int j = 0; j<Y;j++){
      intens =0;
      for(int k = 0;k<Z;k++){
        intens += getValue(data,i,j,k);
      }
      intens = intens/Z;
      int oct1 = intens/256;
      int oct2 = intens - oct1*256;
      buff[0] = (unsigned short *)(oct2*256 + oct1);
      fwrite(buff,sizeof(unsigned short),1,out);
    }
  }
  fclose(out);
}

/*
 * Creer un deux fichier : image de volume rendering MIP
 * Image de volume rendering MinIP
 */
void volumeRenderingMIPMinIP(int ***data){
  int max;
  int min;
  int res;
  unsigned short *buff[1];
  FILE* out = fopen("outMIP.0.raw","wb");
  FILE* out2 = fopen("outMinIP.0.raw","wb");
  min = getValue(data, 0,0,0);
  max = getValue(data,0,0,0);
  for(int i =0;i<X;i++){
    for(int j = 0; j<Y;j++){
      for(int k = 0;k<Z;k++){
        res = getValue(data,i,j,k);
        if(res > max){
          max = res;
        }
        if(res <min){
          min = res;
        }
      }
      int oct1 = max/256;
      int oct2 = max - oct1*256;
      buff[0] = (unsigned short *)(oct2*256 + oct1);
      fwrite(buff,sizeof(unsigned short),1,out);
      oct1 = min/256;
      oct2 = min - oct1*256;
      buff[0] = (unsigned short * )(oct2*256 + oct1);
      fwrite(buff,sizeof(unsigned short),1,out2);
    }
  }
  fclose(out);
  fclose(out2);

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
    volumeRendering(dt); // Création AIP
    volumeRenderingMIPMinIP(dt); // Création MIP et MinIP
	


}
#include "oGl6.h"
#include <iostream>
#include <fstream>

using namespace std;

void readFile(char* fileName){

	ifstream fichier(fileName, ios::in);
	char* ligne;

	if(fichier){
		getLine(fichier, ligne);
		cout<<ligne<<endl;
	}else{
		cerr<<"erreur lors de la lectur du fichier"<<endl;
	}

}
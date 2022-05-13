#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"


int calculateSizeofFile(string path) {

	fstream file;
	file.open(path, ios::in);

	string line = "";
	int cont = 0;

	if (file.is_open()) 
		while (getline(file, line)) 
			cont++; // Count lines in the file 
	else 
		cout << "Erro ao abrir o ficheiro " << path << ". Verificar novamente a localização" << endl;
	
	file.close();

	return cont;
}


string* getContentFromFiles(string path, int sizeofFile) {  

	fstream file;
	file.open(path, ios::in);
	file.clear(); // When you read the entire page, like above, you need to use this to be able to get back to the beggining
	file.seekg(0, ios::beg);  // Set position of the file to the beggining before reading

	string line;
	int cont = 0;
	string* arrayFileContent = new string[sizeofFile];  // The string array that contains every line of the file

	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			arrayFileContent[cont++] = line;  // Put the values inside of the array
		}

	} else 
		cout << "Erro ao abrir o ficheiro " << path << ". Verificar novamente a localização." << endl;
	

	file.close();

	return arrayFileContent;

}


bool verifyFiles(Filepaths* plantationFilepaths) {

	fstream file;
	bool verify = false;
	file.open(plantationFilepaths->pathDataNeeded);

	// Verifies all the paths to save and load all the plantation
	if (!file.is_open()) {
		cout << "Erro ao abrir o ficheiro" << plantationFilepaths->pathDataNeeded;
		verify = true;
	}
	file.close();

	file.open(plantationFilepaths->pathGardens);
	if (!file.is_open()) {
		cout << "Erro ao abrir o ficheiro" << plantationFilepaths->pathGardens;
		verify = true;
	}
	file.close();

	file.open(plantationFilepaths->pathStorage); 
	if (!file.is_open()) {
		cout << "Erro ao abrir o ficheiro" << plantationFilepaths->pathStorage;
		verify = true;
	}
	file.close();

	return verify;
}
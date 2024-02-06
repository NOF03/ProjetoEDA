#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"

int calculateSizeofFile(string path)
{

	fstream file;
	file.open(path, ios::in);

	string line = "";
	int cont = 0;

	if (file.is_open())
		while (getline(file, line))
			cont++; // Count lines in the file
	else
		cout << "Erro ao abrir o ficheiro " << path << ". Verificar novamente a localiza��o" << endl;

	file.close();

	return cont;
}

string *getContentFromFiles(string path, int sizeofFile)
{

	fstream file;
	file.open(path, ios::in);
	file.clear();			 // When you read the entire page, like above, you need to use this to be able to get back to the beggining
	file.seekg(0, ios::beg); // Set position of the file to the beggining before reading

	int cont = 0;
	string *arrayFileContent = new string[sizeofFile]; // The string array that contains every line of the file

	if (file.is_open())
		while (!file.eof())
			getline(file, arrayFileContent[cont++]); // Put the values inside of the array
	else
		cout << "Erro ao abrir o ficheiro " << path << ". Verificar novamente a localiza��o." << endl;

	file.close();

	return arrayFileContent;
}

void saveDataNeededFiles(DataNeeded *internalData, Filepaths *plantationFilepaths)
{

	fstream file;
	file.open(plantationFilepaths->pathDataNeeded, ios::out);
	file.clear();
	file.seekp(0, ios::beg); // Set position of the file to the beggining before writing

	file << internalData->numberofGardens << " " << internalData->numberofGardens << " " << internalData->numberofProductsToCreate;
	// Save the areas of the Gardens
	for (int i = 0; i < internalData->numberofGardens; i++)
		file << internalData->areasChoosenArray[i] << endl;

	file.close();
}

void saveGardensFiles(DataNeeded *internalData, Garden *plantationEDA, Filepaths *plantationFilepaths)
{

	fstream file;
	file.open(plantationFilepaths->pathGardens, ios::out);
	file.clear();
	file.seekp(0, ios::beg);

	// Saves the data from each Garden
	for (int i = 0; i < internalData->numberofGardens; i++)
	{

		file << plantationEDA[i].gardenorder << " "
			 << plantationEDA[i].capacity << " "
			 << plantationEDA[i].numberproducts << " "
			 << plantationEDA[i].cyclesFertilization << " "
			 << plantationEDA[i].quantityharvested;

		file << plantationEDA[i].owner << endl;
		file << plantationEDA[i].area << endl;

		// Saves the array of products in the Garden
		for (int j = 0; j < plantationEDA[i].numberproducts; j++)
		{

			file << plantationEDA[i].ingarden[j].name << endl
				 << plantationEDA[i].ingarden[j].provider << endl
				 << plantationEDA[i].ingarden[j].watering << " "
				 << plantationEDA[i].ingarden[j].resistance << " "
				 << plantationEDA[i].ingarden[j].timeplanted << " "
				 << plantationEDA[i].ingarden[j].wateringcycle;
		}
		// Saves the array of harvested products from each Garden
		for (int j = 0; j < plantationEDA[i].quantityharvested; j++) // saves the array of products sold
			file << plantationEDA[i].gardenrecord[j] << endl;
	}

	file.close();
}

void saveStorageFiles(DataNeeded *internalData, Storage *plantationStorage, Filepaths *plantationFilepaths)
{

	fstream file;
	file.open(plantationFilepaths->pathStorage, ios::out);
	file.clear();
	file.seekp(0, ios::beg);

	// Saves the number of products in Storage
	file << plantationStorage->numProducts;

	// Saves the array of products in the Storage
	for (int i = 0; i < plantationStorage->numProducts; i++)
	{
		file << plantationStorage->inStorage[i].name << endl
			 << plantationStorage->inStorage[i].area << endl
			 << plantationStorage->inStorage[i].provider << endl
			 << plantationStorage->inStorage[i].watering << " "
			 << plantationStorage->inStorage[i].resistance;
	}

	file.close();
}

void loadDataNeeded(DataNeeded *internalData, Filepaths *plantationFilepaths)
{

	fstream file;
	file.open(plantationFilepaths->pathDataNeeded, ios::in);
	file.seekg(0, ios::beg);

	file >> internalData->numberofGardens >> internalData->numberofGardens >> internalData->numberofProductsToCreate;

	delete[] internalData->areasChoosenArray;
	internalData->areasChoosenArray = new string[internalData->numberofGardens];

	// Loads the areas of the Gardens
	for (int i = 0; i < internalData->numberofGardens; i++)
		getline(file, internalData->areasChoosenArray[i]);

	file.close();
}

void loadGardens(DataNeeded *internalData, Garden *plantationEDA, Filepaths *plantationFilepaths)
{

	fstream file;
	file.open(plantationFilepaths->pathGardens, ios::in);
	file.seekg(0, ios::beg);

	delete[] plantationEDA;
	plantationEDA = new Garden[internalData->numberofGardens];

	// Loads the data to each Garden
	for (int i = 0; i < internalData->numberofGardens; i++)
	{
		file >> plantationEDA[i].gardenorder >> plantationEDA[i].capacity >> plantationEDA[i].numberproducts >> plantationEDA[i].cyclesFertilization >> plantationEDA[i].quantityharvested;
		getline(file, plantationEDA[i].owner);
		getline(file, plantationEDA[i].area);

		plantationEDA[i].ingarden = new Product[plantationEDA[i].capacity];
		plantationEDA[i].gardenrecord = new string[plantationEDA[i].quantityharvested];

		// Loads the array of products to the Garden
		for (int j = 0; j < plantationEDA[i].numberproducts; j++)
		{
			getline(file, plantationEDA[i].ingarden[j].name);
			getline(file, plantationEDA[i].ingarden[j].provider);
			file >> plantationEDA[i].ingarden[j].watering >> plantationEDA[i].ingarden[j].resistance >> plantationEDA[i].ingarden[j].timeplanted >> plantationEDA[i].ingarden[j].wateringcycle;
			plantationEDA[i].ingarden[j].area = plantationEDA[i].area;
		}
		// Loads the array of harvested products of the Garden
		for (int j = 0; j < plantationEDA[i].quantityharvested; j++)
			getline(file, plantationEDA[i].gardenrecord[j]);
	}

	file.close();
}

void loadStorage(DataNeeded *internalData, Storage *plantationStorage, Filepaths *plantationFilepaths)
{

	fstream file;
	file.open(plantationFilepaths->pathStorage, ios::in);
	file.seekg(0, ios::beg);

	delete[] plantationStorage->inStorage;

	// Loads the number os products in the Storage
	file >> plantationStorage->numProducts;

	plantationStorage->inStorage = new Product[plantationStorage->numProducts]; // Allocate the memory needed to the array

	// Loads the array of products to the Storage
	for (int i = 0; i < plantationStorage->numProducts; i++)
	{
		getline(file, plantationStorage->inStorage[i].name);
		getline(file, plantationStorage->inStorage[i].area);
		getline(file, plantationStorage->inStorage[i].provider);

		file >> plantationStorage->inStorage[i].watering >> plantationStorage->inStorage[i].resistance;
		plantationStorage->inStorage[i].timeplanted = 0;
		plantationStorage->inStorage[i].wateringcycle = 0;
	}

	file.close();
}

bool verifyFiles(Filepaths *plantationFilepaths)
{

	fstream file;
	bool verify = false;
	file.open(plantationFilepaths->pathDataNeeded);

	// Verifies all the paths to save and load all the plantation
	if (!file.is_open())
	{
		cout << "Erro ao abrir o ficheiro" << plantationFilepaths->pathDataNeeded;
		verify = true;
	}
	file.close();

	file.open(plantationFilepaths->pathGardens);
	if (!file.is_open())
	{
		cout << "Erro ao abrir o ficheiro" << plantationFilepaths->pathGardens;
		verify = true;
	}
	file.close();

	file.open(plantationFilepaths->pathStorage);
	if (!file.is_open())
	{
		cout << "Erro ao abrir o ficheiro" << plantationFilepaths->pathStorage;
		verify = true;
	}
	file.close();

	return verify;
}
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "Structs.h"
#include "Files.h"
#include "Garden.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Essential things to the program
	srand(time(NULL));
	locale::global(locale(""));

	Filepaths *gardenFilepaths = new Filepaths; // Variable that will hold all the filepaths
	DataNeeded *internalData = new DataNeeded;	// Variable that will contain all the arrays and data that we need

	// Filepaths
	gardenFilepaths->pathAreas = "areas.txt";
	gardenFilepaths->pathProviders = "fornecedores.txt";
	gardenFilepaths->pathProducts = "produtos.txt";
	gardenFilepaths->pathDataNeeded = ((argv[1] && argv[2] && argv[3]) == NULL) ? "savedDataNeeded.txt" : argv[1];
	gardenFilepaths->pathGardens = ((argv[1] && argv[2] && argv[3]) == NULL) ? "savedPlantation.txt" : argv[2];
	gardenFilepaths->pathStorage = ((argv[1] && argv[2] && argv[3]) == NULL) ? "savedStorage.txt" : argv[3];

	internalData->sizeofArea = calculateSizeofFile(gardenFilepaths->pathAreas);			  // Size of file area
	internalData->sizeofProvider = calculateSizeofFile(gardenFilepaths->pathProviders);	  // Size of file providers
	internalData->sizeofProductname = calculateSizeofFile(gardenFilepaths->pathProducts); // Size of file name

	internalData->areaArray = getContentFromFiles(gardenFilepaths->pathAreas, internalData->sizeofArea);				  // Content of file area to array
	internalData->providerArray = getContentFromFiles(gardenFilepaths->pathProviders, internalData->sizeofProvider);	  // Content of file provider to array
	internalData->productnameArray = getContentFromFiles(gardenFilepaths->pathProducts, internalData->sizeofProductname); // Content of file product to array

	internalData->numberofGardens = rand() % 6 + 5; // Number of Gardens the plantation is going to have
	cout << "A planta��o tem " << internalData->numberofGardens << " hortas." << endl;
	internalData->numberofProductsToCreate = 15;

	Garden *myplantation = new Garden[internalData->numberofGardens];
	Storage *plantationstorage = new Storage;

	inicializeGardens(internalData, myplantation);

	plantationstorage->inStorage = inicializeProducts(internalData);
	internalData->numberofProductsToCreate = 10;

	plantationMenu(internalData, myplantation, plantationstorage, gardenFilepaths);

	delete[] myplantation;
	delete internalData;
	delete gardenFilepaths;
	delete plantationstorage;
}

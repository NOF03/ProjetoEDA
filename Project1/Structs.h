#pragma once
#include <string>

using namespace std;

// Struct to contain all the files
struct Filepaths
{
	string pathAreas = "";		// String that holds the directory of "areas.txt"
	string pathProviders = "";	// String that holds the directory of "fornecedores.txt"
	string pathProducts = "";	// String that holds the directory of "produtos.txt"
	string pathGardens = "";	// String that holds the directory of "savedPlantation.txt"
	string pathDataNeeded = ""; // String that holds the directory of "savedDataNeeded.txt"
	string pathStorage = "";	// String that holds the directory of "savedStorage.txt"
};

// Struct of the product
struct Product
{
	string name = "";	   // Name of the product
	string area = "";	   // Product area (equal to the Garden area)
	string provider = "";  // The provider of the product
	int resistance = 0;	   // Resistance of the product
	int watering = 0;	   // Watering time of the product
	int wateringcycle = 0; // Count cycles before each watering
	int timeplanted = 0;   // Count the time planted of the product
};

// Struct that holds essential data for the program
struct DataNeeded
{
	int numberofGardens = 0;				// Contains the number of gardens on the plantation
	int sizeofArea = 0;						// Contains the size of the array area
	int sizeofProvider = 0;					// Contains the size of the array provideer
	int sizeofProductname = 0;				// Contains the size of the array name
	int numberofProductsToCreate = 0;		// Contains the number os products to create each cycle
	string *areaArray = new string;			// Array that will keep all the areas from the file
	string *providerArray = new string;		// Array that will keep all providers from the file
	string *productnameArray = new string;	// Array that will keep all the names from the file
	string *areasChoosenArray = new string; // Array that will contain only the areas that are being used
};

// Struct of the garden
struct Garden
{
	char gardenorder = ' ';											   // Order of the Garden
	int capacity = 0;												   // Max number of products the Garden can support
	int numberproducts = 0;											   // Number of products in the Garden
	Product *ingarden = new Product;								   // Products in the Garden
	string *gardenrecord = new string; // Harvested Products of the Garden
	string owner = "";												   // Owner of the Garden
	string area = "";												   // Area of the Garden
	int quantityharvested = 0;										   // Number of harvested products of the Garden
	int cyclesFertilization = 0;									   // Counter of fertilization cycles
};

// Struct of the Storage
struct Storage
{
	Product *inStorage = new Product; // Array that holds all the products in Storage
	int numProducts = 15;			  // Number of products in the Storage
};

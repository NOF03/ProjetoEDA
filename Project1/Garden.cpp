#include <iostream>
#include <string>
#include "Garden.h"
#include "Management.h"

using namespace std;

void inicializeGardens(DataNeeded *internalData, Garden *plantationEDA)
{
	internalData->areasChoosenArray = new string[internalData->numberofGardens];
	// Variables
	auto verifyOwner = [](string& owner, char& order) {
		do
		{
			cout << "Digite o nome do responsável da horta " << order << ": ";
			getline(cin, owner);

			if (!owner.empty()) { // In case the inserted name equals an empty string
				system("cls");
				return;
			}
			cout << "Não pode deixar este espaço em branco!\n" << endl;

		} while (true);
		};
	// Loops through all the gardens
	for (int i = 0; i < internalData->numberofGardens; i++)
	{

		plantationEDA[i].gardenorder = 'A' + i;						        // Order of the Garden
		plantationEDA[i].capacity = rand() % 6 + 3;							// Random capacity of the Garden between 3 and 8
		plantationEDA[i].ingarden = new Product[plantationEDA[i].capacity]; // Creation of the array of products with the capacity of the Garden
		plantationEDA[i].gardenrecord = new string[1];		// Creation of array for the havested products
		internalData->areasChoosenArray[i] = plantationEDA[i].area = internalData->areaArray[rand() % internalData->sizeofArea]; // Going to the array area and choosing a random area for the garden
		verifyOwner(plantationEDA[i].owner, plantationEDA[i].gardenorder);
	}

	delete[] internalData->areaArray; // Since we already choose which areas to use this array is no longer needed
}

Product *inicializeProducts(DataNeeded *internalData)
{

	Product *allProducts = new Product[internalData->numberofProductsToCreate];

	for (int i = 0; i < internalData->numberofProductsToCreate; i++)
	{
		allProducts[i].name = internalData->productnameArray[rand() % internalData->sizeofProductname];	  // Chooses a random name from the array and gives it to the product
		allProducts[i].area = internalData->areasChoosenArray[rand() % internalData->numberofGardens]; // Chooses a random area only from the areas that have already been selected for the sectors
		allProducts[i].provider = internalData->providerArray[rand() % internalData->sizeofProvider];	  // Chooses a random provider from the array and gives it to the product
		allProducts[i].resistance = (rand() % 11) * 10;													  // Gives a random watering time between 1 and 5
		allProducts[i].watering = allProducts[i].wateringcycle = rand() % 5 + 1;						  // Gives a random resistance between 0 and 100
	}
	return allProducts;
}

void display(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage)
{
	// Displays the essential information about the Garden
	for (int i = 0; i < internalData->numberofGardens; i++)
	{
		cout << "Horta: " << plantationEDA[i].gardenorder << " | "
			 << "Respons�vel: " << plantationEDA[i].owner << " | "
			 << "Capacidade: " << plantationEDA[i].capacity << " | "
			 << "Produtos: " << plantationEDA[i].numberproducts << " | "
			 << "�rea: " << plantationEDA[i].area << endl;
		// Displays the products inside the Gardens
		for (int j = 0; j < plantationEDA[i].numberproducts; j++)
		{
			cout << "Produto: " << plantationEDA[i].ingarden[j].name << " | "
				 << "Rega: " << plantationEDA[i].ingarden[j].watering << " | "
				 << "Resist�ncia: " << plantationEDA[i].ingarden[j].resistance << "%" << endl;
		}
		cout << "---------------------------------" << endl;
	}
	cout << endl
		 << endl;

	cout << "Armaz�m:" << endl
		 << endl;
	// Displays the products inside the Storage
	for (int i = 0; i < plantationStorage->numProducts; i++)
	{
		cout << "Nome: " << plantationStorage->inStorage[i].name << " | "
			 << "Resist�ncia: " << plantationStorage->inStorage[i].resistance << "% | "
			 << "�rea: " << plantationStorage->inStorage[i].area << endl;
	}
	cout << endl
		 << endl;
}

void addProductsToRecord(Product productharvested, Garden *plantationEDA, int x)
{
	// Internal array with the size of harvested products + 1 to add the new product
	string *internRecord = new string[plantationEDA[x].quantityharvested + 1];

	// Loop to pass the products already stored in the original array to this own
	for (int j = 0; j < plantationEDA[x].quantityharvested; j++)
		internRecord[j] = plantationEDA[x].gardenrecord[j];

	internRecord[plantationEDA[x].quantityharvested] = productharvested.name; // Adds the products name to the internal array

	delete[] plantationEDA[x].gardenrecord; // Deletes the array of the record
	 
	plantationEDA[x].quantityharvested++;		  // Allocates the memory with the updated number of harvested products
	plantationEDA[x].gardenrecord = internRecord; // Passes the information of the internal array to the original array
}

void verifyProductHarvested(Garden *plantationEDA, DataNeeded *internalData)
{
	// Loops through all the Gardens
	for (int i = 0; i < internalData->numberofGardens; i++)
	{

		int cont1 = 0;
		Product *internProduct = new Product[plantationEDA[i].capacity]; // Allocates the memory of internal array with the capacity of the Garden

		for (int j = 0; j < plantationEDA[i].numberproducts; j++)
		{
			// Product have 25% chance to get haversted
			if (rand() % 3 == 0)
				addProductsToRecord(plantationEDA[i].ingarden[j], plantationEDA, i);
			else
				internProduct[cont1++] = plantationEDA[i].ingarden[j];
		}

		plantationEDA[i].numberproducts = cont1; // Updates the number of products in the Garden
		plantationEDA[i].ingarden = internProduct;
	}
}

void createNewProducts(Storage *plantationStorage, DataNeeded *internalData)
{
	// Variables
	int cont = 0, cont1 = plantationStorage->numProducts;

	Product *internManagement = new Product[internalData->numberofProductsToCreate + plantationStorage->numProducts]; // Internal array that will receive all the products in Garden
	Product *internManagement1 = new Product[internalData->numberofProductsToCreate];								  // Internal array that will receive all the new Products

	for (int i = 0; i < cont1; i++)
		internManagement[i] = plantationStorage->inStorage[i];

	internManagement1 = inicializeProducts(internalData); // Create the new Products saved in the array

	delete[] plantationStorage->inStorage;																				 // Deallocates the memory in the Storage
	plantationStorage->inStorage = new Product[plantationStorage->numProducts + internalData->numberofProductsToCreate]; // Allocates the memory of Storage necessary
	plantationStorage->inStorage = internManagement;																	 // Receives the elements from the first array

	for (int i = plantationStorage->numProducts; i < cont1 + internalData->numberofProductsToCreate; i++)
		plantationStorage->inStorage[plantationStorage->numProducts++] = internManagement1[cont++]; // Receives the elements from the second array

	// Sort by name and area and time in storage using Bubble Sort
	for (int i = 0; i < plantationStorage->numProducts - 1; i++)
		for (int j = plantationStorage->numProducts - 1; j > i; j--)
			if (plantationStorage->inStorage[j].name == plantationStorage->inStorage[i].name && plantationStorage->inStorage[j].area == plantationStorage->inStorage[i].area)
				swap(plantationStorage->inStorage[j], plantationStorage->inStorage[j - 1]);
}

void assignProductsToGardens(Garden *plantationEDA, Storage *plantationStorage, DataNeeded *internalData)
{
	// Variables
	int cont1 = 0, cont2 = 0, cont3 = 0;
	bool sair = false;

	Product *internalproduct = new Product[plantationStorage->numProducts]; // Internal array that will receive some of the products from Storage

	do
	{
		// Loops through all the gardens
		for (int i = 0; i < internalData->numberofGardens; i++)
		{
			if (plantationEDA[i].area == plantationStorage->inStorage[cont2].area)
			{
				if (plantationEDA[i].capacity > plantationEDA[i].numberproducts)
				{

					plantationEDA[i].ingarden[plantationEDA[i].numberproducts++] = plantationStorage->inStorage[cont2++]; // Adds to the Garden the product from the Storage
					cont1++;																							  // Counter of products assigned to Gardens
					break;
				}
			}
			if (i == internalData->numberofGardens - 1)							  // If it has checked all the Gardens and didn�t find one available passes to the next product
				internalproduct[cont3++] = plantationStorage->inStorage[cont2++]; // Saves the product to an internal array

			if (cont2 == plantationStorage->numProducts)
			{ // If it has checked all products it leaves the loop

				sair = true;
				break;
			}
		}
	} while (cont1 != 10 && !sair); // Leaves the loop if 10 products were added to Gardens or if can't be added more products to the Gardens

	for (int i = cont2; i < plantationStorage->numProducts; i++) // Saves the remain products of the Storage to the internal array
		internalproduct[cont3++] = plantationStorage->inStorage[i];


	plantationStorage->inStorage = internalproduct; // Adds all the products, that weren't assigned to a Garden, to the Storage
	plantationStorage->numProducts = cont3;		// Updates the number of products in the Storage
}

void plague(DataNeeded *internalData, Garden *plantationEDA)
{
	// Loops through all the Gardens
	for (int i = 0; i < internalData->numberofGardens; i++)
	{
		int cont1 = 0, prob = 0;
		Product *internProduct = new Product[plantationEDA[i].capacity]; // Allocates the memory of internal array with the capacity of the Garden

		// Loops through all the products in the Garden
		for (int j = 0; j < plantationEDA[i].numberproducts; j++)
		{
			prob = 100 - plantationEDA[i].ingarden[j].resistance; // Probability of being infected by the plague
			if (plantationEDA[i].ingarden[j].wateringcycle == 1)
			{ // Plague acts the day before of the watering
				if ((rand() % 100 + 1) > prob)
				{

					internProduct[cont1++] = plantationEDA[i].ingarden[j]; // Saves the products that weren't infected by the plague
					plantationEDA[i].ingarden[j].wateringcycle = plantationEDA[i].ingarden[j].watering;
				}
				else
					cout << "Perdeu o produto " << plantationEDA[i].ingarden[j].name << " da horta " << plantationEDA[i].gardenorder << endl;
			}
			else
			{

				internProduct[cont1++] = plantationEDA[i].ingarden[j]; // Saves the products that can't be acted by the plague
				plantationEDA[i].ingarden[j].wateringcycle--;
			}
		}

		plantationEDA[i].numberproducts = cont1; // New number of products in the Garden
		plantationEDA[i].ingarden = internProduct;
	}
}

void verifyFertilization(DataNeeded *internalData, Garden *plantationEDA)
{
	// Loops through all the Gardens
	for (int i = 0; i < internalData->numberofGardens; i++)
	{
		if (plantationEDA[i].cyclesFertilization > 0)
		{ // Verifies if an area is being fertilized
			// Loops through all the products in the Garden
			for (int j = 0; j < plantationEDA[i].numberproducts; j++) // Updates the resistance of products in the Garden by 10
				if (plantationEDA[i].ingarden[j].resistance < 100)
					plantationEDA[i].ingarden[j].resistance += 10;

			plantationEDA[i].cyclesFertilization--; // Decreases the number of cycles that remains for the Fertilization
		}
	}
}

void timePlanted(DataNeeded *internalData, Garden *plantationEDA)
{
	// Loops through all the Gardens
	for (int i = 0; i < internalData->numberofGardens; i++)
		// Loops through all the products in the Garden
		for (int j = 0; j < plantationEDA[i].numberproducts; j++)
			plantationEDA[i].ingarden[j].timeplanted++; // Increases the timeplanted of a product (Increased by cycle)
}

void plantationMenu(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage, Filepaths *plantationFilepaths)
{
	// Variables
	char option = ' ';
	bool sair = false;

	do
	{
		display(internalData, plantationEDA, plantationStorage);

		cout << " (s)eguinte  ***********  (g)est�o  ***********  (0)sair" << endl;
		cout << "Selecione a sua op��o:";
		cin >> option;
		cout << endl
			 << "---------------------------------" << endl;

		switch (option)
		{
		case 's':
			timePlanted(internalData, plantationEDA);
			verifyProductHarvested(plantationEDA, internalData);
			verifyFertilization(internalData, plantationEDA);
			plague(internalData, plantationEDA);
			cout << "---------------------------------" << endl;
			createNewProducts(plantationStorage, internalData);
			assignProductsToGardens(plantationEDA, plantationStorage, internalData);
			break;
		case 'g':
			managementMenu(internalData, plantationEDA, plantationStorage, plantationFilepaths);
			break;
		case '0':
			sair = true;
			cout << "Obrigado por usar o nosso programa! " << endl;
			break;
		default:
			cout << "Inseriu uma op��o inv�lida!" << endl;
			break;
		}
	} while (!sair);
}
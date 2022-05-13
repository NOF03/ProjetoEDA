#include <iostream>
#include <string>
#include "Garden.h"
#include "Management.h"

using namespace std;

int length(LLProducts* head){
	LLProducts* current = head; 
	int count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}

Garden createGarden(DataNeeded* internalData, char id) {
	
	string nome;
	Garden newGarden;
	newGarden.gardenorder = id;
	newGarden.capacity = rand() % 6 + 3;
	bool sair = false;
	do {
		std::cout << "Digite o nome do responsável da horta " << newGarden.gardenorder << ": ";
		getline(cin, nome);

		if (nome != "\0")  // In case the inserted name equals an empty string
			sair = true;
		else
			std::cout << "Não pode deixar este espaço em branco!\n" << endl;


	} while (!sair);

	newGarden.owner = nome; // Adds the name given to the owner of the garden
	newGarden.area = internalData->areaArray[rand() % internalData->sizeofArea]; // Going to the array area and choosing a random area for the garden
	return newGarden;
}


void inicializeGardens(DataNeeded* internalData, LLGardens** plantationEDA) {
	// Variables
	char characters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' }; // Array that will have the character order of a Garden
	string nome;
	
	// Loops through all the gardens
	for (int i = 0; i < internalData->numberofGardens; i++) {

		LLGardens* newGarden = new LLGardens;
		newGarden->oneGarden = createGarden(internalData, characters[i]);

		if (i == 0) {
			newGarden->next = NULL;
			*plantationEDA = newGarden;
		}
					
		else {
			LLGardens* it = *plantationEDA;
			while (it->next != NULL)
				it = it->next;

			it->next = newGarden;
		}
	}

	system("cls");

}


Product inicializeProducts(DataNeeded* internalData) {

	Product oneProduct;

	oneProduct.name = internalData->productnameArray[rand() % internalData->sizeofProductname];  // Chooses a random name from the array and gives it to the product
	oneProduct.area = internalData->areaArray[rand() % internalData->sizeofArea];  // Chooses a random area only from the areas that have already been selected for the sectors
	oneProduct.provider = internalData->providerArray[rand() % internalData->sizeofProvider];  // Chooses a random provider from the array and gives it to the product 
	oneProduct.resistance = (rand() % 7 + 2.0) / 10; // Gives a random resistance between 0 and 100
	oneProduct.watering = oneProduct.wateringcycle = rand() % 5 + 1; // Gives a random watering time between 1 and 5

	return oneProduct;
}


void display(DataNeeded* internalData, LLGardens* plantationEDA, LLProducts* plantationStorage) { 
	// Displays the essential information about the Garden 
	LLGardens* itPlantation = plantationEDA;

	while (itPlantation != NULL) {
		cout << "Horta: " << itPlantation->oneGarden.gardenorder << " | "
			<< "Responsável: " << itPlantation->oneGarden.owner << " | "
			<< "Capacidade: " << itPlantation->oneGarden.capacity << " | "
			<< "Produtos: " << itPlantation->oneGarden.numberproducts << " | "
			<< "Área: " << itPlantation->oneGarden.area << endl;
		// Displays the products inside the Gardens
		LLProducts* itProducts = itPlantation->oneGarden.ingarden;
		while (itProducts != NULL) {
			cout << "Produto: " << itProducts->data.name << " | "
				<< "Rega: " << itProducts->data.watering << " | "
				<< "Tempo Plantado: " << itProducts->data.timeplanted << " | "
				<< "Resistência: " << itProducts->data.resistance * 100 << "%" << endl;
			itProducts = itProducts->next;
		}
		cout << "---------------------------------" << endl;
		itPlantation = itPlantation->next;
	} cout << endl << endl;
	LLProducts* internalStorage = plantationStorage;

	cout << "Armazém:" << endl << endl;
	// Displays the products inside the Storage
	while (internalStorage != NULL) {
		cout << "Nome: " << internalStorage->data.name << " | "
			<< "Resistência: " << internalStorage->data.resistance*100 << "% | "
			<< "Área: " << internalStorage->data.area << endl;
		internalStorage = internalStorage->next;
	} cout << endl << endl; 
}


void createNewProducts(LLProducts** plantationStorage, DataNeeded* internalData) {
	
	for (int i = 0; i < internalData->numberofProductsToCreate; i++) {

		LLProducts* internalStorage = new LLProducts;
		internalStorage->data = inicializeProducts(internalData);

		if ((i == 0 && internalData->numberofProductsToCreate == 15) || plantationStorage == NULL ) {
			internalStorage->next = NULL;
			*plantationStorage = internalStorage;
			
		}
		else {

			LLProducts* it = *plantationStorage;

			while (it->next != NULL) 
				it = it->next;
			
			it->next = internalStorage;
			internalStorage->next = NULL;

			
		}

	}
	
}
void insertProductinGarden(LLGardens** plantationEDA, Product addProduct, int position) {

	LLGardens* itPlantation = *plantationEDA;
	int count = 0;
	while (count < position ) {
		itPlantation = itPlantation->next;
		count++;
	}

	LLProducts* newProduct = new LLProducts;
	newProduct->data = addProduct;

	if (itPlantation->oneGarden.ingarden == NULL) {
		
		newProduct->next = NULL;
		itPlantation->oneGarden.ingarden = newProduct;
	} else {
		LLProducts* itProducts = itPlantation->oneGarden.ingarden;

		while (itProducts->next != NULL) {
			itProducts = itProducts->next;
		}
		newProduct->next = NULL;
		itProducts->next = newProduct;

	}

}

void removeProductfromStorage(LLProducts** oneList, int position) {

	if (position == 0) {
		if (oneList == NULL)
			oneList = NULL;
		else {
			LLProducts* aux = *oneList;
			*oneList = aux->next;
			delete aux;
		}
	}
	else if (position == length(*oneList) - 1) {
		LLProducts* iterator = *oneList;

		while (iterator->next->next != NULL) {
			iterator = iterator->next;
		}

		delete iterator->next;
		iterator->next = NULL;
	}
	else {

		LLProducts* itList = *oneList;
		LLProducts* itList2 = *oneList;
		int count = 0;
		while (count != (position - 1)) {
			itList = itList->next;
			count++;
		}

		itList2 = itList->next->next;
		delete itList->next;
		itList->next = itList2;
	}

}

void assignProductsToGardens(LLGardens** plantationEDA, LLProducts** plantationStorage, DataNeeded* internalData) {

	int cont = 0;
	int position2 = 0;
	bool productAdded = false;
	LLProducts* itStorage = *plantationStorage;


	while (itStorage != NULL) {
		if (cont == 10) break;
		LLGardens* itPlantation = *plantationEDA;
		int position = 0;

		while (itPlantation != NULL) {
			if (cont == 10) break;
			productAdded = false;
			if (itStorage->data.area == itPlantation->oneGarden.area && itPlantation->oneGarden.numberproducts < itPlantation->oneGarden.capacity) {

				insertProductinGarden(plantationEDA, itStorage->data, position);
				removeProductfromStorage(plantationStorage, position2);

				itStorage = *plantationStorage;
				productAdded = true;
				if (position2 != 0)
					position2--;
				for (int i = 0; i < position2; i++)
					itStorage = itStorage->next;
				itPlantation->oneGarden.numberproducts++;
				cont++;
				break;
			}
			if (!productAdded) {
				itPlantation = itPlantation->next;
				position++;
			}

		}
		if (position2 != 0 || !productAdded) {
			itStorage = itStorage->next;
			position2++;
		}
		if (cont == 10) break;
	}

}

void newNode(ProductHarvestedRecord** harvestedlist, string data) {
	ProductHarvestedRecord* node = new  ProductHarvestedRecord;
	node->name = data;
	node->left = NULL;
	node->right = NULL;
	*harvestedlist = node;
}


void addProductstoRecord(ProductHarvestedRecord** harvestedlist, string data) {
	
	ProductHarvestedRecord* aux = *harvestedlist;

	if (aux == NULL)
		newNode(harvestedlist, data);
	else {
		if (data <= aux->name)
			addProductstoRecord(&aux->left, data);
		else
			addProductstoRecord(&aux->right, data);
	}
		

}

void removeProductfromGardens(LLProducts** listproducts , int position) {

	if (position == 0) {
		if (listproducts == NULL)
			listproducts = NULL;
		else {
			LLProducts* aux = *listproducts;
			*listproducts = aux->next;
			delete aux;
		}
	}
	else if (position == length(*listproducts) - 1) {
		LLProducts* iterator = *listproducts;

		while (iterator->next->next != NULL) {
			iterator = iterator->next;
		}

		delete iterator->next;
		iterator->next = NULL;
	}
	else {

		LLProducts* itList = *listproducts;
		LLProducts* itList2 = *listproducts;
		int count = 0;
		while (count != (position - 1)) {
			itList = itList->next;
			count++;
		}

		itList2 = itList->next->next;
		delete itList->next;
		itList->next = itList2;
	}

}

void verifyProductHarvested(LLGardens** plantationEDA) {

	LLGardens* itGardens = *plantationEDA;

	while (itGardens != NULL) {

		LLProducts* itProducts = itGardens->oneGarden.ingarden;
		int counter = 0;
		while (itProducts != NULL) {
			if (rand() % 3 == 0) {
				addProductstoRecord(&itGardens->oneGarden.gardenrecord, itProducts->data.name);
				removeProductfromGardens(&itGardens->oneGarden.ingarden, counter);
				itProducts = itGardens->oneGarden.ingarden;
				for (int i = 0; i < counter; i++)
					itProducts = itProducts->next;
			}
			else {
				itProducts = itProducts->next;
				counter++;
			}
		}
		itGardens = itGardens->next;
	}

}


void plague(LLGardens** plantationEDA) {

	LLGardens* itGardens = *plantationEDA;

	while (itGardens != NULL) {

		LLProducts* itProducts = itGardens->oneGarden.ingarden;
		int counter = 0;

		while (itProducts != NULL) {
			
			bool removedProduct = false;

			if (itProducts->data.wateringcycle == 1) {
				if ((rand() % 100 + 1) > itProducts->data.resistance * 100) {

					cout << "Perdeu o produto " << itProducts->data.name << " da horta " << itGardens->oneGarden.gardenorder << endl;
					removeProductfromGardens(&itGardens->oneGarden.ingarden , counter);

					itProducts = itGardens->oneGarden.ingarden;
					for (int i = 0; i < counter; i++)
						itProducts = itProducts->next;
					removedProduct = true;

				} else 
					itProducts->data.wateringcycle = itProducts->data.watering;

				
			} else 
				itProducts->data.wateringcycle--;
			
			if (!removedProduct) {
				itProducts = itProducts->next;
				counter++;
			}
			
		}
		itGardens = itGardens->next;
	}

}


void timePlanted(LLGardens** plantationEDA) {

	LLGardens* itGardens = *plantationEDA;

	while (itGardens != NULL) {
		LLProducts* itProducts = itGardens->oneGarden.ingarden;
		while (itProducts != NULL) {
			itProducts->data.timeplanted++;
			itProducts = itProducts->next;
		}
		itGardens = itGardens->next;
	}
}


void plantationMenu(DataNeeded* internalData, LLGardens* plantationEDA, LLProducts* plantationStorage, Filepaths* plantationFilepaths) {
	// Variables
	char option = ' ';
	bool sair = false;

	do {
		display(internalData, plantationEDA, plantationStorage); 

		
		cout << " (s)eguinte  ***********  (g)estão  ***********  (0)sair" << endl;
		cout << "Selecione a sua opção:";
		cin >> option;
		cout << endl << "---------------------------------" << endl ;

		switch (option) {
		case 's':
			timePlanted(&plantationEDA);
			verifyProductHarvested(&plantationEDA);
			//verifyFertilization(internalData, plantationEDA);
			plague(&plantationEDA);
			cout << "---------------------------------" << endl;
			assignProductsToGardens(&plantationEDA, &plantationStorage, internalData);
			createNewProducts(&plantationStorage, internalData);
			break;
		case 'g':
			managementMenu(internalData, plantationEDA, plantationStorage, plantationFilepaths);
			break;
		case'0':
			sair = true;
			cout << "Obrigado por usar o nosso programa! " << endl;
			break;
		default:
			cout << "Inseriu uma opção inválida!" << endl;
			break;
		}
	} while (!sair);
}
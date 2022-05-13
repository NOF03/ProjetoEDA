#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"
#include "Garden.h"
#include "Management.h"

using namespace std;
/*
void harvestProduct(DataNeeded* internalData, Garden* plantationEDA) {
	// Variables
	string str;
	int cont = 0;
	bool sair = false;

	cin.ignore();

	// Verify if there's a product with the inserted name
	do {
		cout << "Digite o nome do produto a colher: ";
		getline(cin, str);
		// Loops through all Gardens
		for (int i = 0; i < internalData->numberofGardens; i++)
			// Loops through all the products in the Garden
			for (int j = 0; j < plantationEDA[i].numberproducts; j++)
				if (str == plantationEDA[i].ingarden[j].name) // If inserted name is equal to one of products in the Garden it leaves the loop
					sair = true;

		if (!sair)
			cout << "Esse produto n�o est� plantado ou n�o existe" << endl;
	} while (!sair);
	
	// Loops through all Gardens
	for (int i = 0; i < internalData->numberofGardens; i++) {

		Product* internproduct = new Product[plantationEDA[i].numberproducts]; // Internal array with the number of products in a Garden
		int cont1 = 0; 
		int cont2 = plantationEDA[i].numberproducts; 
		// Loops through all the products in the Garden
		for (int j = 0; j < cont2; j++) {
			if (str != plantationEDA[i].ingarden[j].name)
				internproduct[cont1++] = plantationEDA[i].ingarden[j]; // Adds the other products to the internal array
			else {
				//addProductsToRecord(plantationEDA[i].ingarden[j], plantationEDA, i); // Product is added to the harvest products record
				plantationEDA[i].numberproducts--; // Updates number of products in the garden
				cont++; // Variable with the number of products havested
			}
		}

		delete[] plantationEDA[i].ingarden; // Deletes the array with the products in the Garden
		plantationEDA[i].ingarden = new Product[plantationEDA[i].capacity]; // Allocates the memory again with the Garden capacity
		plantationEDA[i].ingarden = internproduct; // Updates the products in the Garden
	}

	cout << endl << "Foram colhidos " << cont << " produto(s)." << endl;
}


void updatewatering(DataNeeded* internalData, Garden* plantationEDA, Product* plantationStorage) {
	// Variables
	string str;
	int watering = 0;
	bool sair = false;

	cin.ignore();
	// Verify if there's a product with the inserted name
	do {
		cout << "Digite o nome do produto que quer atualizar o tempo de rega: ";
		getline(cin, str);

		for (int i = 0; i < internalData->numberofGardens; i++)
			for (int j = 0; j < plantationEDA[i].numberproducts; j++)
				if (str == plantationEDA[i].ingarden[j].name) // If inserted name is equal to one of products in the Garden it leaves the loop
					sair = true;


		//for (int i = 0; i < plantationStorage->numProducts; i++)
			//if (str == plantationStorage->inStorage[i].name) // If inserted name is equal to one of products in the Storage it leaves the loop
				//sair = true;

		if (!sair)
			cout << "Esse produto n�o existe" << endl;
	} while (!sair);
	
	sair = false;
	
	// Verify if the inserted watering time is valid
	do {
		cout << "Insira o novo tempo de rega (1-5): ";
		cin >> watering;

		if (watering < 1 || watering > 5)
			cout << "N�o pode inserir esse valor" << endl;
		else
			sair = true;

	} while (!sair);
	// Updates watering time for the product
	for (int i = 0; i < internalData->numberofGardens; i++) 
		for (int j = 0; j < plantationEDA[i].numberproducts; j++) 
			if (str == plantationEDA[i].ingarden[j].name)  
				plantationEDA[i].ingarden[j].watering = watering;

	//for (int  i = 0; i < plantationStorage->numProducts; i++) 
		//if (str == plantationStorage->inStorage[i].name) 
		//	plantationStorage->inStorage[i].watering = watering;

	cout << endl << "Tempo de rega atualizado!" << endl;

}


void fertilization(DataNeeded* internalData, Garden* plantationEDA) {
	// Variables
	string str;
	int timefertilized = 0;
	bool sair = false;

	cin.ignore();
	// Verify if the time of fertilization is valid
	do{
		cout << "Insira quantos dias quer fertilizar: ";
		cin >> timefertilized;

		if (timefertilized < 0) 
			cout << "Insira um acima ou igual a 0!" << endl;
		else
			sair = true;
	} while (!sair);
	
	sair = false;
	cin.ignore();

	do {

		cout << "Indique a �rea que quer fertilizar: ";
		getline(cin, str);

		for (int i = 0; i < internalData->numberofGardens; i++) // Updates the time that the area will be fertilized
			if (str == plantationEDA[i].area) 
				plantationEDA[i].cyclesFertilization = timefertilized;	
		
		for (int i = 0; i < internalData->sizeofAreasChoosen; i++) // Verifies if the area is available
			if (str == internalData->areaArray[i]) 
				sair = true;

		if (!sair) 
			cout << "Essa �rea n�o existe, insira uma �rea existente! " << endl;
		
		cin.clear();
	} while (!sair);

	cout << endl << "�rea fertilizada com sucesso!" << endl;
}


void recordPlantation(DataNeeded* internalData, Garden* plantationEDA, Product* plantationStorage, Filepaths* plantationfilepaths) {
	// Verifies the Directory Paths
	if (verifyFiles(plantationfilepaths) == false) {
		// Execute the save to the Directory
		//saveDataNeededFiles(internalData, plantationfilepaths);
		//saveGardensFiles(internalData, plantationEDA, plantationfilepaths);
		//saveStorageFiles(internalData, plantationStorage, plantationfilepaths);
		cout << "Planta��o gravada com sucesso!" << endl;
	} else
		cout << endl << "A planta��o n�o foi gravada!" << endl;
}


void loadPlantation(DataNeeded* internalData, Garden* plantationEDA, Product* plantationStorage, Filepaths* plantationfilepaths) {
	// Variables
	char option;
	string str;
	bool sair = false;
	
	do {
		cout << "Quais os ficheiros que quer carregar?\n (1)Ficheiros Locais\n (2)Outros Ficheiros \nSelecione a sua op��o: ";
		cin >> option;

		cin.ignore();
		switch (option) {
		case '1':
			// Verifies the Directory Paths
			if (verifyFiles(plantationfilepaths) == false) {
				// Execute the load from the Directory
				//loadDataNeeded(internalData, plantationfilepaths);
				//loadGardens(internalData, plantationEDA, plantationfilepaths);
				//loadStorage(internalData, plantationStorage, plantationfilepaths);
				cout << endl << "A planta��o foi carregada com sucesso!" << endl;
			}
			else
				cout << endl << "A planta��o n�o foi carregada!" << endl;
			sair = true;
			break;
		case '2':
			// Change Diretory of the files
			cout << "Insira o diret�rio do DataNeeded: ";
			getline(cin, str);
			plantationfilepaths->pathDataNeeded = str;

			cout << "Insira o diret�rio das Hortas: ";
			getline(cin, str);
			plantationfilepaths->pathGardens = str;

			cout << "Insira o diret�rio do Armaz�m: ";
			getline(cin, str);
			plantationfilepaths->pathStorage = str;

			// Verifies the Directory Paths
			if (verifyFiles(plantationfilepaths) == false) {
				// Execute the load from the Directory
				//loadDataNeeded(internalData, plantationfilepaths);
				//loadGardens(internalData, plantationEDA, plantationfilepaths);
				//loadStorage(internalData, plantationStorage, plantationfilepaths);
				cout << endl << "A planta��o foi carregada com sucesso!" << endl;
			} else
				cout << endl << "A planta��o n�o foi carregada!" << endl;
			sair = true;
			break;
		default:
			cout << "Insira um n�mero v�lido!" << endl;
		}
		
	} while (!sair);
	
	
}


void alphabeticalOrder(Product* allProducts, int size) {

	Product* temp = allProducts;

	// Turn uppercase letters into lowercase
	for (int i = 0; i < size; i++) 
		if (temp[i].name[0] < 91 && temp[i].name[0] > 64)
			temp[i].name[0] += 32;
	// Sort alphabetically
	for (int i = 0; i < size; i++) 
		for (int j = i + 1; j < size; j++) 
			if (temp[j].name < temp[i].name) // Sort by name
				swap(temp[i], temp[j]);

	// Print the alphabeticalOrder 
	cout << endl << "Ordem alfabetica: " << endl;
	for (int i = 0; i < size; i++) 
		cout << "Nome: " << temp[i].name << " | "
			 << "Fornecedor: " << temp[i].provider << " | "
			 << "Tempo Plantado: " << temp[i].timeplanted << endl;
	
}


void timeplantedOrder(Product* allProducts, int size) {

	Product* temp = allProducts;
	// Turn uppercase letters into lowercase
	for (int i = 0; i < size; i++) 
		if (temp[i].name[0] < 91 && temp[i].name[0] > 64)
			temp[i].name[0] += 32;
	// Sort alphabetically
	for (int i = 0; i < size; i++) 
		for (int j = i + 1; j < size; j++) 
			if (temp[j].timeplanted < temp[i].timeplanted) // Sort by time planted
				swap(temp[i], temp[j]);
		

	// Print the timeplantedOrder 
	cout << endl << "Por tempo plantado: " << endl;
	for (int i = 0; i < size; i++) 
		cout << "Nome: " << temp[i].name << " | "
			<< "Fornecedor: " << temp[i].provider << " | "
			<< "Tempo Plantado: " << temp[i].timeplanted << endl;
}*/


/*void printProducts(DataNeeded* internalData, Garden* plantationEDA, Storage* plantationStorage) {
	// Variables
	int size = plantationStorage->numProducts;  // Variable with the number of products in the Storage
	int cont = 0;
	bool sair = false;
	char opcao = ' ';

	for (int i = 0; i < internalData->numberofGardens; i++) // Adds to size the number of products in the plantation
		size += plantationEDA[i].numberproducts;

	Product* allProducts = new Product[size]; // Array that holds all the products

	for (int i = 0; i < internalData->numberofGardens; i++) // Insert all the products in the Plantation to the array
		for (int j = 0; j < plantationEDA[i].numberproducts; j++)
			allProducts[cont++] = plantationEDA[i].ingarden[j];

	for (int i = 0; i < plantationStorage->numProducts; i++) // Insert all the products in the Storage to the array
		allProducts[cont++] = plantationStorage->inStorage[i];


	do { // Menu with the choices
	
		cout << endl << "Deseja ter os produtos ordenados por nome ou por tempo plantado? " << endl
		     << "(1) Por Nome" << endl
			<< "(2) Por Tempo Plantado" << endl
			<< "(0) Sair" << endl;

		cout << "Digite a sua opcao: ";
		cin >> opcao;

		switch (opcao) {
		case'1':
			alphabeticalOrder(allProducts, size);
			break;
		case'2':
			timeplantedOrder(allProducts, size);
			break;
		case'0':
			sair = true;
			cout << "Escolheu a op��o sair! " << endl;
			break;
		default:
			cout << "Digite uma op��o v�lida!" << endl;
			break;
		}

	} while (!sair);
}*/

/*
void createnewarea(DataNeeded* internalData) {
	cin.ignore();

	string* updateArea = new string[internalData->sizeofAreasChoosen + 1]; // Array that will contain all the areas used in the program and the new one

	for (int i = 0; i < internalData->sizeofAreasChoosen; i++) // Puts all the areas being used to the internal created array
		updateArea[i] = internalData->areaArray[i];

	cout << "Digite o nome da nova �rea a criar: ";
	getline(cin, updateArea[internalData->sizeofAreasChoosen]); // Puts the new area to the areas choosen array


	delete[] internalData->areaArray; // Deletes the areas used in the program
	internalData->areaArray = new string[internalData->sizeofAreasChoosen++]; // Allocates the memory with the correct size and increases the number of areas choosen

	internalData->areaArray = updateArea; // Updates the areas used in the program with the new one added
	cout << endl << "�rea criada com sucesso!" << endl;
}

*/
void printBST(ProductHarvestedRecord* oneProduct) {

	ProductHarvestedRecord* aux = oneProduct;

	if (aux == NULL) {
		cout << endl;
		return;
	}

	printBST(aux->right);

	cout << "Nome: " << aux->name;

	printBST(aux->left);
}


void harvestRecord(LLGardens* plantationEDA) {
	// Variables
	string responsavel;
	LLGardens* itPlantation = plantationEDA;

	while (itPlantation != NULL) {
		cout << "---------------------------------" << endl;
		cout << "Respons�vel: " << itPlantation->oneGarden.owner << " | "
			<< "�rea: " << itPlantation->oneGarden.area << endl;
		cout << "---------------------------------" << endl;
		// Loops through all harvested products in a Garden
		printBST(itPlantation->oneGarden.gardenrecord);
		cout << "---------------------------------" << endl;
		itPlantation = itPlantation->next;
	}
}

/*
void changeArea(DataNeeded* internalData, Garden* plantationEDA) {
	// Variables
	char c = ' ';
	bool sair = false;
	string str;

	do {
		cout << "Digite o identificador da horta que deseja alterar a �rea (maiusculas): ";
		cin >> c;

		cin.ignore();

		for (int i = 0; i < internalData->numberofGardens; i++) // Checks if there is a Garden with that character
			if (c == plantationEDA[i].gardenorder)
				sair = true;

		if (!sair) 
			cout << "Essa horta n�o existe, por favor digite um identificador de horta existente!\n" << endl;

	} while (!sair);
	sair = false;
	
// Array of strings with no duplicates and ordered - function removeduplicates
	string* tempArea = new string[internalData->sizeofAreasChoosen];
	string* areasChoosenNoDuplicates = new string[internalData->sizeofAreasChoosen];
	string currentarea = "";
	int sizem = 0;
	tempArea = internalData->areaArray;

	// Sort areasChoosen
	for (int i = 0; i < internalData->sizeofAreasChoosen; i++)
		for (int j = i + 1; j <= internalData->sizeofAreasChoosen - 1; j++)
			if (tempArea[j] < tempArea[i])
				swap(tempArea[i], tempArea[j]);		
	 
	// Remove Duplicates
	for (int i = 0; i < internalData->sizeofAreasChoosen; i++) {
		if (currentarea != tempArea[i]) 
			areasChoosenNoDuplicates[sizem++] = tempArea[i];

		currentarea = tempArea[i];
	}

	// Loops through all Gardens
	for (int i = 0; i < internalData->numberofGardens; i++) { 
		if (plantationEDA[i].gardenorder == c) { // Verifies in which Garden the character is equal to the Garden order
		
			cout << endl << "Poss�veis �reas:  " << endl;

			for (int j = 0; j < sizem; j++)  // Displays all the areas you can choose
				if (areasChoosenNoDuplicates[j] != plantationEDA[i].area)
					cout << " -" << " " << areasChoosenNoDuplicates[j] << endl;
			

			do { //Asks for an area and checks to see if it is acceptable
			
				cout << "Digite a sua op��o: ";
				getline(cin, str);

				for (int j = 0; j < internalData->sizeofAreasChoosen; j++)
					if (str == areasChoosenNoDuplicates[j] && str != plantationEDA[i].area)
						sair = true;

				if (!sair) 
					cout << "Digite uma das op��es acima!" << endl;

			} while (!sair);


			internalData->areaArray[i] = str;
			plantationEDA[i].area = str;

			delete[] plantationEDA[i].ingarden; // Deletes the array of products in the Garden
			//plantationEDA[i].ingarden = new Product[plantationEDA[i].capacity]; // Allocates memory with the capacity of Garden
			plantationEDA[i].numberproducts = 0;
		}
	}
	cout << endl << "�rea alterada com sucesso!" << endl;
}*/


void managementMenu(DataNeeded* internalData, LLGardens* plantationEDA, LLProducts* plantationStorage, Filepaths* plantationFilepaths) {
	// Variables
	bool sair = false;
	char opcoes = ' ';

	do {
		cout << " " << endl;
		cout << "*****" << " Bem Vindo Gestor " << "*****" << endl;
		cout << "(1).Colher Produto" << endl;
		cout << "(2).Atualizar tempo de rega" << endl;
		cout << "(3).Fertiliza��o" << endl;
		cout << "(4).Gravar Planta��o" << endl;
		cout << "(5).Carregar Planta��o" << endl;
		cout << "(6).Imprimir Planta��o" << endl;
		cout << "(7).Criar nova �rea" << endl;
		cout << "(8).Mostrar registo de agricultor" << endl;
		cout << "(9).Alterar �rea" << endl;
		cout << "(0).Voltar" << endl;
		cout << "Selecione a sua opc�o: ";
		cin >> opcoes;

		cout << " " << endl;
		switch (opcoes) {
		case '1':
			//harvestProduct(internalData, plantationEDA);
			break;
		case '2':
			//updatewatering(internalData, plantationEDA, plantationStorage);
			break;
		case '3':
			//fertilization(internalData, plantationEDA);
			break;
		case '4':
			//recordPlantation(internalData, plantationEDA, plantationStorage, plantationFilepaths);
			break;
		case '5':
			//loadPlantation(internalData, plantationEDA, plantationStorage, plantationFilepaths);
			break;
		case '6':
			//printProducts(internalData, plantationEDA, plantationStorage);
			break;
		case '7':
			//createnewarea(internalData);
			break;
		case '8':
			harvestRecord(plantationEDA);
			break;
		case '9':
			//changeArea(internalData, plantationEDA);
			break;
		case '0':
			cout << "Selecionou a opcao sair!" << endl;
			sair = true;
			break;
		default:
			cout << "Selecione uma op��o v�lida!" << endl;
		}
	} while (!sair);
	cin.ignore();
}
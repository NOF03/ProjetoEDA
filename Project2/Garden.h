#pragma once
#include "Structs.h"

Garden createGarden(DataNeeded* internalData, char id);

void inicializeGardens(DataNeeded* internalData, LLGardens** plantationEDA);

Product inicializeProducts(DataNeeded* internalData); // Initialize the Products 

void display(DataNeeded* internalData, LLGardens* plantationEDA, LLProducts* plantationStorage); // Displays the current products in the plantation and storage

void assignProductsToGardens(LLGardens** plantationEDA, LLProducts** plantationStorage, DataNeeded* internalData);

void createNewProducts(LLProducts** plantationStorage, DataNeeded* internalData); // Creates the products in the Storage cycle by cycle

void insertProductinGarden(LLGardens** plantationEDA, Product addProduct, int position);

void removeProductfromStorage(LLProducts** oneList, int position);

void verifyProductHarvested(LLGardens** plantationEDA);

void plague(LLGardens** plantationEDA);

void timePlanted(LLGardens** plantationEDA);

void plantationMenu(DataNeeded* internalData, LLGardens* plantationEDA, LLProducts* plantationStorage, Filepaths* plantationFilepaths); // Menu of the Plantation
#pragma once
#include "Structs.h"

void inicializeGardens(DataNeeded *internalData, Garden *plantationEDA); // Initialize all Gardens

Product *inicializeProducts(DataNeeded *internalData); // Initialize the Products

void display(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage); // Displays the current products in the plantation and storage

void addProductsToRecord(Product productsold, Garden *plantationEDA, int x); // Removes a product from a Garden and adds it to its Record

void verifyProductHarvested(Garden *plantationEDA, DataNeeded *internalData); // Verifies if a product is harvested or not (has a 25% chance)

void createNewProducts(Storage *plantationStorage, DataNeeded *internalData); // Creates the products in the Storage cycle by cycle

void assignProductsToGardens(Garden *plantationEDA, Storage *plantationStorage, DataNeeded *internalData); // Removes some products from the Storage and plant them on the Gardens

void plague(DataNeeded *internalData, Garden *plantationEDA); // Removes by chance products from Gardens

void verifyFertilization(DataNeeded *internalData, Garden *plantationEDA); // Verifies if an area is being Fertilized

void plantationMenu(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage, Filepaths *plantationFilepaths); // Menu of the Plantation
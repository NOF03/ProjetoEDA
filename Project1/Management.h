#pragma once
#include "Structs.h"

void harvestProduct(DataNeeded *internalData, Garden *plantationEDA); // Harvest a product manually

void updatewatering(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage); // Update the watering of a product

void fertilization(DataNeeded *internalData, Garden *plantationEDA); // Fertilize an area, given by the user

void recordPlantation(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage, Filepaths *plantationfilepaths); // Saves the plantation to a file

void loadPlantation(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage, Filepaths *plantationfilepaths); // Loads the plantation from a file

void printProducts(DataNeeded *internalData, Garden *plantantionEDA, Storage *supermarketStorage); // Prints all products of the plantation and storage ordered

void createnewarea(DataNeeded *internalData); // The user creates a new area

void harvestRecord(DataNeeded *internalData, Garden *plantationEDA); // Prints a list of the harvested products

void changeArea(DataNeeded *internalData, Garden *plantationEDA); // Change an area, choosen by the user, of a Garden

void managementMenu(DataNeeded *internalData, Garden *plantationEDA, Storage *plantationStorage, Filepaths *plantationFilepaths); // Menu of the Manager
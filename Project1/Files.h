#pragma once
#include "Structs.h"
using namespace std;

int calculateSizeofFile(string path); // Calculate the size of a file to initialize the array

string *getContentFromFiles(string path, int sizeofFile); // Adds to an array the content in the file

void saveDataNeededFiles(DataNeeded *internalData, Filepaths *plantationFilepaths); // Save the essential data to a file

void saveGardensFiles(DataNeeded *internalData, Garden *plantationEDA, Filepaths *plantationFilepaths); // Save the Gardens to a file

void saveStorageFiles(DataNeeded *internalData, Storage *plantationStorage, Filepaths *plantationFilepaths); // Save the Storage to a file

void loadDataNeeded(DataNeeded *internalData, Filepaths *plantationFilepaths); // Loads a saved DataNeeded from a Plantation

void loadGardens(DataNeeded *internalData, Garden *plantationEDA, Filepaths *plantationFilepaths); // Loads saved Gardens from a Plantation

void loadStorage(DataNeeded *internalData, Storage *plantationStorage, Filepaths *plantationFilepaths); // Loads a saved Storage from a Plantation

bool verifyFiles(Filepaths *plantationFilepaths); // Verifies if the files paths can be opened
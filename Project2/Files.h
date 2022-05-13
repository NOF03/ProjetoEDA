#pragma once
#include "Structs.h"
using namespace std;

int calculateSizeofFile(string path); // Calculate the size of a file to initialize the array

string* getContentFromFiles(string path, int sizeofFile); // Adds to an array the content in the file

bool verifyFiles(Filepaths* plantationFilepaths); // Verifies if the files paths can be opened
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include "record.h"

//location_noise, alters where the key-values are located
//filesize, size of the file
//function, function used to generate the 

//generates records from a function
//also applies noise
float datafunc(int input) {
    //function used to generate data (float)
    float dFloat = (float)(input*10);
    return dFloat;
}

//applied a function to an input, based on the index
record recordfunc(int index) {
    record input;
    input.deleted = false;
    input.index = index;
    input.data = datafunc(index);
    input.ptr = NULL;
    return input;
}

//input levels fileSize and function
void generateRecordFiles(int levels, int fileSize) { //function
    //tracks total number of records
    int totalSize = 0;
    //tracks current file size
    double dFileSize = (double)fileSize;
    int currentFileSize;
    for (int l = 0; l < levels; l++) {
        // Create a level based on fileSize, levels and function
        currentFileSize = (int)(pow(dFileSize, l + 1));
        std::ofstream myFile("data/Level" + std::to_string(l) + ".txt");
        // Add records to file;    
        record iRecord;
        for (int i = totalSize; i < (totalSize + currentFileSize); i++) {
            iRecord = recordfunc(i);
            string inpVal = iRecord.rec_split();
            myFile << inpVal << "\n";
        }
        cout << to_string(sizeof(iRecord)/1048576.0) << "\n";
        totalSize = currentFileSize;

        // Close the file
        myFile.close();
    }
}

/*
//int main(int argc, char** argv) {
int main(int input, char** argv) {
    
    //needs to be converted to an input
    generateRecordFiles(4, 25);

    return 0;
}
*/
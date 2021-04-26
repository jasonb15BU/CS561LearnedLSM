#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

//location_noise, alters where the key-values are located
//filesize, size of the file
//function, function used to generate the 

//generates records from a function
//also applies noise
int datafunc(int input) {
    //function used to generate data
    input = input*10;
    return input;
}

//input levels fileSize and function
void generateFiles(int levels, int fileSize) { //function
    //tracks total number of records
    int totalSize = 0;
    //tracks current file size
    double dFileSize = 0.0;
    int currentFileSize;
    for (int l = 0; l < levels; l++) {
        // Create a level based on fileSize, levels and function
        dFileSize = (double)fileSize;
        currentFileSize = (int)(pow(dFileSize, l+1));
        std::ofstream myFile("data/funcNameSize" + std::to_string(currentFileSize) + "Level" + std::to_string(l) + ".txt");
        // Add values to file; 
        for (int i = totalSize; i < currentFileSize; i++) {
            int inpVal = datafunc(i);
            myFile << inpVal << "\n";
        }
        totalSize = totalSize + (int(pow(fileSize, l + 1)));

        // Close the file
        myFile.close();
    }
}

//int main(int argc, char** argv) {
int main(int input, char** argv) {
    
    generateFiles(4, 25);

    return 0;
}
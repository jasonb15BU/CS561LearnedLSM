#include <iostream> 
#include <fstream> 
#include <string> 
#include <algorithm> 
#include <vector>
#include <iterator>
#include <ctime>

using namespace std;

//record datatype
//bool deleted
//vector<float> data
//method get_value: get value at this location
//method delete: bool deleted = true;

std::vector<float> getFileContent(std::string fileName, std::vector<float>& fileVec)
{
    // Open the File
    //cout << "test";
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            fileVec.push_back(std::stof(str));
    }
    //Close The File
    in.close();
    return fileVec;
}

bool comparator(float i, float j) { return (i < j); }

int binary_search_list(std::vector<float> searchVec, std::vector<float> file) {
    int findnum = 0;
    vector<float>::iterator searchIndex;
    for (searchIndex = searchVec.begin(); searchIndex < searchVec.end(); searchIndex++) {
        //std::sort(file.begin(), file.end(), comparator);
        if (std::binary_search(file.begin(), file.end(), *searchIndex, comparator)) {
            //std::cout << "found!\n"; 
            findnum = findnum + 1;
            continue;
        } else {
            //std::cout << "not found.\n";
            continue;
        }
    }
    cout << "learned found numbers:" << findnum << "\n";
    return findnum;
}

//uses slope intercept method for finding functions, returns the slope and intercept
//rough estimation of our CDF, compare current value to previous value
vector<float> build_learned_function_linear(vector<float> training) {
    
    float intercept = 0.0;
    float slope = 0.0;
    vector<float>::iterator tIndex;
    tIndex = training.begin();
    intercept = *tIndex;
    //contains learned
    vector<float> learnedFunction;
    //holds the index  for calculation of slope
    int intIndex;
    //previous value for getting a rough estimate of the slope
    float pFloat = 0.0;
    for (tIndex = training.begin(); tIndex < training.end(); tIndex++) {
        //float tFloat = static_cast<float>(tIndex);
        intIndex = std::distance(training.begin(), tIndex);
        float tFloat = (float)(*tIndex);
        //float sFloat = (float)(slope);
        float iFloat = (float)(intIndex);
        //cout << tFloat << " " << iFloat << " " <<(float)(slope)+ tFloat << "\n";
        slope = ((tFloat - pFloat) + slope) / ((float)(intIndex)+1.0);
        pFloat = (float)(*tIndex);
    }
    return { slope, intercept };
}


//checks predicted location of the float
int learnedIndexSearch(vector<float> searchVec, vector<float> learned_function, vector<float> file) {
    int findnum = 0;
    vector<float>::iterator searchIndex;
    float fFile = file.at(0);
    for (searchIndex = searchVec.begin(); searchIndex < searchVec.end(); searchIndex++) {
        //uses learned function for predicted index
        int predIndex = int(fFile + (*searchIndex/(learned_function.at(1))));
        
        if (*searchIndex == file.at(predIndex)) {
            //std::cout << "found!\n";
            findnum = findnum + 1;
            continue;
        }
        else {
            //std::cout << "not found.\n";
            continue;
        }
    }

    cout << "learned found numbers:" << findnum << "\n";
    return findnum;
}

int main() {
    std::cout << "binary search\n";
    float searchTime = 0.0;
    clock_t binary_search_start, binary_search_end;

    //vector that contains our file
    std::vector<float> v;

    //selection of values we search for
    std::vector<float> searchVector;
    searchVector.reserve(10000000);
    float n(0);
    std::generate_n(std::back_inserter(searchVector), 10000000, [n]()mutable { return n++; });

    binary_search_start = clock();
    v = (getFileContent("10int9000000.txt", v));
    std::cout << "list search\n";
    binary_search_list(searchVector, v);
    binary_search_end = clock();
    searchTime = ((float)binary_search_end - (float)binary_search_start);
    std::cout << "Binary Search Time: " << searchTime << "ms (Milliseconds)\n" << endl;

    searchTime = 0.0;
    clock_t learn_search_start, learn_search_end;
    //training data we use for our learned indexes
    std::vector<float> trainingData{ 10, 20, 30, 40, 50 };
    std::cout << "learned search\n" << endl;
    learn_search_start = clock();
    v = (getFileContent("10int9000000.txt", v));
    vector<float> lFunc = build_learned_function_linear(trainingData);
    //for (std::vector<float>::const_iterator i = lFunc.begin(); i != lFunc.end(); ++i)
    //    std::cout << *i << ' ';
    //std::cout << "learned search 2\n" << endl;
    learnedIndexSearch(searchVector, lFunc, v);
    learn_search_end = clock();
    searchTime = ((float)learn_search_end - (float)learn_search_start);
    std::cout << "Learned Search Time: " << searchTime << "ms (Milliseconds)\n" << endl;

	return 0;
}

// using default comparison:
    //std::sort(v.begin(), v.end());
    /*
    cout << "looking for a 3000... ";
    if (std::binary_search(v.begin(), v.end(), 1000))
        std::cout << "found!\n"; else std::cout << "not found.\n";

    std::sort(v.begin(), v.end(), comparator);

    std::cout << "looking for a 6000... ";
    if (std::binary_search(v.begin(), v.end(), 6000, comparator))
        std::cout << "found!\n"; else std::cout << "not found.\n";
    */
    // using myfunction as comp:
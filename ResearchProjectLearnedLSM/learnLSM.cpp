#include <iostream> 
#include <fstream> 
#include <string> 
#include <algorithm> 
#include <vector>
#include <iterator>
#include <ctime>
#include "LSMRecords.h"


using namespace std;
/*
//record datatype
bool deleted; //determines whether or not this record is deleted.
int index;
vector<float> data; //data stored within.
record* ptr; //points to the next node, address
*/


//obtains records from the file and store in a vector<record>
/*
vector<record> getRecords(std::string fileName, vector<record> fileVec)
{
    //open file
    float searchTime = 0.0;
    clock_t data_start, data_end, close_end;
    data_start = clock();
    std::ifstream in(fileName.c_str());
    std::string str;
    //read lines
    record newRecord;
    int count = 0;
    data_end = clock();
    searchTime = ((float)data_end - (float)data_start);
    std::cout << "Data Time: " << searchTime << "ms (Milliseconds)\n" << endl;
    while (std::getline(in, str))
    {
        //create and new record and store if not zero
        //need to get fileVec pointers when generating records
        //cout << str << "\n";
        if (str.size() > 0) {  
            newRecord.rec_generate(str);
            fileVec.push_back(newRecord);
            count = count + 1;
        }
    }
    cout << to_string(count) << "\n";
    //Close The File
    in.close();
    close_end = clock();
    searchTime = ((float)close_end - (float)data_start);
    std::cout << "Close Time: " << searchTime << "ms (Milliseconds)\n" << endl;
    return fileVec;
}
*/

//gets all records and places them into an lsm 
void getAllRecords(LSMRecords& lsm) {
    //for each level, add a vector<record>
    //lsm.levels.resize(lsm.numlev);
    list<list<record>>::iterator nRIT = lsm.levels.begin();
    for (int i = 0; i < lsm.numlev; i++) {
        lsm.levels.emplace_back();
        string fileName;
        //cout << "b" << "\n";
        fileName = "data/Level" + to_string(i) + ".txt";
        float searchTime = 0.0;
        clock_t data_start, data_end, loop_start, loop_end;
        std::ifstream in(fileName);
        vector<record> newRec; //((int(pow((double)lsm.fileSize, i + 1))));
        //newRec.reserve(int(pow((double)lsm.fileSize, i + 1)));
        //cout << "capacity" << to_string(newRec.capacity()) << "\n";
        //cout << newRec.size() << "\n";
        std::string str;
        record newRecord;
        int count = 0;
        //cout << "b" << "\n";
        float splitTime = 0.0;
        clock_t split_start, split_end;
        data_start = clock();
        while (std::getline(in, str))
        {
            split_start = clock();
            //if (str.size() > 0) {
            //cout << to_string(newRec.capacity()) << "\n";
            newRecord.rec_generate(str);
            //newRec.at(count) = (newRecord);
            //*nRIT = newRecord;
            //(*nRIT).push_back(newRecord);
            lsm.levels.back().push_back(newRecord);
            //insert the hash
            lsm.insert_hash(newRecord.index, addressof((lsm.levels.back()).back()));
            //newRec.insert(nRIT, (newRecord));
            //advance(nRIT, 1);
            split_end = clock();
            //newRec.insert(newRec.end(),newRecord);
            //newRec.insert(nRIT,(newRecord));
            count = count + 1;
            //cout << count;
            splitTime = splitTime + ((float)split_end - (float)split_start);
            //}
        }
        //advance(nRIT, 1);
        //std::cout << "Split Time: " << splitTime << "ms (Milliseconds)\n";
        data_end = clock();
        searchTime = ((float)data_end - (float)data_start);
        cout << "Data Time: " << to_string(searchTime) << "ms (Milliseconds)" << "\n" << endl;
        //cout << "count levels.back" << lsm.levels.back().size() << "\n";
        //cout << "count levels" << lsm.levels.size() << "\n";
        in.close();
        loop_end = clock();
        searchTime = ((float)loop_end - (float)data_start);
        //std::cout << "Loop Time: " << searchTime << "ms (Milliseconds)" << "\n" << endl;
        //cout << to_string(i) << "\n" << endl;
    }
    //cout << to_string((lsm).levels.size()) << "size before end\n" << endl;
}

/*
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
}*/


//int learnedIndexLSM(vector<float> searchVec, vector<float> l_func, LSMRecords lsm) //finds values in the LSM tree

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

vector<float> genSearchVec(float size) {
    vector<float>::iterator searchIndex;
    float vecSize = size;
    std::vector<float> sVec;
    sVec.reserve(vecSize);
    float n(0);
    std::generate_n(std::back_inserter(sVec), vecSize, [n]()mutable { return n++; });
    return sVec;
}

int main() {
    //cout << "check" << "\n";
    LSMRecords lsmv;
    int fileSize;
    int levels;
    //cout << to_string(sizeof(lsmv)) << "\n";
    //cout << to_string(sizeof(lsmv) / 1048576.0) << "\n"; 
    cout << "fileSize: " << endl;
    cin >> fileSize;
    cout << "levels: " << endl;
    cin >> levels;
    lsmv.numlev = levels;
    lsmv.fileSize = fileSize;
    float searchTime = 0.0;
    clock_t data_start, data_end;
    data_start = clock();
    generateRecordFiles(lsmv.numlev, lsmv.fileSize);
    data_end = clock();
    searchTime = ((float)data_end - (float)data_start);
    std::cout << "Generation Time: " << searchTime << "ms (Milliseconds)\n" << endl;
    cout << "check" << "\n";
    getAllRecords(lsmv);

    //testing hashmap
    float accTime = 0.0;
    clock_t acc_start, acc_end;
    acc_start = clock();

    /*
    vector<float>::iterator searchIndex;
    float vecSize = 100.0;
    std::vector<float> searchVec;
    searchVec.reserve(vecSize);
    float n(0);
    std::generate_n(std::back_inserter(searchVec), vecSize, [n]()mutable { return n++; });
    float sum = 0;
    for (searchIndex = searchVec.begin(); searchIndex < searchVec.end(); searchIndex++) {
        sum = lsmv.find_index(*searchIndex).index;
    }
    cout << sum << "\n";
    cout << lsmv.find_addr(1) << "\n";
    cout << lsmv.find_index(1).data << "\n";
    cout << lsmv.find_index(1).index << "\n";
    cout << lsmv.find_index(1).ptr << "\n";
    cout << lsmv.find_addr(11) << "\n";
    cout << lsmv.find_index(11).data << "\n";
    cout << lsmv.find_index(11).index << "\n";
    cout << lsmv.find_index(11).ptr << "\n";
    cout << lsmv.find_addr(300) << "\n";
    cout << lsmv.find_index(300).data << "\n";
    cout << lsmv.find_index(300).index << "\n";
    cout << lsmv.find_index(300).ptr << "\n";
    cout << lsmv.find_addr(15) << "\n";
    cout << lsmv.find_addr(15) << "\n";
    cout << lsmv.find_addr(15) << "\n";
    cout << lsmv.find_index(15).data << "\n";
    cout << lsmv.find_index(15).index << "\n";
    cout << lsmv.find_index(15).ptr << "\n";
    acc_end = clock();
    accTime = ((float)acc_end - (float)acc_start);
    std::cout << "Access Time: " << accTime << "ms (Milliseconds)\n" << endl;
    */

    string userInput;
    float userInt;
    

    while (userInput != "exit")
    {

        cout << "select a test: " << endl;
        cin >> userInput;

        vector<float> sVec;


        if (userInput == "linear") // run a linear test for 1000000 consective numbers
        {
            cout << "select size: " << endl;
            cin >> userInt;
            sVec = genSearchVec(userInt);
            float accTime = 0.0;
            clock_t acc_start, acc_end;
            acc_start = clock();
            lsmv.learnedIndexSearch(sVec, lsmv.build_learned_function_linear({ 10,20,30,40,50 }));
            acc_end = clock();
            accTime = ((float)acc_end - (float)acc_start);
            std::cout << "Linear Search Time for " << userInt << " variables: "<< accTime << "ms (Milliseconds)\n" << endl;
        }
        else if (userInput == "binary")  // run a binary test
        {
            cout << "select size: " << endl;
            cin >> userInt;
            sVec = genSearchVec(userInt);
            float accTime = 0.0;
            clock_t acc_start, acc_end;
            acc_start = clock();
            lsmv.binaryMultiSearch(sVec);
            acc_end = clock();
            accTime = ((float)acc_end - (float)acc_start);
            std::cout << "Linear Search Time for " << userInt << " variables: " << accTime << "ms (Milliseconds)\n" << endl;
        }
        else if (userInput != "exit")  // incorrect test number
        {
            cout << "invalid, please select another test" << endl;
        }
    }
    return 0;
}

/*
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
*/

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
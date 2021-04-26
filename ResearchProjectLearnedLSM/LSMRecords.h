#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>
#include <unordered_map>
#include "file_generator_records.cpp"
#include <list>

using namespace std;

class LSMRecords {
public:
	int numlev; //tracks number of levels
	int fileSize; //tracks initial file size
	list<list<record>> levels; //contains all vector<records>/levels
	unordered_map<int, record*> hashmap; //stores index and record

	vector<float> build_learned_function_linear(vector<float> training) {
		float intercept = 0.0;
		float slope = 0.0;
		vector<float>::iterator tIndex;
		tIndex = training.begin();
		intercept = *tIndex;
		vector<float> learnedFunction;
		int intIndex;
		float pFloat = 0.0;
		for (tIndex = training.begin(); tIndex < training.end(); tIndex++) {
			intIndex = std::distance(training.begin(), tIndex);
			float tFloat = (float)(*tIndex);
			float iFloat = (float)(intIndex);
			slope = ((tFloat - pFloat) + slope) / ((float)(intIndex)+1.0);
			pFloat = (float)(*tIndex);
		}
		return { slope, intercept };
	}

	void learnedIndexSearch(vector<float> searchVec, vector<float> learned_function) {
		int findnum = 0;
		vector<float>::iterator searchIndex;
		//get first value for prediction/intercept
		float fFile = find_index(0).data;
		for (searchIndex = searchVec.begin(); searchIndex < searchVec.end(); searchIndex++) {
			//uses learned function for predicted index
			int predIndex = int(fFile + (*searchIndex / (learned_function.at(1))));
			float searchLoc = find_index(predIndex).data;
			if (searchLoc == *searchIndex) {
				//cout << searchLoc << "\n";
				findnum = findnum + 1;
				continue;
			}
			else {
				continue;
			}
		}
		cout << "learned found numbers:" << findnum << "\n";
		//return findnum;
	}

	void binaryMultiSearch(vector<float> searchVec) {
		int findnum = 0;
		vector<float>::iterator searchIndex;
		float fFile = find_index(0).data;
		for (searchIndex = searchVec.begin(); searchIndex < searchVec.end(); searchIndex++) {
			//uses learned function for predicted index
			//int predIndex = int(fFile + (*searchIndex / (learned_function.at(1))));
			bool searchLoc = binarySearch(0, hashmap.size(), *searchIndex);
			if ((searchLoc)) {
				findnum = findnum + 1;
				continue;
			}
			else {
				continue;
			}
		}
		cout << "learned found numbers:" << findnum << "\n";
		//return findnum;
	}


	bool binarySearch(int l, int r, int x)
	{
		if (r >= l) {
			int mid = l + (r - l) / 2;
			// If the element is present at the middle
			// itself
			if (find_index(mid).data == x)
				return true;

			// If element is smaller than mid, then
			// it can only be present in left subarray
			if (find_index(mid).data > x)
				return binarySearch(l, mid - 1, x);

			// Else the element can only be present
			// in right subarray
			return binarySearch(mid + 1, r, x);
		}

		// We reach here when element is not
		// present in array
		return false;
	}


	/*
	//binary searches entire hashmap for data
	int binary_search_list(int vecSize) {
		int findnum = 0;
		vector<float>::iterator searchIndex;
		std::vector<float> searchVec;
		searchVec.reserve(vecSize);
		float n(0);
		std::generate_n(std::back_inserter(searchVec), vecSize, [n]()mutable { return n++; });
		for (searchIndex = searchVec.begin(); searchIndex < searchVec.end(); searchIndex++) {
			if (std::binary_search(file.begin(), file.end(), *searchIndex)) {
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
	*/

	void insert_level(list<record>& vRec) { //inserts level
		float searchTime = 0.0;
		clock_t data_start, data_end;
		data_start = clock();
		levels.push_back(vRec);
		data_end = clock();
		searchTime = ((float)data_end - (float)data_start);
		std::cout << "Insert Time: " << searchTime << "ms (Milliseconds)\n" << endl;
	}

	/*
	int return_size(int levIndex) {
		return levels.at(levIndex).size();
	}
	*/

	list<record> last_level() { //inserts level
		return levels.back();
	}

	//insert index and pointer into the hashmap
	//utilized for updates and deletes
	//still need to update the pointers and previous records
	//never referenced itself, must be used with update or delete
	//functions
	void insert_hash(int index, record* recPointer) {
		//cout << recPointer << " to " << index << "\n";
		hashmap.insert({ index, recPointer });
		//cout << "insert_hash data: " << &find_index(0).data << "\n";
		//cout << "insert_hash data: " << find_index(index).data << "\n";
	}

	//goes to index in the hashmap, and return from the addr
	record* find_addr(int index) {
		auto it = hashmap.find(index);
		if (it == hashmap.end()) {
			cout << "notfound" << "\n";
			return NULL;
		}
		else {
			//return the record at the (index, pointer -> record)
			//return addr_to_record(index);
			return it->second;
		}
	}

	//never used by itself, returns the record at this location
	//used to prevent having to type *hashmap.at(index); as its prone to typos and misreading
	record find_index(int index) {
		return *find_addr(index);
	}
};


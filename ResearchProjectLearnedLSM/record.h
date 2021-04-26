#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>

//record datatype
//bool deleted
//vector<float> data
//method get_value: get value at this location
//method delete: bool deleted = true;

using namespace std;

class record {
	public:
		bool deleted; //determines whether or not this record is deleted.
		int index;
		record* ptr; //points to the next node, address
		float data; //data stored within.

		record() { //creates default record, not inputted yet, no data
			deleted = false;
			index = -1;
			ptr = NULL;
			data = 0.0;
		}

		record(bool d, int i, record* p, float dta) { //creates record w params
			deleted = d;
			index = i;
			ptr = p;
			data = 0.0;
		}
		/*
		void rec_del(); //delete the value (set bool deleted to zero)
		string rec_split(); //split into string for file
		void rec_generate(); //fill in from string file
		float rec_value(int); //get the value at a selected position
		vector<float> rec_values(); //get the values
		bool rec_is_del(); //get the delete
		string str_addr(); //get the string of the address
		record rec_updated(); //returns updated record
		void str_to_del(string); //convert string to delete
		void str_to_dta(string); //convert string to data(float)
		void str_to_ind(string); //convert string to index
		void str_to_ptr(string); //convert string to pointer
		*/
		void rec_del() {
			deleted = true;
		}

		//if is_null, can assume it doesn't exist or empty
		bool is_null() {
			if (index == -1) {
				return true;
			}
			else {
				return false;
			}
		}

		string str_is_del() {
			if (deleted) {
				return "true";
			}
			else {
				return "false";
			}
		}

		string str_addr() {
			const void* ptrAddr = static_cast<const void*>(ptr);
			stringstream ptrSS;
			ptrSS << ptrAddr;
			string ptrStr = ptrSS.str();
			//if nonexistent, return null
			if (ptrStr == "0") {
				return "NULL";
			}
			else {
				return ptrStr;
			}
		}

		string str_ind() {
			return to_string(index);
		}

		void str_to_del(string delStr) {
			if (delStr == "true") {
				deleted = true;
			}
			else {
				deleted = false;
			}
		}

		void str_to_ind(string indStr) {
			index = stoi(indStr);
		}

		void str_to_dta(string indStr) {
			data = stof(indStr);
		}

		string rec_split() {
			int intIndex;
			string fString = "" + record::str_is_del() + "," + record::str_ind() + "," + record::str_addr() + "," + to_string(data) ;
			return fString;
		}

		void rec_generate(string fRecord){
			istringstream ssr(fRecord);
			//contains the strings from the txt file
			vector<string> fString;
			while (ssr)
			{
				string s;
				//std::cout << s;
				if (!getline(ssr, s, ',')) break;
				fString.push_back(s);
			}
			//index for navigating our vector<string>
			vector<string>::iterator sIndex = fString.begin();
			//get deleted status
			str_to_del(*sIndex);
			advance(sIndex,1);
			//get record index
			str_to_ind(*sIndex);
			advance(sIndex, 1);
			//get pointer
			ptr = NULL;
			advance(sIndex, 1);
			//get the float
			str_to_dta(*sIndex);
			/*
			int intIndex;
			for (sIndex = sIndex; sIndex < fString.end(); sIndex++) {
				//float tFloat = static_cast<float>(tIndex);
				intIndex = std::distance(fString.begin(), sIndex);
				float iFloat = (float)(intIndex);
				append_data(iFloat);
			*/
			
		}

		float rec_value() {
			return data;
		}

		bool rec_is_del() {
			return deleted;
		}

		record rec_updated() {
			return *ptr;
		}
};

/*
record::record(NULL) {
}
*/

/*
record::record(bool d, int i, record* p, vector<float> dta) {
}
*/
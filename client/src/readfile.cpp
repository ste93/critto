#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;



int main () {
	string line;
	string temp;
	ifstream filedb;
	filedb.open("dataset_128.txt");
	if (!filedb.is_open())
		return -1;
    while ( getline(filedb,line) )
    {
    	cout << line << '\n';
		istringstream iss(line);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		cout << tokens[0]
		for(string n : tokens){
			cout << "inserting" << n << endl;
			
		}		
	}
	filedb.close();
	return 0;
}

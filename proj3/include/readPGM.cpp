#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<double> readOne(ifstream& inFile){ // take in file, read lines into vector, return
	vector<double> output;
	string line;

	getline(inFile, line);
	getline(inFile, line);
	getline(inFile, line);
	getline(inFile, line);

	return output;
}

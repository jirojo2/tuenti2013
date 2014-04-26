/*
 * Tuenti Challenge #4
 * José Ignacio Rojo Rivero -josi-
 */

#include "util.h"
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include <limits>

using namespace std;

#define MAX_MEMORY 4*1024*1024*1024

vector<int> req;
vector<int> missing;

int main (int argc, char** argv)
{
	string line;
	
	// #n of cases
	getline(cin, line);
	int k = stoi(line);
	for (int i = 0; i < k; i++)
	{
		// Number to be found
		getline(cin, line);
		req.push_back(stoi(line));
	}
	
	int N = numeric_limits<int>::max();
	int L = (int)((long)MAX_MEMORY/sizeof(int));
	int* A = new int[L]; // make sure its initialized to zero
	int T = ceil((double)N/L);
	
	for (long c = 0; c < T; c++)
	{
	
	//cout << "[" << c+1 << "/" << T << "]" << endl; 

	for (int i = 0; i < L ; i++)
		A[i] = 0;

	ifstream file("integers");

	while( file.good() )
	{
		// Reuse k to read one integer
		file.read((char*)&k, sizeof(int));
		if (k >= c*L && k < c*L+L)
			A[k-c*L] = k;
	}

	//int mstart = missing.size();
	// Report missing ones!
	for (int j = 0; j < L; j++)
		if (A[j] == 0)
			missing.push_back(j+c*L);

	file.close();
	
	// Write the new finds!
	//for (size_t j = mstart; j < missing.size(); j++)
	//	cout << missing[j] << endl;
	}	

	delete[] A;

	// Remember to ignore the first entry! (0)
	//for (size_t j = 0; j < missing.size(); j++)
	//	cout << missing[j] << endl;

	//cout << missing.size()-1 << " missing!" << endl;
	
	// Output
	for (size_t i = 0; i < req.size(); i++)
	{
		cout << missing[req[i]];
		if (i+1 < req.size())
			cout << endl;
	}
	return 0;
}

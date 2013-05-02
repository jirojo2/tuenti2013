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

#define MAX_MEMORY 1024*1024*1024

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
		k = stoi(line);
		req.push_back(k);
	}
	
	int N = numeric_limits<int>::max();
	int L = MAX_MEMORY/sizeof(int);
	int* A = new int[L]; // make sure its initialized to zero
	
	for (int c = 0; c < N/L; c++)
	{
	
	cout << "[" << c+1 << "/" << N/L << "]" << endl; 

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

	// Report missing ones!
	for (int j = c*L; j < c*L+L; j++)
		if (A[j-c*L] == 0)
			missing.push_back(j);

	file.close();
	
	}	

	delete[] A;

	// Remember to ignore the first entry! (0)
	for (size_t j = 0; j < missing.size(); j++)
		cout << missing[j] << endl;

	cout << missing.size() << " missing!" << endl;
	return 0;
}

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

vector<int> req;
set<int> all;
set<int> missing;

int main (int argc, char** argv)
{
	string line;
	
	// #n of cases
	getline(cin, line);
	int n = stoi(line);
	for (int i = 0; i < n; i++)
	{
		// Number to be found
		getline(cin, line);
		int k = stoi(line);
		req.push_back(k);
	}
	
	// Handle processing... maybe multithreaded?
	// I need to locate ALL the numbers first...
	int max_mem = 16*1024*1024;
	cout << "Allocating memory..." << endl;
	for (int i = 1; i < numeric_limits<int>::max(); i+=max_mem)
	{
		cout << "Processing block " << 1+i/max_mem << " of " << numeric_limits<int>::max()/max_mem << endl;
		all.erase(all.begin(), all.end());
		for (int k = i; k < i+max_mem; k++)
		{
			all.insert(all.end(), i);
		}
		
		ifstream file("integers");
		if (!file.is_open()) return 1;
		while (file.good())
		{
			file.read((char*)&n, sizeof(int));
			if (n >= i && n < i+max_mem)
			{
				if (all.erase(n) < 1)
					missing.insert(missing.end(), n);
			}
		}
		file.close();
	}

	cout << missing.size() << " missing!" << endl;
	return 0;
}

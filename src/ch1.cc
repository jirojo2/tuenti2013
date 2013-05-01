/*
 *  Tuenti Challenge #1
 *	José Ignacio Rojo Rivero
 */

#include "util.h"

using namespace std;

int computeTransaction(int budget, vector<int>& values)
{
	int total = budget;
	bool euros = true;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (euros)
		{
			// Buy bitcoins
			if (i+1 < values.size() && values[i] <= total && values[i+1] > values[i])
			{
				total /= values[i]; // buy
				euros = false; // we have bitcoins now
				//cout << "Buy at " << values[i] << ", total: " << total << endl;
			}
		}
		else
		{
			// Sell
			if (i+1 == values.size() || values[i] > values[i+1])
			{
				total *= values[i];
				euros = true;
				//cout << "Sell at " << values[i] << ", total: " << total << endl;
			}
		}
	}
	return total;
}


void processInput()
{
	string line;
	getline(cin, line);

	// First line => n of cases
	int n = stoi(line);
	// Validate n? negative, NaN, ...
	
	for (int i = 0; i < n; n++)
	{
		// Init budget
		getline(cin, line);
		int budget;
		try {
			budget = stoi(line);
		} catch (invalid_argument& e) {
			break;
		}

		// Future values
		getline(cin, line);
		vector<int> values;
		vector<string> params = split(line, ' ');
		for (unsigned int k = 0; k < params.size(); k++)
			try{
				values.push_back(stoi(params[k]));
			}catch(invalid_argument& e) {}

		// Process case
		int total = computeTransaction(budget, values);
		cout << total << endl;
	}
}

int main(int argc, char** argv)
{
	processInput();
	return 0;
}


/*
 * Tuenti Challenge #3
 * José Ignacio Rojo Rivero
 */

#include "util.h"
#include <algorithm>

using namespace std;

bool _debug = false;

void processPlot(string line)
{
	vector<int>   event;
	vector<string> plot;
	vector<string> final;

	// Process events
	int length = 0;
	unsigned int start = 1;
	for (size_t i = 0; i < line.length(); i++)
	{
		switch (line[i])
		{
			case '.':
			{
				event.push_back(0);
				break;
			}
			case '<':
			{
				event.push_back(-1);
				break;
			}
			case '>':
			{
				event.push_back(1);
				break;
			}
			default:
				continue;
		}
		
		// Fail-safe
		if (i+1 == line.length())
			break;

		// Add the stored plot
		length = i - start;
		if (length > 0)
			plot.push_back(line.substr(start, length));
		start = i+1;	
	}

	// Add the remaining string
	if (start < line.size())
		plot.push_back(line.substr(start));
	
	// Debug
	if (_debug)
	for (size_t i = 0; i < event.size(); i++)
	{
		cout << "[" << event[i] << "] " << plot[i] << endl;
	}
	
	// Check for repeated plot entries...
	// If any, the result will be either valid or invalid...
	// IF there is a -1 before a 0 => invalid
	// IF there is a  1 after  a 0 => invalid
	// ELSE valid

	for (size_t i = 0; i < event.size(); i++)
		for (size_t j = i+1; j < event.size(); j++)
		{
			bool invalid = false;
			if (plot[i].compare(plot[j]) == 0)
			{
				if (event[i] == 1 && event[j] == -1 && j-i == 2)
					continue;
				if (event[i] < event[j])
					invalid = true;
				if (invalid)
					cout << "invalid" << endl;
				else
					cout << "valid" << endl;
				return;
			}
		}

	// No viable end
	if (event[event.size()-2] == 1)
	{
		cout << "invalid" << endl;
		return;
	}

	// Order the plot
	final.resize(event.size());
	for (size_t i = 0; i < event.size(); i++)
	{
		int pos = i + event[i];
		if (pos < 0) pos = 0;
		if (pos > final.size()) pos--;
		final.insert(final.begin()+pos, plot[i]); 
	}

	// Remove empty places
	final.erase(
    	remove_if(
        	final.begin(),
        	final.end(),
        	[](string const& s) { return s.size() == 0; }),
    final.end());
	
	// Remove possible repeated
	vector<string>::iterator it;
	for (it = final.begin(); it != final.end(); ++it)
	{
		vector<string>::iterator it2;
		for (it2 = it+1; it2 != final.end(); ++it2)
			if (it->compare(*it2) == 0)
			{
				final.erase(it2);
				break;
			}
	}
	
	// Render output
	if (final.size() > 0)
		cout << final[0];
	for (size_t i = 1; i < final.size(); i++)
		cout << "," << final[i];
	cout << endl;
}

int main(int argc, char** argv)
{
	string line;
	
	if (argc > 1 && string("d").compare(argv[1]) == 0)
		_debug = true;

	// Read input
	getline(cin, line);
	int n = stoi(line);
	for (int i = 0; i < n; i++)
	{
		getline(cin, line);
		processPlot(line);
	}
}

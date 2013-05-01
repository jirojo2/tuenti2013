#include <iostream>
#include "util.h"

using namespace std;

long processLine(string line)
{
	long s = 0;
	vector<string> params = split(line, ' ');
	for (int i = 0; i < params.size(); i++)
	{
		try
		{
			long n = stol(params[i]);
			s += n;
		}
		catch(invalid_argument& e)
		{
		}
		catch(out_of_range& e2)
		{
		}
	}
	return s;
}

int main(int argc, char** argv)
{
	string line;
	
	while (!cin.eof())
	{
		getline(cin, line);
		if (line == "") continue;
		cout << processLine(line);
		if (!cin.eof()) cout << endl;
	}
}

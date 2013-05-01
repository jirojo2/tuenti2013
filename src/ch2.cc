/*
 * Tuenti Challenge #2
 * José Ignacio Rojo Rivero
 */

#include "util.h"
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

map< int, vector<string> > data;

int state = 0; // process line state
int wn = 0; // helper counter
int wc = 0;

// Process data, store the words in a hashmap ordered by char-count
void processDictionary(vector<string>& words)
{
	for (size_t i = 0; i < words.size(); i++)
	{
		int l = words[i].length();

		// Add the entry to data
		if (data.find(l) == data.end())
			data[l] =  vector<string>();
		
		data[l].push_back(words[i]);
	}
}

vector<string> readDictionary(string filename)
{
	ifstream file (filename);

	vector<string> words;
	string line;

	if (!file.is_open())
		return words;

	while (file.good())
	{
		getline(file, line);
		words.push_back(line);
	}

	file.close();

	return words;
}

bool isValidSuggestion(string sug, string word)
{
	// Dont accept the same word
	if (word.compare(sug) == 0)
		return false;

	// Only accept the suggestion if it has the same letters, in any order
	for (size_t i = 0; i < word.length(); i++)
	{
		if (sug.find(word[i]) == string::npos)
			return false; // char not found!
	}

	for (size_t i = 0; i < word.length(); i++)
	{
		size_t n1 = count(sug.begin(), sug.end(), word[i]);
		size_t n2 = count(word.begin(), word.end(), word[i]);
		if (n2 != n1) return false;
	}

	return true;
}

void processWord(string word)
{
	// Filter by word length
	int l = word.length();
	if (data.find(l) == data.end())
	{
		// No data
		cout << word << " ->" << endl;
		return;
	}

	cout << word << " ->";
	
	vector<string> words = data[l];
	for (size_t i = 0; i < words.size(); i++)
	{
		// They must have the same letters, in any order
		if (isValidSuggestion(words[i], word))
		{
			cout << " " << words[i];
		}
	}
	cout << endl;
}

void processLine(string& line)
{
	switch (state)
	{
		case 0: // Dictionary file 
		{
			vector<string> words = readDictionary(line);
			processDictionary(words);
			state++;
			break;
		}
		case 1: // Number of words
		{
			try {
				wn = 0;
				wc = stoi(line);
				state++;
			} catch (invalid_argument e) { exit(1); }
			break;
		}
		case 2: // Actual words
		{	
			if (wn < wc)
			{
				processWord(line);
				wn++;
			}
			
			if (wn == wc)
				state = 0;
			break;
		}
	}
}

int main (int argc, char** argv)
{
	string line;

	// Process lines
	while (!cin.eof())
	{
		getline(cin, line);
		
		if (line.length() == 0)
			continue;
		if (line[0] == '#')
			continue;

		processLine(line);
	}	
}

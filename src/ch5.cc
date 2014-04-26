/*
 * Tuenti Challenge #5
 * José Ignacio Rojo Rivero -josi-
 */

#include "util.h"
#include <algorithm>

using namespace std;

int M,N,X,Y,Z,G;
vector<int> m;
string gems;
int maxv;

int idx(int x, int y)
{
	return x+y*N;
}

bool canMoveTo(int x, int y, vector<int>* p)
{
	if (x < 0 || x >= M) return false;
	if (y < 0 || y >= N) return false;
	if (p && find(p->begin(), p->end(), idx(x,y)) != p->end())
		 return false;
	return true;
}

void fork(int x, int y, int moves, vector<int> path)
{
	if (!canMoveTo(x,y,&path)) return;

	path.push_back(idx(x,y));
	
	if (moves-- > 0)
	{
		// fork again!
		fork(x+1, y, moves, path);
		fork(x-1, y, moves, path);
		fork(x, y+1, moves, path);
		fork(x, y-1, moves, path);
	}
	else
	{
		// Register ourselves!
		int total = 0;
		for (size_t i = 0; i < path.size(); i++)
		{
			total += m[path[i]];
		}
		if (total > maxv) 
			maxv = total;
	}
}

void processGame()
{
	int moves = Z;
	vector<int> path;
	
	fork(X, Y, moves, path);
	// fork the game... recursion ftw!
}

int main (int argc, char** argv)
{
	// Read input
	string line;
	
	getline(cin, line);
	int n = stoi(line);
	for (int i = 0; i < n; i++)
	{
		// Read params
		getline(cin, line);
		vector<string> params = split(line, ',');
		M = stoi(params[0]);
		N = stoi(params[1]);
		getline(cin, line);
		params = split(line, ',');
		X = stoi(params[0]);
		Y = stoi(params[1]);
		getline(cin, line);
		Z = stoi(line);
		getline(cin, line);
		G = stoi(line);
		getline(cin, line);
		// Generate Map
		m.clear();
		m.resize(M*N);
		maxv = 0;	
		// Read gems
		vector<string> gems = split(line, '#');
		int gemx, gemy, gemv;
		for (size_t k = 0; k < gems.size(); k++)
		{
			params = split(gems[k], ',');
			gemx = stoi(params[0]);
			gemy = stoi(params[1]);
			gemv = stoi(params[2]);
			m[idx(gemx,gemy)] = gemv;
		}
		// Debug
		//for (size_t k = 0; k < m.size(); k++)
		//{
		//	cout << m[k] << " ";
		//	if (((int)k) % M == M-1) 
		//		cout << endl;
		//}
		// Process game
		processGame();
		cout << maxv;
		if (i+1 < n) cout << endl;
		//
	}

	// Recursive algorithm... cannot go back to the same cell, limited steps
}

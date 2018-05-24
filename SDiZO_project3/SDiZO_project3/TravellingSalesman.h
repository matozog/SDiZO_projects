#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class TravellingSalesman {

	int towns, **tableDistances;
	int *permutationTable, distanceBrute,*bestPath, bestDistance = 200000;

	vector<int> path;

	void initMatrix();
	bool file_read_line(ifstream &file, int tab[], int size);
	void permutation(int k, int l);
	void showPathB();
	void showPathG(vector<int> path, int cost);

public:
	TravellingSalesman();
	~TravellingSalesman();
	void showMatrix();
	void readFromFile(string file_name);
	void GreedyAlgorithm();
	void AlgorithmBruteForce();
};
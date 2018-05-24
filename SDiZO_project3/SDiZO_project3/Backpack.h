#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

struct Item {
	int weight, value,id;
	float factor;
	bool operator()(const Item &e1, const Item &e2) {
		if (e1.value > e2.value) return false;
		if (e1.value < e2.value) return true;
		return false;
	}
};

struct SortByFactor {
	bool operator()(const Item &e1, const Item &e2) {
		if (e1.factor > e2.factor) return false;
		if (e1.factor < e2.factor) return true;
		return false;
	}
};

class Backpack {

	int capacity, items;
	vector<Item> vectorItems;
	vector<int> vectorID;
	priority_queue<Item> queue;

	bool binaryBit(int, int);
	bool file_read_line(ifstream & file, int tab[], int size);
	void showBackpackBrute(int subset);
	void showBackpackGreedy(vector<int> vectorID, int weight,string type);

public:
	Backpack();
	~Backpack();
	void GreedyAlgorithmV();
	void AlgorithmBruteForce();
	void readFromFile(string);
	void GreedyAlgorithm();
	void showItems();
};
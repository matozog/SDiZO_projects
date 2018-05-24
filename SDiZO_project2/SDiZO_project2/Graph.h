#pragma once
#include <string>
#include <queue>
#include <list>
#include <array>
#include <vector>
using namespace std;

class edge
{
public:
	int weight;
	int top_start, top_end;
	bool operator()(const edge &e1, const edge &e2) {
		if (e1.weight > e2.weight) return true;
		if (e1.weight < e2.weight) return false;
		return false;
	}
};

class Graph {

	bool file_read_line(ifstream &file, int tab[], int size);
	void init_matrixEdge();
	void init_listEdge();
protected:
	int _amountOfTops , _amountOfEdges , _top_start, _top_end;
	edge** _matrixOfEdges;
	list<edge> *_tableList;
	list<edge> *_tableList_undir;
	edge** _matrixOfEdges_undir;
public:
	Graph();
	void display_matrix_neigh(edge **matrixOfEdges);
	void display_list_neigh(list<edge> *tableList);
	void read_file(string file_name);
	int amountOfTops() { return _amountOfTops; }
	int amountOfEdges() { return _amountOfEdges; }
	int top_start() { return _top_start; }
	edge** matrixOfEdges() { return _matrixOfEdges; }
	edge** matrixOfEdges_undir() { return _matrixOfEdges_undir; }
	list<edge>* tableList() { return _tableList; }
	list<edge>* tableList_undir() { return _tableList_undir; }
	//~Graph();
};
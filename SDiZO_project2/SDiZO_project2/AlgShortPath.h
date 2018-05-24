#pragma once
#include "Graph.h"
#include <list>

class AlgShortPath:Graph{

	int *tableCosts_Dij;
	int *tablePrev_Dij; 
	int *tableCosts_BF;
	int *tablePrev_BF;

public:
	AlgShortPath(Graph graph);
	void DijkstraAlgorithmList();
	void DijkstraAlgorithmMatrix();
	void BellmanFordAlgorithmList();
	void BellmanFordAlgorithmMatrix();
	void AddCostsAndPrev(int *table_Costs, int *table_Prev);
	void display_shortest_road(int tableCosts[], int tablePrev[]);
	~AlgShortPath();
};
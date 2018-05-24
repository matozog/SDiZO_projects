#pragma once
#include "Graph.h"
#include "MSTree.h"

class MSTAlg:Graph{
	edge element;
	list<edge>::iterator it;
public:
	MSTAlg(Graph graph);
	void KruskalAlgorithmList();
	void join_subtrees(int *color_table, edge element);
	void KruskalAlgorithmMatrix();
	void PrimAlgorithmList();
	void PrimAlgorithmMatrix();

};
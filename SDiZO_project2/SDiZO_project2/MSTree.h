#pragma once
#include "Graph.h"

class MSTree {

	int _weight = 0, _amountOfTops;
	list<edge> *tableList;
	
public:
	MSTree(int tops);
	void add_edge(int i,edge element);
	void diplay_tree();
};
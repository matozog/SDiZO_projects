#include "MSTree.h"
#include <iostream>
#include <iomanip>

using namespace std;

MSTree::MSTree(int tops)
{
	tableList = new list<edge>[tops];
	_amountOfTops = tops;
	for (int i = 0; i < tops; i++)
	{
		list<edge> *listNeigh = new list<edge>;
		tableList[i] = *listNeigh;
	}
}
void MSTree::add_edge(int i,edge element)
{
	tableList[i].push_back(element);
	_weight += element.weight;
}

void MSTree::diplay_tree()
{
	list<edge>::iterator j;
	cout << setw(7) << left << "Edge" << setw(7) << left << "Weight" << endl;
	for (int i = 0; i < _amountOfTops; i++)
	{
		for (j = (tableList[i]).begin(); j != (tableList[i]).end(); j++)
		{
			cout << "(" << j->top_start << "," << j->top_end << ")";
			cout <<"\t"<< j->weight;
			cout << endl;
		}
	}
	cout << "MST = " << _weight << endl;
}

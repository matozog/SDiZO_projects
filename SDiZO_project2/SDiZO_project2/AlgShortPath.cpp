#include "AlgShortPath.h"
#include "Graph.h"
#include <iostream>
#include <iomanip>

using namespace std;
const int MAX_INT = 2000000;

AlgShortPath::AlgShortPath(Graph graph)
{
	this->_amountOfTops = graph.amountOfTops();
	this->_amountOfEdges = graph.amountOfEdges();
	this->_top_start = graph.top_start();
	this->_tableList = graph.tableList();
	this->_matrixOfEdges = graph.matrixOfEdges(); 
	tableCosts_Dij = new int[_amountOfTops];
	tablePrev_Dij = new int[_amountOfTops];
	tableCosts_BF = new int[_amountOfTops];
	tablePrev_BF = new int[_amountOfTops];
}

AlgShortPath::~AlgShortPath()
{
	delete[]tableCosts_Dij;
	delete[]tableCosts_BF;
	delete[]tablePrev_Dij;
	delete[]tablePrev_BF;
}

void AlgShortPath::AddCostsAndPrev(int *tableCosts, int *tablePrev)
{
	for (int i = 0; i < _amountOfTops; i++)
	{
		tableCosts[i] = MAX_INT;
		tablePrev[i] = -1;
	}
	tableCosts[_top_start] = 0;
	tablePrev[_top_start] = _top_start;
}

void AlgShortPath::DijkstraAlgorithmList()
{
	edge element;
	bool *visited = new bool[_amountOfTops];
	bool all_true = false;
	list<edge>::iterator it;
	list<edge>::iterator it1;
	priority_queue<edge, vector<edge>, edge> queue;
	AddCostsAndPrev(tableCosts_Dij, tablePrev_Dij);
	for (it = _tableList[_top_start].begin(); it != _tableList[_top_start].end(); it++)
	{
		queue.push(*it);
	}
	for (int i = 0; i < _amountOfTops; i++) visited[i] = false;
	visited[_top_start] = true;
	do{
		element = queue.top();
		queue.pop();
		for (it = _tableList[element.top_start].begin(); it != _tableList[element.top_start].end(); it++)
		{
			if (tableCosts_Dij[it->top_end] > (tableCosts_Dij[it->top_start] + it->weight))
			{
				tableCosts_Dij[it->top_end] = tableCosts_Dij[it->top_start] + it->weight;
				tablePrev_Dij[it->top_end] = it->top_start;
			}
		}
		if (visited[element.top_end] == false)
		{
			for (it = _tableList[element.top_end].begin(); it != _tableList[element.top_end].end(); it++)
			{
				queue.push(*it);
			}
		}
		visited[element.top_end] = true;
		all_true = true;
		for (int i = 0; i < _amountOfTops; i++)
		{
			if (visited[i] == false)
			{
				all_true = false;
				break;
			}
		}
	} while (all_true==false);
	display_shortest_road(tableCosts_Dij, tablePrev_Dij);
}

void AlgShortPath::DijkstraAlgorithmMatrix()
{
	edge element;
	priority_queue<edge, vector<edge>, edge> queue;
	AddCostsAndPrev(tableCosts_Dij, tablePrev_Dij);
	bool *visited = new bool[_amountOfTops];
	bool all_true = false;
	for (int j = 0; j < _amountOfTops; j++)
	{
		if (_matrixOfEdges[_top_start][j].weight != MAX_INT)
		{
			queue.push(_matrixOfEdges[_top_start][j]);
		}
	}
	for (int i = 0; i < _amountOfTops; i++) visited[i] = false;
	visited[_top_start] = true;
	do
	{
		element = queue.top();
		queue.pop();
		for (int i = 0; i < _amountOfTops; i++)
		{
			if (_matrixOfEdges[element.top_start][i].weight != MAX_INT)
			{
				if (tableCosts_Dij[_matrixOfEdges[element.top_start][i].top_end] > tableCosts_Dij[element.top_start] + _matrixOfEdges[element.top_start][i].weight)
				{
					tableCosts_Dij[_matrixOfEdges[element.top_start][i].top_end] = tableCosts_Dij[element.top_start] + _matrixOfEdges[element.top_start][i].weight;
					tablePrev_Dij[_matrixOfEdges[element.top_start][i].top_end] = element.top_start;
				}
			}
		}
		if (visited[element.top_end] == false)
		{
			for (int j = 0; j < _amountOfTops; j++)
			{
				if (_matrixOfEdges[element.top_end][j].weight != MAX_INT)
				{
					queue.push(_matrixOfEdges[element.top_end][j]);
				}
			}
		}
		visited[element.top_end] = true;
		all_true = true;
		for (int i = 0; i < _amountOfTops; i++)
		{
			if (visited[i] == false)
			{
				all_true = false;
				break;
			}
		}
	} while(all_true==false);
	display_shortest_road(tableCosts_Dij, tablePrev_Dij);

}

void AlgShortPath::BellmanFordAlgorithmList()
{
	list<edge>::iterator it;
	bool change;
	bool negative=false;
	AddCostsAndPrev(tableCosts_BF, tablePrev_BF);
	for (int k = 0; k < _amountOfTops - 1; k++)
	{
		change = false;
		for (int i = 0; i < _amountOfTops; i++)
		{
			for (it = _tableList[i].begin(); it != _tableList[i].end(); it++)
			{
				if (tableCosts_BF[it->top_end] > (tableCosts_BF[it->top_start] + it->weight))
				{
					tableCosts_BF[it->top_end] = tableCosts_BF[it->top_start] + it->weight;
					tablePrev_BF[it->top_end] = it->top_start;
					change = true;
				}
			}
		}
		if (!change) break;
	}
	for (int i = 0; i < _amountOfTops; i++)
	{
		for (it = _tableList[i].begin(); it != _tableList[i].end(); it++)
		{
			if (tableCosts_BF[it->top_end] >(tableCosts_BF[it->top_start] + it->weight))
			{
				cout << "CYKL UJEMNY!" << endl;
				system("pause");
				negative = true;
				break;
			}
		}
	}
	if(!negative)
	display_shortest_road(tableCosts_BF, tablePrev_BF);
	}

void AlgShortPath :: BellmanFordAlgorithmMatrix()
{
	bool negative = false;
	AddCostsAndPrev(tableCosts_BF, tablePrev_BF);
	bool change;
	for (int k = 0; k < _amountOfTops - 1; k++)
	{
		change = false;
		for (int i = 0; i < _amountOfTops; i++)
		{
			for (int j = 0; j < _amountOfTops; j++)
			{
				if (_matrixOfEdges[i][j].weight != MAX_INT) {
					if (tableCosts_BF[_matrixOfEdges[i][j].top_end]  >(tableCosts_BF[_matrixOfEdges[i][j].top_start] + _matrixOfEdges[i][j].weight))
					{
						tableCosts_BF[_matrixOfEdges[i][j].top_end] = tableCosts_BF[_matrixOfEdges[i][j].top_start] + _matrixOfEdges[i][j].weight;
						tablePrev_BF[_matrixOfEdges[i][j].top_end] = _matrixOfEdges[i][j].top_start;
						change = true;
					}
				}
			}
		}
		if (!change) break;
	}

	for (int i = 0; i < _amountOfTops; i++)
	{
		for (int j = 0; j < _amountOfTops; j++)
		{
			if (_matrixOfEdges[i][j].weight != MAX_INT) {
				if (tableCosts_BF[_matrixOfEdges[i][j].top_end]  >(tableCosts_BF[_matrixOfEdges[i][j].top_start] + _matrixOfEdges[i][j].weight))
				{
					cout << "CYKL UJEMNY!" << endl;
					system("pause");
					negative = true;
					break;
				}
			}
		}
	}
	if(!negative)
	display_shortest_road(tableCosts_BF, tablePrev_BF);
	}

void AlgShortPath::display_shortest_road(int tableCosts[], int tablePrev[])
{
	list<int>::iterator it_tmp;
	int j = 0;
	list<int> tmp_list;
	cout << "Start = " << _top_start << endl;
	cout << setw(6) << left << "End" << setw(6) << left << "Dist" << setw(6) << left << "Path" << endl;
	for (int i = 0; i < _amountOfTops; i++)
	{
		j = i;
		cout << setw(5) << right << i << "|" << setw(5) << right << tableCosts[i] << "|";
		do {
			tmp_list.push_front(tablePrev[j]);
			j = tablePrev[j];
		} while (j != _top_start);
		if (i != _top_start)
		{
			tmp_list.push_back(i);
		}
		for (it_tmp = tmp_list.begin(); it_tmp != tmp_list.end(); it_tmp++)
		{
			cout << " " << *it_tmp;
		}
		tmp_list.clear();
		cout << endl;
	}
}

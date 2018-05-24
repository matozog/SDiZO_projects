#include "MSTAlg.h"
#include "Graph.h"

using namespace std;

const int MAX_INT = 2000000;

MSTAlg::MSTAlg(Graph graph)
{
	this->_amountOfTops = graph.amountOfTops();
	this->_amountOfEdges = graph.amountOfEdges();
	this->_tableList_undir = graph.tableList_undir();
	this->_matrixOfEdges_undir = graph.matrixOfEdges_undir();
}

void MSTAlg::KruskalAlgorithmList()
{
	priority_queue<edge, vector<edge>, edge> queue_kruskal;
	edge element;
	list<edge>::iterator it;
	int *color_table = new int[_amountOfTops];
	MSTree mstree(_amountOfTops);
	for (int i = 0; i < _amountOfTops; i++)
	{
		for (it = _tableList_undir[i].begin(); it != _tableList_undir[i].end(); it++)
		{
			queue_kruskal.push(*it);
		}
		color_table[i] = i;
	}
	for (int i = 0; i < _amountOfTops - 1; i++)
	{
		do {
			element = queue_kruskal.top();
			queue_kruskal.pop();
		} while (color_table[element.top_start]==color_table[element.top_end]);
		mstree.add_edge(element.top_start, element);
		join_subtrees(color_table, element);
	}
	mstree.diplay_tree();
	delete[]color_table;
}

void MSTAlg::join_subtrees(int *to_visit_tops, edge element)
{
	if (to_visit_tops[element.top_start] < to_visit_tops[element.top_end])
	{
		for (int i = 0; i < _amountOfTops; i++)
		{
			if (to_visit_tops[i] == to_visit_tops[element.top_end] && i != element.top_end)
			{
				to_visit_tops[i] = to_visit_tops[element.top_start];
			}
		}
		to_visit_tops[element.top_end] = to_visit_tops[element.top_start];
	}
	else
	{
		for (int i = 0; i < _amountOfTops; i++)
		{
			if (to_visit_tops[i] == to_visit_tops[element.top_start] && i != element.top_start)
			{
				to_visit_tops[i] = to_visit_tops[element.top_end];
			}
		}
		to_visit_tops[element.top_start] = to_visit_tops[element.top_end];
	}
}

void MSTAlg::KruskalAlgorithmMatrix()
{
	priority_queue<edge, vector<edge>, edge> queue_kruskal;
	edge element;
	list<edge>::iterator it;
	int *color_table = new int[_amountOfTops];
	MSTree mstree(_amountOfTops);
	for (int i = 0; i < _amountOfTops; i++)
	{
		for (int j = 0; j < _amountOfTops; j++)
		{
			if (_matrixOfEdges_undir[i][j].weight != MAX_INT)
			{
				queue_kruskal.push(_matrixOfEdges_undir[i][j]);
			}
		}
		color_table[i] = i;
	}
	for (int i = 0; i < _amountOfTops - 1; i++)
	{
		do {
			element = queue_kruskal.top();
			queue_kruskal.pop();
		} while (color_table[element.top_start] == color_table[element.top_end]);
		mstree.add_edge(element.top_start, element);
		join_subtrees(color_table, element);
	}
	mstree.diplay_tree();
	delete[]color_table;
}

void MSTAlg::PrimAlgorithmList()
{
	priority_queue<edge, vector<edge>, edge> queue_kruskal;
	int j = 0;
	list<edge>::iterator it;
	edge element;
	MSTree mstreePrim(_amountOfTops);
	bool *visited = new bool[_amountOfEdges];
	for (int i = 0; i < _amountOfEdges; i++)
	{
		visited[i] = false;
	}
	visited[j] = true;
	for (int i = 0; i < _amountOfTops - 1; i++)
	{
		for (it = _tableList_undir[j].begin(); it != _tableList_undir[j].end(); it++)
		{
			queue_kruskal.push(*it);
		}
		do {
			element = queue_kruskal.top();
			queue_kruskal.pop();
		} while (visited[element.top_end] != false);
		mstreePrim.add_edge(element.top_start, element);
		visited[element.top_end] = true;
		j = element.top_end;
	}
	mstreePrim.diplay_tree();
	delete[]visited;
}

void MSTAlg::PrimAlgorithmMatrix()
{
	priority_queue<edge, vector<edge>, edge> queue_kruskal;
	MSTree mstree(_amountOfTops);
	int j = 0;
	bool *visited = new bool[_amountOfTops];
	for (int i = 1; i < _amountOfTops; i++)
	{
		visited[i] = false;
	}
	visited[j] = true;
	for (int i = 0; i < _amountOfTops - 1; i++)
	{
		for (int k = 0; k < _amountOfTops; k++)
		{
			if (_matrixOfEdges_undir[j][k].weight != MAX_INT)
				queue_kruskal.push(_matrixOfEdges_undir[j][k]);
		}
		do {
			element = queue_kruskal.top();
			queue_kruskal.pop();
		} while (visited[element.top_end] != false);
		mstree.add_edge(element.top_start, element);
		visited[element.top_end] = true;
		j = element.top_end;
	}
	mstree.diplay_tree();
	delete[]visited;
}
#include "Graph.h"
#include "MSTree.h"
#include <iostream>
#include <fstream>
#include <list>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;
const int MAX_INT = 2000000;

Graph::Graph()
{
}

/*Graph::~Graph()
{
	for (int i = 0; i < _amountOfTops; i++)
	{
		delete[]_matrixOfEdges[i];
		delete[]_matrixOfEdges_undir[i];
	}
	delete[]_matrixOfEdges;
	delete[]_matrixOfEdges_undir;
	//delete[]_tableList;
	//delete[]_tableList_undir;

}*/

void Graph::read_file( string file_name)
{
	ifstream file;
	int tab[4];
	file.open(file_name);
	if (file.is_open())
	{
		if (file_read_line(file, tab, 4))
		{
			this->_amountOfEdges = tab[0];
			this->_amountOfTops = tab[1];
			this->_top_start = tab[2];
			this->_top_end = tab[3];
			init_matrixEdge();
			init_listEdge();
			for (int i = 0; i < _amountOfEdges; i++)
			{
				if (file_read_line(file, tab, 3))
				{
					edge element;
					element.top_start = tab[0];
					element.top_end = tab[1];
					element.weight = tab[2];

					_matrixOfEdges[tab[0]][tab[1]] = element;
					_matrixOfEdges_undir[tab[0]][tab[1]] = element;

					_tableList[tab[0]].push_back(element);
					_tableList_undir[tab[0]].push_back(element);
					element.top_start = tab[1];
					element.top_end = tab[0];
					_matrixOfEdges_undir[tab[1]][tab[0]] = element;
					_tableList_undir[tab[1]].push_back(element);
				}
				else {
					cout << "Blad odczytu krawedzi!" << endl;
					break;
				}
			}
		}
		else cout << "Blad odczytu danych" << endl;

		file.close();
	}
	else
	{
		cout << "Nie udalo sie znalezc pliku!" << endl;
		system("pause");
	}
}

bool Graph::file_read_line(ifstream &file, int tab[], int size)
{
	string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return false;
	istringstream in_ss(s);
	for (int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
			return(false);
	}
	return (true);
}

void Graph::init_matrixEdge()
{
	_matrixOfEdges = new edge*[_amountOfTops];
	_matrixOfEdges_undir = new edge*[_amountOfTops];
	for (int i = 0; i < _amountOfTops;i++)
	{
			_matrixOfEdges[i] = new edge[_amountOfTops];
			_matrixOfEdges_undir[i] = new edge[_amountOfTops];
			for (int j = 0; j < _amountOfTops; j++)
			{
				_matrixOfEdges_undir[i][j].weight = MAX_INT;
				_matrixOfEdges[i][j].weight = MAX_INT;
			}
	}
}

void Graph::init_listEdge()
{
	_tableList = new list<edge>[_amountOfTops];
	_tableList_undir = new list<edge>[_amountOfTops];
	for (int i = 0; i < _amountOfTops; i++)
	{
		list<edge> *listNeigh = new list<edge>;
		_tableList[i] = *listNeigh;
		list<edge> *listNeigh1 = new list<edge>;
		_tableList_undir[i] = *listNeigh1;
	}
}

void Graph::display_matrix_neigh(edge **matrixOfEdges)
{
	cout << "   ";
	for (int i = 0; i < _amountOfTops; i++)
	{
		cout <<setw(2)<<right<< i << " ";
	}
	cout << endl;
	for (int i = 0; i < _amountOfTops; i++)
	{
		cout << "---";
	}
	cout<<endl;
	for (int i = 0; i < _amountOfTops; i++)
	{
		cout << setw(2) << left << i << "|";
		for (int j = 0; j < _amountOfTops; j++)
		{
			if (matrixOfEdges[i][j].weight == MAX_INT)
			{
				cout << setw(2) << right << "*" << " ";
			}
			else
			cout<<setw(2)<<right<<matrixOfEdges[i][j].weight<<" ";
		}
		cout << endl;
	}
}

void Graph::display_list_neigh(list<edge> *tableList)
{
	list<edge>::iterator j;
	for (int i = 0; i < _amountOfTops; i++)
	{
		cout << "A[" << i << "] = ";
		for (j = (tableList[i]).begin(); j != (tableList[i]).end(); j++)
		{
			cout << "("<<j->top_end<<","<<j->weight<<") ";
		}
		cout << endl;
	}
}

#include "TravellingSalesman.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>

using namespace std;


TravellingSalesman::TravellingSalesman()
{
}

TravellingSalesman::~TravellingSalesman()
{
	for (int i = 0; i < towns; i++)
	{
		delete[]tableDistances[i];
	}
	delete[]tableDistances;
	delete[]permutationTable;
}

void TravellingSalesman::AlgorithmBruteForce()
{
	bestDistance = 20000;
	bestPath = new int[towns];
	bestPath[towns-1] = 0;
	bestPath[0] = 0;
	permutationTable[towns] = 0;
	permutationTable[0] = 0;
	for (int i = 1; i < towns; i++)
		permutationTable[i] = i;
	permutation(towns - 1,1);
	showPathB();
	delete[]bestPath;
}

void TravellingSalesman::permutation(int sortTo, int sortFrom)
{
	if (sortFrom == sortTo)
	{
		distanceBrute = 0;
		for (int j = 1; j < towns + 1; j++)
		{
		distanceBrute += tableDistances[permutationTable[j - 1]][permutationTable[j]];
		}
		if (distanceBrute < bestDistance)
		{
			copy(permutationTable+1, permutationTable + towns , stdext::checked_array_iterator<int*>(bestPath,towns-1));
			bestDistance = distanceBrute;
		}
	}
	else {
		for (int i = sortFrom; i <= sortTo; i++)
		{
			swap(permutationTable[sortFrom], permutationTable[i]);
			permutation(sortTo, sortFrom + 1);
			swap(permutationTable[sortFrom], permutationTable[i]);
		}
	}
}

void TravellingSalesman::showPathB()
{
	cout << "\nBrute force algorithm(TravellingSalesman):" << endl;
	cout << "--------------------------" << endl;
	cout << "Length = " << bestDistance << endl;
	cout << "Path = ";
	cout << "0 - ";
	for (int i = 0; i < towns; i++)
	{
		cout << bestPath[i];
		if (i != towns - 1)
			cout << " - ";
	}
	cout << endl;
}

void TravellingSalesman::GreedyAlgorithm()
{
	path.clear();
	bestDistance = 20000;
	int *visitedTowns = new int[towns];
	int cost = 0, currentTown=0,minValue,tmp=0;

	for (int i = 0; i < towns; i++)
		visitedTowns[i] = 0;
	visitedTowns[currentTown] = 1;
	for (int i = 0; i < towns - 1; i++)
	{
		minValue = 20000;
		for (int k = 0; k < towns; k++)
		{
			if ((tableDistances[currentTown][k] < minValue) && (tableDistances[currentTown][k]!=0) && (visitedTowns[k]==0)) {
				minValue = tableDistances[currentTown][k];
				tmp = k;
			}
		}
		cost += minValue;
		currentTown = tmp;
		path.push_back(tmp);
		visitedTowns[tmp] = 1;
	}
	path.push_back(0);
	cost += tableDistances[currentTown][0];
	showPathG(path,cost);
	delete[]visitedTowns;
}

void TravellingSalesman::showPathG(vector<int> path, int cost)
{
	cout << "\nGreedy algorithm(TravellingSalesman):" << endl;
	cout << "--------------------------" << endl;
	cout << "Length = " << cost<<endl;
	cout << "Path = ";
	cout << "0 - ";
	for (int i = 0; i < towns; i++)
	{
		cout << path[i];
		if (i != towns - 1)
			cout << " - ";
	}
	cout << endl << endl;;
}

void TravellingSalesman::readFromFile(string file_name)
{
	ifstream file;
	int tab[1], *tmp;
	file.open(file_name);
	if (file.is_open())
	{
		if (file_read_line(file, tab, 1))
		{
			towns = tab[0];
			tmp = new int[towns];
			permutationTable = new int[towns + 1];
			bestPath = new int[towns];
			initMatrix();
			for (int i = 0; i < towns; i++)
			{
				if (file_read_line(file, tmp, towns))
				{
					for (int j = 0; j < towns; j++)
						tableDistances[i][j] = tmp[j];
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

void TravellingSalesman::initMatrix()
{
	tableDistances = new int*[towns];
	for (int i = 0; i < towns; i++)
	{
		tableDistances[i] = new int[towns];
	}
}

void TravellingSalesman::showMatrix()
{
	cout << "TravellingSalesman problem: " << endl;
	cout << endl << "Numbers of cities: " << towns << endl;
	cout << endl;
	cout << "    ";
	for (int i = 0; i < towns; i++)
	{
		cout << setw(3) << right << i << " ";
	}
	cout << endl;
	for (int i = 0; i < towns; i++)
	{
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < towns; i++)
	{
		cout << setw(3) << left << i << "|";
		for (int j = 0; j < towns; j++)
		{
				cout << setw(3) << right << tableDistances[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool TravellingSalesman::file_read_line(ifstream &file, int tab[], int size)
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
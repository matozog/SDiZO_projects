#include "Backpack.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

Backpack::Backpack()
{
}

Backpack::~Backpack()
{
}

void Backpack::GreedyAlgorithmV()
{
	priority_queue<Item, vector<Item>, Item> queue;
	string type = "sort by value: ";
	vectorID.clear();
	int sumWeight = 0;
	for (int i = 0; i < items; i++)
	{
		queue.push(vectorItems[i]);
	}

	for (int i = 0; i < items; i++)
	{
		if (queue.top().weight + sumWeight <= capacity)
		{
			sumWeight += queue.top().weight;
			vectorID.push_back(queue.top().id);
		}
		queue.pop();
	}
	showBackpackGreedy(vectorID, sumWeight,type);
}

void Backpack::GreedyAlgorithm()
{
	priority_queue<Item, vector<Item>,SortByFactor> queue;
	string type = "sort by ratio: ";
	vectorID.clear();
	int sumWeight = 0;
	for (int i = 0; i < items; i++)
	{
		queue.push(vectorItems[i]);
	}

	for (int i = 0; i < items; i++)
	{
		if (queue.top().weight + sumWeight <= capacity)
		{
			sumWeight += queue.top().weight;
			vectorID.push_back(queue.top().id);
		}
		queue.pop();
	}
	showBackpackGreedy(vectorID, sumWeight,type);
}

void Backpack::showBackpackGreedy(vector<int> vectorID, int sumWeight,string type)
{
	int cost = 0;
	cout << "\nGreedy algorithm " + type << endl;
	cout << "--------------------------" << endl;
	cout << "Item  Size  Value" << endl;
	cout << "--------------------------" << endl;
	sort(vectorID.begin(), vectorID.end());
	for (int i = 0; i < vectorID.size(); i++)
	{
		cout << setw(3) << right << vectorID.at(i) << "  " << setw(4) << right << vectorItems[vectorID.at(i)].weight << "  " << setw(5) << right << vectorItems[vectorID.at(i)].value << endl;
		cost += vectorItems[vectorID.at(i)].value;
	}
	cout << "---------------------------" << endl;
	cout << "Total  " << sumWeight << setw(7) << right << cost << endl << endl;;
}

void Backpack::AlgorithmBruteForce()
{
	int weight, value, best_value=0, subset;

	for (int i = 1; i < pow(2, items); i++)
	{
		weight = 0;
		value = 0;
		for (int k = 0; k < items; k++)
		{
			if (binaryBit(i,k) == true)
			{
				weight += vectorItems[k].weight;
				value += vectorItems[k].value;
			}
		}
		if ((value > best_value) && (weight <= capacity))
		{
			best_value = value;
			subset = i;
		}
	}
	cout << "";
	showBackpackBrute(subset);
}

bool Backpack::binaryBit(int number, int positionBit)
{
	int w = 0, tmp[31];
	while (number)
	{
		tmp[w++] = number % 2;
		number /= 2;
	}
	if (tmp[positionBit] == 1) return true;
	else return false;
}

void Backpack::showBackpackBrute(int subset)
{
	int cost = 0, weight = 0;
	int tmp[31], w = 0;
	for (int i = 0; i < 31; i++) tmp[i] = 0;
	while (subset)
	{
		tmp[w] = subset % 2;
		subset /= 2;
		w++;
	}
	cout << "\nBrute Force:" << endl;
	cout << "--------------------------" << endl;
	cout << "Item  Size  Value" << endl;
	cout << "--------------------------" << endl;
	for (int i = 0; i < items; i++)
	{
		if (tmp[i] == 1)
		{
			cout <<setw(3)<<right<< i << "  " <<setw(4)<<right<< vectorItems[i].weight << "  " << setw(5)<<right<<vectorItems[i].value << endl;
			weight += vectorItems[i].weight;
			cost += vectorItems[i].value;
		}
	}
	cout << "---------------------------" << endl;
	cout << "Total  " << weight << setw(7) << right << cost << endl<<endl;

}

void Backpack::showItems()
{
	cout << "Backpack problem: " << endl;
	cout << endl << "Capacity: " << capacity << endl;
	cout << "Items: " << items << endl;
	cout <<endl<< "Item  Size  Value" << endl;
	cout << "--------------------------" << endl;
	for (int i = 0; i < items; i++)
	{
		cout << setw(3) << right << i << "  " << setw(4) << right << vectorItems[i].weight << "  " << setw(5) << right << vectorItems[i].value << endl;
	}
	cout << endl;
}

void Backpack::readFromFile(string file_name)
{
	ifstream file;
	int tab[2],k=0,m=0,id=0;
	Item item;
	vectorItems.clear();
	file.open(file_name);
	if (file.is_open())
	{
		if (file_read_line(file, tab, 2))
		{
			capacity = tab[0];
			items = tab[1];
			for (int i = 0; i < items; i++)
			{
				if (file_read_line(file, tab, 2))
				{
					item.weight = tab[0];
					item.id = id;
					id++;
					item.value = tab[1];
					item.factor = (float)tab[1] / (float)tab[0];
					vectorItems.push_back(item);
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


bool Backpack::file_read_line(ifstream &file, int tab[], int size)
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
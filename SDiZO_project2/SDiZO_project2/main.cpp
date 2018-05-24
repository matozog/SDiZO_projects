#include <iostream>
#include "Graph.h"
#include "AlgShortPath.h"
#include "MSTAlg.h"
#include <Windows.h>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{	
	int choice = 0;
	string file_name="test.txt";
	Graph graph;
	do {
		cout << "Menu\n";
		cout << "1.Wczytaj graf z pliku\n";
		cout << "2.Wyswietl graf macierzowo i listowo\n";
		cout << "3.Algorytmy MST macierzowo i listowo\n";
		cout << "4.Algorytmy najkrotszej sciezki macierzowo i listowo\n";
		cout << "5.Wyjscie.\n";
		cin >> choice;
		switch(choice)
		{
		case 1:
			{
				cout << "Podaj nazwe pliku: ";
				cin >> file_name;
				graph.read_file(file_name);
			}
			break;
		case 2:
			{
				graph.display_list_neigh(graph.tableList());
				cout << endl;
				graph.display_matrix_neigh(graph.matrixOfEdges());
			}
			break;
		case 3:
			{
				MSTAlg mstalg(graph);
				cout << "\nAlgorytm KRUSKALA LISTA\n";
				mstalg.KruskalAlgorithmList();
				cout << "\nAlgorytm KRUSKALA MACIERZ\n";
				mstalg.KruskalAlgorithmMatrix();
				cout << "\nAlgorytm PRIMA LISTA\n";
				mstalg.PrimAlgorithmList();
				cout << "\nAlgorytm PRIMA MACIERZ\n";
				mstalg.PrimAlgorithmMatrix();
			}
			break;
		case 4:
			{
			AlgShortPath algshortpath(graph);
			cout << "\nAlgorytm DIJKSTRY LISTA\n";
			algshortpath.DijkstraAlgorithmList();
			cout << "\nAlgorytm DIJKSTRY  MACIERZ\n";
			algshortpath.DijkstraAlgorithmMatrix();
			cout << "\nAlgorytm BELLMANA FORDA LISTA\n";
			algshortpath.BellmanFordAlgorithmList();
			cout << "\nAlgorytm BELLMANA FORDA MACIERZ\n";
			algshortpath.BellmanFordAlgorithmMatrix();
			}
			break;
		}
	} while (choice != 5);

	system("pause");
	return 0;
}
#include <iostream>
#include "Backpack.h"
#include "TravellingSalesman.h"
#include <Windows.h>
#include <iomanip>

using namespace std;

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int )count.QuadPart);
}

void test_TSP()
{
	TravellingSalesman TravellingSalesman;
	int TravellingSalesmanBF[5] = { 10,11,12,13,14 };
	int TravellingSalesmanG[5] = { 100,500,1000,1500,2000 };
	fstream plik;
	string file,saveTo;
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	long long int tmp[5] = { 0,0,0,0,0 };
	for (int k = 4; k < 5; k++) {
		for (int m = 0; m < 10; m++) {

			file = "GreedyTSP/TSP-G_" + to_string(TravellingSalesmanG[k]) + "-test" + to_string(m) + ".txt";
			TravellingSalesman.readFromFile(file);
			start = read_QPC();
			TravellingSalesman.GreedyAlgorithm();
			elapsed = read_QPC() - start;
			tmp[k] += elapsed;
			}
		tmp[k] /= 10;
		cout << "\nTime [ms]  = " << fixed << setprecision(3) << 1000.0*tmp[k] / frequency << endl;
		}

	saveTo = "greedyTSP_results.txt";
	plik.open(saveTo, ios::out);
	if (plik.good())
	{
		for (int i = 4; i < 5; i++)
		{
			plik << "greedyTSP_Towns_" << TravellingSalesmanG[i] << ": " << (1000.0*tmp[i]/frequency) << " ms\n";
		}
	}
	else cout << "Blad";

}

void test_Backpack()
{
	Backpack backpack;
	int BackpackBF[5] = {12,18 ,20, 22 , 26 }, capacity[3] = {400,800,1200};
	int BackpackG[5] = { 1000,5000,10000,15000,20000 };
	fstream plik;
	string file, saveTo;
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	long long int tmp[3][5] = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
	for (int c = 0; c < 3; c++)
	{
		for (int k = 0; k < 5; k++) {
			for (int m = 0; m < 100; m++) {

				file = "GreedyB/B-G_Cap_" + to_string(capacity[c]) + "_Items_" + to_string(BackpackG[k]) + "-test" + to_string(m) + ".txt";;
				backpack.readFromFile(file);
				
				start = read_QPC();
				backpack.GreedyAlgorithmV();
				elapsed = read_QPC() - start;
				tmp[c][k] += elapsed;
			}
			tmp[c][k] /= 100;
			cout << "\nTime [ms]  = " << fixed << setprecision(3) << 1000.0*tmp[c][k] / frequency << endl;
		}
	}

	saveTo = "greedyVB_results.txt";
	plik.open(saveTo, ios::out);
	if (plik.good())
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 5; j++)
				{
					plik << "greedyB_Cap_" << capacity[i] << "_Items_" << BackpackG[j] << ": " << 1000.0*tmp[i][j] / frequency << " ms\n";
				}
		}
	}
	else cout << "Blad" << endl;
}

int main()
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	int choice = 0;
	string file_name = "test.txt";
	TravellingSalesman travellingSalesman;
	Backpack backpack;

	do {
		system("cls");
		cout << "Menu\n";
		cout << "1.Dyskretny problem plecakowy\n";
		cout << "2.Asymetryczny problem komiwojazera\n";
		cout << "0.Wyjscie.\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("cls");
			do
			{
				cout << "1.Wczytaj plik.\n";
				cout << "2.Wykonaj algorytmy.\n";
				cout << "3.Cofnij.\n";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					cout << "Podaj nazwe pliku: ";
					cin >> file_name;
					backpack.readFromFile(file_name);
					cout << endl;
				}
				break;
				case 2:
				{
					backpack.showItems();
					backpack.AlgorithmBruteForce();
					backpack.GreedyAlgorithm();
					backpack.GreedyAlgorithmV();
				}
				break;
				}
			} while (choice != 3);
		}
		break;
		case 2:
		{
			system("cls");
			do {
				cout << "1.Wczytaj plik.\n";
				cout << "2.Wykonaj algorytmy.\n";
				cout << "3.Cofnij.\n";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					cout << "Podaj nazwe pliku: ";
					cin >> file_name;
					travellingSalesman.readFromFile(file_name);
					cout << endl;
				}
					break;
				case 2:
				{
					travellingSalesman.showMatrix();
					travellingSalesman.AlgorithmBruteForce();
					travellingSalesman.GreedyAlgorithm();
				}
					break;
				}
			} while (choice!=3);
		}
		break;
		}
	} while (choice != 0);
	return 0;
}
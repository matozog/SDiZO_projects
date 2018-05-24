#include "Array.h"
#include <fstream>
#include <string>

using namespace std;


void Array::add_element(int index, int value)  // dodawanie elementu do tablicy
{
	if (size == 0)						// gdy brak elementów tworzymy tablice
	{
		size++;
		array = new int[size];
		array[0] = value;
	}
	else if (index > size || index < 0)
	{
		cout << "Nie uda sie umiescic tu elementu!"<<endl;
		system("pause");
	}
	else
	{
		int *T = new int[size + 1];
		if (index == 0)					// wariant wstawiana na pocz¹tku
		{
			T[0] = value;
			for (int i = 0; i < size; i++)
			{
				T[i + 1] = array[i];
			}
		}
		else if (index == size)				// wariant wstawiania na koñcu
		{
			for (int i = 0; i < size; i++)
			{
				T[i] = array[i];
			}
			T[size] = value;
		}
		else
		{												// wstawianie elementu wewn¹trz tablicy
			for (int i = 0; i < index; i++)				// kopiujemy zawartoœæ starej tablic do indeksu wskazanego
			{											// nastêpnie w miejsce indeksu wstawiamy wartoœæ i kopiujemy resztê
				T[i] = array[i];
			}
			T[index] = value;
			for (int i = index; i < size; i++)
			{
				T[i + 1] = array[i];
			}
		}
		size++;
		delete []array;
		array = T;
	}
}

void Array::delete_element(int index) // usuwanie elementu z tablicy
{
	if (size == 0)
	{
		cout << "Brak elementow w tablicy!" << endl;
		system("pause");
	}
	else if (index < 0 || index > size)
	{
		cout << "Zly element!"<<endl;
		system("pause");
	}
	else if (size == 1)
	{
		size--;
		delete []array;
	}
	else
	{		
		int *T = new int[size - 1];					// podobnie jak w dodawaniu do œrodka, tym razem pomijamy element o zadanym indeksie
		for (int i = 0; i < index-1 ; i++)
		{
			T[i] = array[i];
		}
		for (int i = index; i < size; i++)
		{
			T[i-1] = array[i];
		}
		size--;
		delete []array;
		array = T;
	}
}

void Array::read_file()
{
	fstream file;
	file.open("test.txt", ios::in);
	if (file.good() == false)
	{
		cout << "Nie udalo sie znalezc pliku!" << endl;
		system("pause");
	}
	else
	{
		int x, *T, new_size;
		file >> new_size;
		T = new int[new_size];
		for (int i = 0; i < new_size; i++)
		{
			file >> x;
			T[i] = x;
		}
		size = new_size;
		array = T;
	}
	file.close();
}
void Array::search_element(int value) // wyszukiwanie elementu w tablicy
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] == value)
		{
			count++;
			if (count == 1)
			{
				cout << "Znaleziono element na pozycji: ";
				count++;
			}
			cout << i + 1 << " ";
		}
	}
	cout << endl;
	if (count==0)
	{
		cout << "Brak elementu w tablicy." << endl;
	}
	system("pause");
}

void Array::display_array() // wyswietlanie tablicy
{
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	system("pause");
}




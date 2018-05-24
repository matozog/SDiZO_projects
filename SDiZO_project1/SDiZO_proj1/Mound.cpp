#include "Mound.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void Mound::insert_element(int value)	//dodawanie elementu do kopca
{
	if (size == 0)						//jeœli brak kopca, to tworzymy go
	{
		int *T = new int[size + 1];
		T[size] = value;
		size++;
		array_m = T;
	}
	else
	{
		int *T = new int[size + 1];		// alokujemy tablice wiêksza od od dotychczasowego rozmiaru kopca
		for (int i = 0; i < size; i++)
		{
			T[i] = array_m[i];			// kopiujemy ca³a zawartoœæ starego kopca
		}
		T[size] = value;				// na koncu dodajemy nowy element
		int tmp = 0, s=size;
		while (s != 0)					// wykonujemy budowanie kopca do góry
		{
				if (T[s] > T[((s-1) / 2)])
				{
					swap(T[s], T[((s-1) / 2)]);
					s = ((s-1) / 2);
				}
				else break;
		}
		size++;
		delete []array_m;
		array_m = T;
	}
}

void Mound::delete_element()			// usuwanie elementu z kopca
{
	if (size == 0)
	{
		cout << "Kopiec pusty." << endl;
		system("pause");
	}
	else if (size == 1)
	{
		size = 0;
		delete []array_m;				// ca³kowite usuniêcie kopca
	}
	else
	{
		int *T = new int[size - 1];		// alokujemy tablice mniejsz¹ od starej
		int i = 0;
		T[0] = array_m[size - 1];
		for (int j = 1; j < size - 1; j++)
			T[j] = array_m[j];
		while ((2*i+1) < (size - 1))		// budowanie kopca do do³u
		{
			if ((2*i+2)>=size-1)
			{
				if (T[(2 * i + 1)] > T[i])
					swap(T[i], T[2 * i + 1]);
				break;
			}
			else if ((T[(2 * i+1)]>T[i]) || (T[(2 * i +2)]>T[i]))
			{
				if (T[(2 * i+1)] >= T[(2 * i + 2)])
				{
					swap(T[i], T[(2 * i+1)]);
					i = (2 * i+1);
				}
				else
				{
					swap(T[(2 * i + 2)], T[i]);
					i = (2 * i + 2);
				}
			}
			else break;
		}
		size--;
		delete []array_m;
		array_m = T;
	}
}

void Mound::read_file()
{
	fstream file;
	file.open("test.txt", ios::in);
	if (!file.good())
	{
		cout << "Nie udalo sie znalezc pliku!" << endl;
		system("pause");
	}
	else
	{
		int new_size, x;
		file >> new_size;
		int *T = new int[new_size];
		for (int i = 0; i < new_size; i++)		// wczytanie liczb w tablice pomocnicz¹
		{
			file >> x;
			T[i] = x;
		}
		file.close();
		size = new_size;
		rebuild(T);	
		//delete[]array_m;
		array_m = T;
	}
}

void Mound::rebuild(int *T)
{
	for (int i = (size - 2) / 2; i >= 0; i--)	// szukamy indeks ostatniego rodzica i przekazujemy do kolejnej funkcji
	{
		build(T, i);
	}
}

void Mound::build(int *T, int i)
{
		while (i < size)						// rozpoczynamy budowanie do do³u dla ka¿dego z rodziców
		{
			if ((2*i+1) >= size) break;
			else if ((T[i] < T[2 * i + 1]) || (T[i] < T[2 * i + 2]))
			{
				if (T[2 * i + 1] < T[2 * i + 2] && (2*i+2<size))
				{
					swap( T[2 * i + 2], T[i]);
					i = 2 * i + 2;
				}
				else
				{
					swap( T[2 * i + 1], T[i]);
					i = 2 * i + 1;
				}
			}
			else break;
		}
}

void Mound::search_element(int value)				// wyszukiwanie elementu w kopcu
{
	int count = 0;
	for (int i = 0; i < size; i++)					// przeszukujemy tablice i zwracamy ewentualne wyniki
	{
		if (array_m[i] == value)
		{
			count++;
			if (count == 1)
			{
				cout << "Znaleziono element na pozycji: ";
				count++;
			}
			cout << i << " ";
		}
	}
	cout << endl;
	if (count == 0)
	{
		cout << "Brak elementu w kopcu." << endl;
	}
	system("pause");
}

void Mound::display_mound(string sp, string sn,int v) // wyœwietlanie kopca
{
	string cl, cp, cr;
	string s;
	cl = cp = cr = "  ";
	cr[0] = 218;
	cl[0] = 192; 
	cl[1] = 196;
	cp[0] = 179;
	cr[1] = 196;
	if (v < size)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		display_mound(s + cp, cr, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << array_m[v] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		display_mound(s + cp, cl, 2 * v + 1);
	}

}

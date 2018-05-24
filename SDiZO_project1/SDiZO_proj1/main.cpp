#include <iostream>
#include <windows.h>
#include <random>
#include <cstdlib>
#include <iomanip>
#include "Array.h"
#include "List.h"
#include "Mound.h"
#include <Windows.h>

using namespace std;

void menu()
{
		cout << "1. Dodaj element." << endl;
		cout << "2. Usun element." << endl;
		cout << "3. Znajdz element." << endl;
		cout << "4. Wpisz dane z pliku." << endl;
		cout << "5. Wyswietl strukture." << endl;
		cout << "6. Glowne menu." << endl;
		cout << "--------------------------------------------" << endl;
}
void index_menu()
{
	cout << "Gdzie element wstawic/usunac: " << endl;
	cout << "1.Poczatek." << endl;
	cout << "2.Wybrany indeks." << endl;
	cout << "3.Koniec" << endl;
	cout << "--------------------------------------------" << endl;
}

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return(( long long int )count.QuadPart);
}

int main()
{
	int choice, value, index=0;
	Array array;
	Mound mound;
	List list;
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 1000000);
	do
	{
		cout << "Wybierz strukture danych: " << endl;
		cout << "1.Tablica. " << endl;
		cout << "2.Lista dwukierunkowa. " << endl;
		cout << "3.Kopiec. " << endl;
		cout << "4.Zakoncz program. " << endl;
		cout << "--------------------------------------------"<<endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			do {
				menu();
				cin >> choice;
				switch (choice)
				{
				case 1:
					cout << "Podaj wartosc elementu: ";
					cin >> value;
					if (array.get_size() != 0) {
						index_menu();
						cin >> choice;
						switch (choice)
						{
						case 1:
							array.add_element(0, value);
							break;
						case 2:
							cout << "Podaj numer indeksu: " << endl;
							cin >> index;
							array.add_element(index - 1, value);
							break;
						case 3:
							array.add_element(array.get_size(), value);
							break;
						}
					}
					else array.add_element(0, value);
					array.display_array();
					break;
				case 2:
					if (array.get_size() == 0)
					{
						cout << "Brak elemenetow w tablicy!" << endl;
						system("pause");
					}
					else {
						index_menu();
						cin >> choice;
						switch (choice)
						{
						case 1:
							array.delete_element(1);
							break;
						case 2:
							cout << "Podaj numer indeksu: " << endl;
							cin >> index;
							array.delete_element(index);
							break;
						case 3:
							array.delete_element(array.get_size());
							break;
						}
						array.display_array();
					}
					break;
				case 3:
					cout << "Podaj wartosc elementu, ktory chcesz znalezc: ";
					cin >> value;
					array.search_element(value);
					break;
				case 4:
					array.read_file();
					break;
				case 5:
					array.display_array();
					break;
				}
			} while (choice != 6);
			break;
		case 2:
			do {
				menu();
				cin >> choice;
				switch (choice)
				{
				case 1:
					if (list.get_size() != 0)
					{
						cout << "Podaj wartosc elementu: ";
						cin >> value;
						index_menu();
						cin >> choice;
						switch (choice)
						{
						case 1:
							list.add_element(1, value);
							break;
						case 2:
							cout << "Podaj numer elementu: " << endl;
							cin >> index;
							list.add_element(index, value);
							break;
						case 3:
							list.add_element(list.get_size() + 1, value);
							break;
						}
					}
					else
					{
						cout << "Podaj wartosc elementu: ";
						cin >> value;
						cout << endl;
						list.add_element(index, value);
					}
					list.display_list();
					break;
				case 2:
					if (list.get_size() == 0)
					{
						cout << "Brak elemenetow w tablicy!" << endl;
						system("pause");
					}
					else {
						index_menu();
						cin >> choice;
						switch (choice)
						{
						case 1:
							list.delete_element(1);
							break;
						case 2:
							cout << "Podaj numer indeksu: " << endl;
							cin >> index;
							list.delete_element(index);
							break;
						case 3:
							list.delete_element(list.get_size());
							break;
						}
						list.display_list();
					}
					break;
				case 3:
					cout << "Podaj wartosc elementu, ktory chcesz znalezc: ";
					cin >> value;
					list.search_element(value);
					break;
				case 4:
					list.read_file();
					break;
				case 5:
					list.display_list();
					break;
				}
			} while (choice != 6);
			break;
		case 3:
			do {
				cout << "1.Dodaj element do kopca." << endl;
				cout << "2.Usun element z kopca." << endl;
				cout << "3.Wyswietl kopiec." << endl;
				cout << "4.Wczytaj z pliku." << endl;
				cout << "5.Wyszukaj element." << endl;
				cout << "6.Glowne menu." << endl;
				cin >> choice;
				switch (choice)
				{
				case 1:
					cout << "Podaj wartosc: ";
					cin >> value;
					mound.insert_element(value);
					mound.display_mound("","",0);
					system("pause");
					break;
				case 2:
					mound.delete_element();
					mound.display_mound("","",0);
					system("pause");
					break;
				case 3:
					mound.display_mound("", "", 0);
					system("pause");
					break;
				case 4:
					mound.read_file();
					break;
				case 5:
					cout << "Podaj wartosc:";
					cin >> value;
					mound.search_element(value);
					break;
				}
			} while (choice != 6);
			break;
		}
	} while (choice != 4);
	//array.~Array();
	//mound.~Mound();
	//list.~List();
	return 0;
}
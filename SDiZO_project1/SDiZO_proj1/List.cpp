#include "List.h"
#include <string>
#include <fstream>

using namespace std;

void List::add_element(int index,int value)				// dodawanie elementu
{
	cell *element = new cell;							// nowy element
	if (size == 0)										// jeœli brak elementów w liœcie ustawiamy wskazniki nastepnika i poprzednika
	{
		element->value = value;							// na null, glowa i ogon wskazuj¹ ten element
		element->next = NULL;
		element->prev = NULL;
		head = element;
		tail = element;
		size++;
	}
	else if (index > 0 && index <= size + 1)
	{
		if (index == 1)							// przypadek dodawania na pocz¹tek
		{
			head->prev = element;
			element->next = head;
			element->prev = NULL;
			head = element;
		}
		else if (index == size + 1)				// dodawanie na koniec
		{
			tail->next = element;
			element->prev = tail;
			element->next = NULL;
			tail = element;
		}
		else
		{
			cell *tmp;
			cell *tmp2;
			if (index == size)						// dodawanie w miejsce ostatniego elementu
			{
				tmp = tail;
				tmp2 = tmp->prev;
				element->next = tmp;
				element->prev = tmp2;
				tmp->prev = element;
				tmp2->next = element;
			}
			else if (size / 2 < index)					// z racji listy dwukierunkowej, sprawdzamy, w któro miejsce mamy wstawic
			{											// element i od tej zaleznoœci wybieramy punkt startowy(glowa,ogon)
				tmp = tail;
				index = size - index;
				for (int i = 0; i < index; i++)
				{
					tmp = tmp->prev;
				}
				element->next = tmp;
				tmp2 = tmp->prev;
				element->prev = tmp2;
				tmp2->next = element;
				tmp->prev = element;
			}
			else
			{
				tmp = head;
				for (int i = 0; i < index - 2; i++)
				{
					tmp = head->next;
				}
				element->prev = tmp;
				tmp2 = tmp;
				tmp = tmp->next;
				element->next = tmp;
				tmp2->next = element;
				tmp->prev = element;
			}
		}
		element->value = value;
		size++;
	}
	else
	{
		cout << "Nie mozna wstawic w tym miejscu!" << endl;
		system("pause");
	}
}

void List::delete_element(int index)
{
	cell *tmp, *tmp2;

	if (size == 0)
	{
		cout << "Lista jest pusta.";
		return;
	}
	else if (index > 0 && index <= size )
	{
		if (index == size)		//usuwanie z konca
		{
			if (size == 1)
			{
				head = NULL;
				tail = NULL;
			}
			else {
				tmp = tail;
				tmp = tmp->prev;
				tmp->next = NULL;
				tail = tmp;
			}
		}
		else if (index == 1)		//usuwanie z  pocz¹tku
		{
			tmp = head;
			tmp = tmp->next;
			tmp->prev = NULL;
			head = tmp;
		}
		else						// usuwanie w œrodku, podobnie jak w dodawniu zaleznoœæ od tego który element chcemy usun¹æ
		{
			if (index > size / 2)
			{
				tmp = tail;
				for (int i = 0; i < size - index; i++)
				{
					tmp = tmp->prev;
				}
				tmp2 = tmp->prev;
				tmp = tmp->next;

				tmp->prev = tmp2;
				tmp2->next = tmp;
			}
			else
			{
				tmp = head;
				for (int i = 0; i < index - 1; i++)
				{
					tmp = tmp->next;
				}
				tmp2 = tmp->next;
				tmp = tmp->prev;
				tmp->next = tmp2;
				tmp2->prev = tmp;
			}
		}
		size--;
	}
	else
	{
		cout << "Nie mozna usunac tego indeksu.";
	}
}

void List::search_element(int value)
{
	int count = 0, i=0;
	cell *tmp = head;
	while(tmp!=NULL)						// dopóki nie natrafimy na koniec listy
	{										// iterujemy szukaj¹c elementów o wskazanej wartoœci
		if (tmp->value == value)
		{
			count++;
			if (count == 1)
			{
				cout << "Znaleziono element na pozycji: ";
			}
			cout << i + 1 << " ";
			count++;
		}
		tmp = tmp->next;
		i++;
	}
	cout << endl;
	if (count == 0)
	{
		cout << "Brak elementu w liscie." << endl;
	}
	system("pause");
}

void List::read_file()
{
	size = 0;
	fstream file;
	file.open("test.txt", ios::in);
	if (!file.good())
	{
		cout << "Nie udalo sie znalezc pliku!" << endl;
		system("pause");
	}
	else
	{
		int new_size,x;
		file >> new_size;
		for (int i = 0; i < new_size;i++)				// wczytujemy strumieniowo, a nastêpnie wywyo³ujemy funkcje dodawania dla poszczególnych elementów
		{
			file >> x;
			add_element((i+1),x);
		}
		file.close();
	}
}
void List::display_list()
{
	cout << endl;
	cell *tmp = head;
	while (tmp != NULL)
	{
		cout << tmp->value<< " ";
		tmp = tmp->next;
	}
	system("pause");
}

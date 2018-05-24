#pragma once
#include <iostream>

class List {

	struct cell {
		int value;
		cell *next, *prev;
	};
	cell *head, *tail;
	int size=0;
public:
	int get_size() { return size; }
	void set_size(int size1) { size = size1; }
	void add_element(int index, int value);
	void delete_element(int index);
	void search_element(int value);
	void read_file();
	void display_list();
};
#pragma once
#include <iostream>

using namespace std;

class Array
{
	int *array, size=0;
public:
	int get_size() { return size; }
	void set_size(int size1) { size = size1; }
	void add_element(int index, int value);
	void delete_element(int index);
	void search_element(int value);
	void read_file();
	void display_array();
};
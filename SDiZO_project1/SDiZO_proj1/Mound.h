#pragma once
#include <string>

using namespace std;
class Mound {
	int *array_m;
	int size = 0;
public:
	void insert_element(int value);
	void delete_element();
	void display_mound(string sp, string sn, int v);
	void read_file();
	void search_element(int value);
	void rebuild(int *T);
	void build( int *T, int i);
};
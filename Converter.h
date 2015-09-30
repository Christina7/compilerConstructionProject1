#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node{
	string data;
	node *next;
};


class Converter{
private:
	string alphabet;
	string init;
	string final;
	node *head;
	bool flag;

public:
	Converter();
	void insert(string x, node *&L);
	bool isEmpty();
	void print();
	void build(ifstream& file);
	node*& getHead();
};


#endif

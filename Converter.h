#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

struct node{
	string data;
	node *next;
};


class Converter{
private:


	vector<map<char, set<string>>> input;


	string total;
	vector<char> alphabet;
	set<string> initial;
	set<string> final;


	///may not need linked list stuff
	node *head;
	bool flag;

public:
	Converter();
	void insert(string x, node *&L);
	bool isEmpty();
	void print();

	set<string> findEClosure(string state, vector<map<char, set<string>>> v);
	void convertNFA2DFA();
	void build(ifstream& file);


	node*& getHead();
};


#endif

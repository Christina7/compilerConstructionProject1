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


	string total;	//total number of states
	vector<char> alphabet;	//letters used for transitions
	string initial;	 //one initial state
	set<string> final;	//multiple final states


	///may not need linked list stuff
	node *head;
	bool flag;

public:
	Converter();
	void insert(string x, node *&L);
	bool isEmpty();
	
	set<string> move(set<string> s, char c);
	void printSet(set<string> s);
	set<string> findEClosure(string state, vector<map<char, set<string>>> v);
	set<string> findEClosureHelper(string state, vector<map<char, set<string>>> v);
	void convertNFA2DFA();
	set<string> findInitial(vector<set<string>> v);
	set<string> findFinal(vector<set<string>> v);

	void build(ifstream& file);


	node*& getHead();
};


#endif

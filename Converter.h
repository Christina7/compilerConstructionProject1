/*
*				Christina Schoenrogge
*				EECS 665 Project 1
*				NFA to DFA Converter
*
*/

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


class Converter{
private:
	vector<map<char, set<string>>> input;	//where the input is completely mapped to 
	string total;	//total number of states
	vector<char> alphabet;	//letters used for transitions
	string initial;	 //one initial state
	set<string> final;	//multiple final states


public:
	Converter();
	set<string> move(set<string> s, char c);
	void printSet(set<string> s);
	set<string> findEClosure(string state, vector<map<char, set<string>>> v);
	set<string> findEClosureHelper(string state, vector<map<char, set<string>>> v);
	void convertNFA2DFA();
	set<string> findInitial(vector<set<string>> v);
	set<string> findFinal(vector<set<string>> v);
	void build(ifstream& file);
};


#endif

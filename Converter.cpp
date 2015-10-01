#include <iostream>
#include <string>
#include <ctype.h>
#include "Converter.h"
using namespace std;

Converter::Converter(){
	total = "";
	head = NULL;
	flag = false;
}

//adds state to end of list
void Converter::insert(string x, node *&L){
	if (L == NULL){	//if current node is NULL adds new node with data
		L = new node;
		L->data = x;
		L->next = NULL;
	} else if (L->next == NULL){
		L->next = new node;
		L->next->next = NULL;
		L->next->data = x;
	} else {	// current node is not last node then move on to next node recursively
		insert(x, L->next);
	}
		
	
}

//checks if Converter is empty
bool Converter::isEmpty(){
	if (head == NULL){
		return true;
	}
	else{
		return false;
	}
}


//prints current Converter
void Converter::print(){
	node *temp = head;	//new node pointing to head
	if (temp == NULL){
		cout << "Empty List \n";
	}
	else{
		while (temp->next != NULL){		//while next node isn't null print data
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << temp->data << endl;	//print last node
	}
}

//finds eclosure of given state		NOTE: state is the state wanted 
set<string> Converter::findEClosure(string state, vector<map<char, set<string>>> v){
	set<string> eclosure;
	eclosure.insert(state);
	eclosure.insert(v[stoi(state) - 1].find('E')->second.begin(), v[stoi(state) - 1].find('E')->second.end());
	return eclosure;
}

void Converter::convertNFA2DFA(){
	//just use this-> whatever
	vector<set<string>> marks;

	cout << "E-closure(I0) = {";// findEClosure(initial)
	
}


//builds/fills in initial Converter class
void Converter::build(ifstream& file){
	string item; //string line
	string states; //holding alphanumeric
	set<string> numStates;	//states to go to map value
	map<char, set<string>> inputValue;	//maps alphabet to states
	int length;
	int a;
	int track = 0;

	while (getline(file, item)){
		length = item.length();
		if (item.at(0) == 'I'){	//initial states line
			for (int i = 0; i < length; i++){	//loop through to find states to build string for initial
				if (isdigit(item.at(i))){
					a = i;
					break;
				}
			}

			while (a < length){ //loop through all the states an add to initial set
				switch (item.at(a)){
				case ',':
					initial.insert(states); 
					states = "";
					break;
				case '}':
					initial.insert(states);
					states = "";
					break;
				default:
					states += item.at(a);
					break;
				}
				a++;
			}
		
			
			states = "";
			cout << "built initial states \n";
		}
		else if (item.at(0) == 'F'){
			for (int i = 0; i < length; i++){	//loop through to find states to build string for initial
				if (isdigit(item.at(i))){
					a = i;
					break;
				}
			}

			while (a < length){ //loop through all the states an add to initial set
				switch (item.at(a)){
				case ',':
					initial.insert(states);
					states = "";
					break;
				case '}':
					final.insert(states);
					states = "";
					break;
				default:
					states += item.at(a);
					break;
				}
				a++;
			}
			states = "";
			cout << "built final states \n";
		}
		else if (item.at(0) == 'T'){
			for (int i = 0; i < length; i++){	//loop through to find states to build string for total
				if (isdigit(item.at(i))){
					a = i;
					break;
				}
			}

			while ((a < length) && (isdigit(item.at(a)))){ //loop through to find total
						
						states += item.at(a);
					
						a++;
					}
					total = states;
					states = "";
				
			
			cout << "built total states \n";
		}
		else if (item.at(0) == 'S'){
			int i = 0;
			//int j = 0;
			while (isalpha(item.at(i))){	//loop through to find 'State' to get to alphabet
				i++;
			}
			for (i; i < length; i++){
				if (isalpha(item.at(i))){
					alphabet.push_back(item.at(i));
				}
			}
			cout << "built alphabet \n";
		}
		else{
			int i = 0;
			string current = "";
			while (isdigit(item.at(i))){
				states += item.at(i);
				i++;
			}
			
			for (int k = 0; k < int(alphabet.size()); k++){
				while (i < length){	
					if (isdigit(item.at(i))){
						current += item.at(i);
					}
					else if (item.at(i) == ',') {
						numStates.insert(current);
						current = "";
					}
					else if (item.at(i) == '}'){
						//if ((track == k) && (current != "")){
						if (current != ""){
							numStates.insert(current);
							current = "";
						}
						//track++;
						i++;
						break;
					}
					else{
					}
					i++;
				}
				if (!numStates.empty()){
					inputValue.insert(pair<char, set<string>>(alphabet[k], numStates));
					
				}
				//inputValue.clear();
				numStates.clear();
			}
			input.push_back(inputValue);
			inputValue.clear();

		}
	}

	cout << "built all\n";
}

node*& Converter::getHead(){
	return head;
}

#include <iostream>
#include <string>
#include <ctype.h>
#include "Converter.h"
using namespace std;

Converter::Converter(){
	total = "";
	alphabet = "";
	initial = "";
	final = "";
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



//builds initial Converter 
void Converter::build(ifstream& file){
	string item;
	string states;
	set<string> numStates;
	map<char, set<string>> inputValue;

	int a;
	while (getline(file, item)){
		if (item.at(0) == 'I'){	//initial states line
			for (int i = 0; i < item.length(); i++){	//loop through to find states to build string for initial
				if (isdigit(item.at(i))){
					states += item.at(i);
					a = i + 1;
					while ((item.at(a) != '}') && (a < item.length)){ //loop through all the states an add to initial set
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
				}
			}
			states = "";
		}
		else if (item.at(0) == 'F'){
			for (int i = 0; i < item.length(); i++){	//loop through to find states to build string for initial
				if (isdigit(item.at(i))){
					states += item.at(i);
					a = i + 1;
					while ((item.at(a) != '}') && (a < item.length)){ //loop through all the states an add them to set
						switch (item.at(a)){
						case ',':
							final.insert(states);
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
				}
			}
			states = "";
		}
		else if (item.at(0) == 'T'){
			for (int i = 0; i < item.length(); i++){	//loop through to find states to build string for total
				if (isdigit(item.at(i))){
					states += item.at(i);
					a = i + 1;
					while ((item.at(a) != '}') && (a < item.length)){ //loop through to find total
						switch (item.at(a)){
						case '}':
							break;
						default:
							states += item.at(a);
							break;
						}
						a++;
					}
					total = states;
					states = "";
				}
			}
		}
		else if (item.at(0) == 'S'){
			int i = 0;
			int j = 0;
			while (isalpha(item.at(i))){	//loop through to find 'State' to get to alphabet
				i++;
			}
			for (i; i < item.length(); i++){
				if (isalpha(item.at(i))){
					alphabet[j] = (item.at(i));
					j++;
				}
			}
		}
		else{
			int i = 1;
			states += item.at(0);
			while (isdigit(item.at(i))){
				states += item.at(i);
			}
			for (i; i < item.length; i++){
				if 
			}
			

			input[stoi(states)] = NULL;
		}
	}
}

node*& Converter::getHead(){
	return head;
}

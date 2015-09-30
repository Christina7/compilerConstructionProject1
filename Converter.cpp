#include <iostream>
#include <string>
#include <ctype.h>
#include "Converter.h"
using namespace std;

Converter::Converter(){
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
	while (getline(file, item)){//read from file and add each number to head
		if (item.at(0) == 'I'){
			for (int i = 0; i < item.length(); i++){
				if (isdigit(item.at(i))){
					states = 'a';
				}
			}
			initial = item;
		}
		
		
		
		
		insert(item, head);
	}
}

node*& Converter::getHead(){
	return head;
}

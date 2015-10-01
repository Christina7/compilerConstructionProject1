/*
*				Christina Schoenrogge
*				EECS 665 Project 1
*				NFA to DFA Converter
*
*/

#include <iostream>
#include <string>
#include <ctype.h>
#include "Converter.h"
using namespace std;

Converter::Converter(){
	total = "";
	initial = "";
}


set<string> Converter::move(set<string> s, char c){
	set<string> state;
	set<string> returnState;

	for (set<string>::iterator it = s.begin(); it != s.end(); ++it){//for each state given
		if (input[stoi(*it) - 1].count(c) != 0){	//see if it's in the map add the states it transitions to given c
			state.insert(input[stoi(*it) - 1].at(c).begin(), input[stoi(*it) - 1].at(c).end());  //vector[map<char, set<string>>] input;
			if (state != returnState){	//add it if 
				returnState.insert(state.begin(), state.end());
				
			}
			state.clear();
		}
	}
	return returnState;
}

//prints current Converter
void Converter::printSet(set<string> s){
	for (set<string>::iterator it = s.begin(); it != s.end(); ++it){
		cout << *it << " ";
	}
}

//finds eclosure of given state		NOTE: state is the state wanted 
set<string> Converter::findEClosure(string state, vector<map<char, set<string>>> v){
	set<string> eclosure1;
	set<string> eclosure2;
	set<string> getRest;
	
	eclosure1.insert(state);
	if (v[stoi(state) - 1].count('E') != 0){
		eclosure1.insert(v[stoi(state) - 1].at('E').begin(), v[stoi(state) - 1].at('E').end());
	}
	while (eclosure1 != eclosure2){
		eclosure2 = eclosure1;

		for (set<string>::iterator it = eclosure1.begin(); it != eclosure1.end(); ++it){
			getRest = findEClosureHelper(*it,input);
			eclosure1.insert(getRest.begin(), getRest.end());
		}

	}

	return eclosure1;
}

set<string> Converter::findEClosureHelper(string state, vector<map<char, set<string>>> v){
	set<string> eclosure;
	eclosure.insert(state);
	if (v[stoi(state) - 1].count('E') != 0){
		eclosure.insert(v[stoi(state) - 1].at('E').begin(), v[stoi(state) - 1].at('E').end());
	}
	return eclosure;
}

void Converter::convertNFA2DFA(){
	vector<set<string>> markList; // marks and the set they hold
	vector<map<char, string>> markTransitions;
	map<char, string> statemap;
	set<string>  mark;
	set<string>  Emark;
	set<string> temp;
	int counter = 1;
	int whichMark = 1;
	bool isInList = false;

	string stateName = "";

	mark = findEClosure(initial, input);
	markList.push_back(mark);

	cout << "E-closure(I0) = {";
	printSet(mark);
	cout << "} = 1 \n";// findEClosure(initial)

	mark.clear();

	do{
		// find all the marks 


		cout << "\nMark " << whichMark << "\n";


		for (int i = 0; i < int(alphabet.size() - 1) ; i++){


			mark = move(markList[whichMark - 1], alphabet[i]); //find the set that a transitions to
			if (!mark.empty()){

				cout << "{";
				printSet(markList[whichMark - 1]);
				cout << "} --" << alphabet[i] << "--> {";
				printSet(mark);
				cout << "}\n";
				for (set<string>::iterator it = mark.begin(); it != mark.end(); ++it){ // for each entry in that set
					temp = findEClosure(*it, input);								  // find the eclosure 
					Emark.insert(temp.begin(), temp.end());
					temp.clear();

				}

				cout << "E-closure{";
				printSet(mark);
				cout << "} = {";
				printSet(Emark);
				cout << "} = ";


				for (int j = 0; j < int(markList.size()); j++){	//see if its in the list
					if (Emark == markList[j]){
						isInList = true;
						stateName = j + 1;
						break;
					}
				}
				if (!isInList){	//if not in list add it, increment counter
					markList.push_back(Emark);
					Emark.clear();
					counter++;
					stateName = to_string(counter);
				}

				cout << stateName << endl;

				statemap.insert(pair<char, string>(alphabet[i], stateName));
			}
		}
		//add to final
		markTransitions.push_back(statemap);
		statemap.clear();
		whichMark++;
		cout << endl << endl;

	} while (whichMark != counter);


	cout << "Initial State: {";
	printSet(findInitial(markList));
	cout << "} \nFinal States: {";
	printSet(findFinal(markList));
	cout << "} \nState\t";
	for (int g = 0; g < int(alphabet.size() - 1); g++){
		cout << alphabet[g] << "\t";
	}
	cout << endl;

	for (int b = 0; b < int(markTransitions.size() - 1); b++){
		cout << b + 1;
		for (int h = 0; h < int(alphabet.size() - 1); h++){
			cout << "\t{";
			if (markTransitions[b].count(alphabet[h]) != 0){
				cout << markTransitions[b].at(alphabet[h]) << "}\t";
			}
			else{
				cout << "}\t";
			}
		}
		cout << endl;
	}
}

set<string> Converter::findInitial(vector<set<string>> v){
	set<string> returnSet;
	for (int i = 0; i < int(v.size()); i++){
		if (v[i].find(initial) != v[i].end()){
			returnSet.insert(to_string(i+1));
		}
	}

	return returnSet;
}

set<string> Converter::findFinal(vector<set<string>> v){
	set<string> returnSet;

	for (int i = 0; i < int(v.size()); i++){
		for (set<string>::iterator itA = v[i].begin(); itA != v[i].end(); ++itA){
			for (set<string>::iterator itB = final.begin(); itB != final.end(); ++itB){
				if (*itA == *itB){
					returnSet.insert(to_string(i + 1));
				}
			}
		}
	}


	return returnSet;
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
					initial = states; 
					states = "";
					break;
				case '}':
					initial = states;
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
						if (current != ""){
							numStates.insert(current);
							current = "";
						}
						
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

	cout << "built all\n\n\n\n";
}


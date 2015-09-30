#include <iostream>
#include "Converter.h"
using namespace std;

int main(){

	Converter a;

	ifstream file;
	file.open("input.txt");

	a.build(file);

	cout << "stop";

	return 0;

}
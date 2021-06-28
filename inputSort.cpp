#include<stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int main() {
	char name[99];
	char in[10] = {'u','s','e','r','I','n','.','t','x','t'};
	char fileRead[99];
	string typeOfInput;
	string quitIn;
	bool done = false;
	printf(
			"\nEnter 'i' to input custom proccesses -- or -- press any other key to continue to stress file input");
	cin >> typeOfInput;

	if (typeOfInput == "i") {
		// Create and open a text file
		ofstream MyFile("userIn.txt");
		strcpy (name,in);
		//name = "userIn.txt";
		int pidCount = 0;
		int burstIn;
		int arrIn;
		MyFile << "Pid";
		MyFile << "\t";
		MyFile << "Bst";
		MyFile << "\t";
		MyFile << "Arr";
		MyFile << "\n";
		while (!done) {
			burstIn = 0;
			arrIn = 0;

			pidCount++;
			MyFile << pidCount;
			MyFile << "\t";

			printf("\nEnter burst for process %d ", pidCount);
			cin >> burstIn;
			MyFile << burstIn;
			MyFile << "\t";

			// user input

			printf("Enter arrival for process %d", pidCount);
			cin >> arrIn;
			MyFile << arrIn;
			MyFile << "\n";

			printf("Enter 'q' to quit, or any other key to continue\n\n");
			cin >> quitIn;

			if (quitIn == "q") {
				done = true;
			}
		}

	} else {

		printf("\nEnter the test file name:\t");
		scanf("%s", name);

	}

	sprintf(fileRead, "sort -g -k 3,3 -o %s %s", name, name);

	system(fileRead); // execute the UNIX command "sort"
	//string line;
	//ifstream myfile("%s",name);
}

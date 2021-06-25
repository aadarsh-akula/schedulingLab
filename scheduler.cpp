/*
/ CS 452 
Scheduler Lab Assignment
Zach Terry & Aadarsh Akula
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    cout << "Running MFQS ....." << "\n\n";

    int processCount = 0;
    string line; 

    ifstream file("500k"); // Open process file
    ofstream newFile("copy.txt"); // Open file to copy valid processes to

    // Loop through file and copy over sanitized values
    while (getline (file, line)) {

        if (line.find('-') == string::npos) {

            int i = 0; // loop counter
            int spaceCount = 0; // num of spaces, used to cut out unnecessary values

            // Get the first 3 values to copy over
            while (spaceCount < 3) {

                if (isspace(line[i])) // if current char is a space, increment space count and copy over
                {
                    spaceCount++;
                    newFile << line[i]; 
                }  else { // otherwise just copy the char over
                    newFile << line[i];
                }
                
                i++;

            }   

        newFile << "\n";

        processCount++;

        }

    }

    cout << "# of valid processes: " << processCount; //test
    
    // close files
    file.close();
    newFile.close();

    int numQueues;
    int timeQuantum;
    int ageInterval;
    
    cout << "\n Enter number of queues: ";
    cin >> numQueues;

    cout << "Enter time quantum for top queue: ";
    cin >> timeQuantum;

    cout << "Enter aging interval: ";
    cin >> ageInterval;

    return 0;

}
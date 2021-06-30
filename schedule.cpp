/*
CS 452 
Scheduler Lab Assignment
Zach Terry & Aadarsh Akula
*/

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// create Process structure
struct Process {

    int arrival;
    int pid;
    int burst;
    int priority;
    int remaining;
    int turnTime;
    int waitTime;

    //create process constructor
    Process(int arr, int bur, int id, int pri, int rem) {
        arrival = arr;
        burst = bur;
        pid = id;
        priority = pri;
        remaining = rem;
    }

    Process() {};

    //operator for sorting by arrival time
    bool operator < (const Process& proc) const {
        return (arrival < proc.arrival);
    }
};

//
int checkUnder(vector<Process> queue, int a, int time) {
    cout << "Process " << queue[a].pid << ": runs at time: " << time << "\n";

                while (queue[a].remaining != 0) {

                    time++;
                    if (queue[a].arrival == time) {

                        cout << "Process " << queue[a].pid << ": arrives at time: " << time << "\n";
                    
                    }
                    queue[a].remaining--;
                }

                cout << "Process " << queue[a].pid << ": finishes at time: " << time << "\n";

    return time;                      
}

//
int checkOver(vector<Process> queue, int a, int time, int quantum) {
    cout << "Process " << queue[a].pid << ": runs at time: " << time << "\n";

            int check = quantum;

            while (check != 0) {
                time++;

                if (queue[a].arrival == time) {

                    cout << "Process " << queue[a].pid << ": arrives at time: " << time << "\n";
                
                }
                check--;
            }
    return time;
}

int main() {

    /*
    Selecting & Filtering
    */
    string name;
    string line;

    //select what processes to use
    string input;
    cout << "Enter 'i' for custom processes, or enter any other key to use a file: ";
    cin >> input;

    int processCount = 0;

    //create copy file to sort processes in
    ofstream customFile("copy.txt");

    //if user chooses to enter custom processes
    if (input == "i") {

        int burstInput;
        int arrivalInput;
        int priorityInput;

        //ask user for # of processes
        cout << "Enter # of processes: ";
        cin >> processCount;

        customFile << 0 << "\t" << 0 << "\t" << 0 << "\t" << 0;

        for(int i = 1; i <= processCount; i++) {
            
            //add process id to file
            customFile << i;
            customFile << "\t";
            //ask user for burst and add to file
            cout << "Enter burst for process #" << i << ": ";
            cin >> burstInput;
            customFile << burstInput;
            customFile << "\t";
            //ask user for arrival and add to file
            cout << "Enter arrival for process #" << i << ": ";
            cin >> arrivalInput;
            customFile << arrivalInput;
            customFile << "\t";
            //ask user for priority and add to file
            cout << "Enter priority for process #" << i << ": ";
            cin >> priorityInput;
            customFile << priorityInput;
            customFile << "\n";
        }

    } else {

        cout << "Enter file name: ";
        cin >> name;

        ifstream file(name); // Open process file

        // Loop through file and copy over sanitized values
        while (getline (file, line)) {

            if (line.find('-') == string::npos) {

                int i = 0; // loop counter
                int spaceCount = 0; // num of spaces, used to cut out unnecessary values

                // Get the first 4 values to copy over
                while (spaceCount < 4) {
                        
                    if (isspace(line[i])) {// if current char is a space, increment space count and copy over
                        spaceCount++;
                        customFile << " "; 
                    }  else { // otherwise just copy the char over
                        customFile << line[i];
                    }
                    
                    i++;
                }  

                customFile << "\n"; 
                processCount++;
            }
        }

        processCount--;
        file.close();
    }

    customFile.close();

    /*
    Sorting 
    */

    //create vector of processes
    vector<Process> processList;
    
    ifstream newFile("copy.txt");
    string newLine;

    int count = 0;
    int pid, burst, arrival, priority, remaining;

    //loops through all lines of new process file
    while (getline (newFile, newLine)) {
        
        // use stringstream to seperate values
        stringstream ss(newLine);
        string value;

        // while there is a value, check to see which value it is using mod and add to correct variable
        while (ss >> value) {
            if (isdigit(value[0])) {
                //cout << value << "\n";
                
                if (count % 4 == 0)
                {
                    pid = stoi(value);
                } else if (count % 4 == 1)
                {
                    burst = stoi(value);
                    remaining = stoi(value);
                } else if (count % 4 == 2)
                {
                    arrival = stoi(value);
                } else if (count % 4 == 3) 
                {
                    priority = stoi(value);
                } else {
                    cout << "uh oh";
                }
            }

            count++;
        }
        // add values into the process vector
         processList.emplace_back(Process(arrival, burst, pid, priority, remaining));   

    }
    
    // sort process list
    sort(processList.begin(), processList.end());

    newFile.close();

    /*
    Scheduling
    */

    //user input
    cout << "Running MFQS ....." << "\n\n";
    int numQueues;
    int timeQuantum;
    int ageInterval;
    cout <<"Enter number of queues(2-5): \n";
    cin >> numQueues;
    cout << "Enter time quantum for top queue: \n";
    cin >> timeQuantum;
    cout << "Enter aging interval: \n";
    cin >> ageInterval;

    int time = processList[1].arrival;
    
    //counters for each queue
    int i, j, k, m, n = 1;

    // flag determines if going to next queue
    bool flag1, flag2, flag3, flag4, flagLast = false;

    int totalTurn = 0;
    int totalWait = 0;

    // process count for each queue
    int processCount2, processCount3, processCount4, processCount5 = 0;
    int check = timeQuantum;

    //create extra queues
    vector<Process> queue2, queue3, queue4, queueLast;

    /*first queue*/
    cout << "first queue\n";
    while (i <= processCount) {

        // cout << "time: " << time << "\n";
        // cout << "quantum: " << timeQuantum << "\n:";
        // cout << "arrival" << processList[i].arrival << "\n";
        // cout << "i: " << i << "\n";

        //print new arrivals
        if (processList[i].arrival == time)
        {
            cout << "Process " << processList[i].pid << ": arrives at time: " << time << "\n";
        }
        
        //run queue if available and check for completeion
        if (processList[i].remaining <= timeQuantum && processList[i].arrival <= time) {

            time = checkUnder(processList, i, time);
            i++;

        //run queue if available and check to send to next queue
        } else if (processList[i].remaining > timeQuantum && processList[i].arrival <= time){

            time = checkOver(processList, i, time, timeQuantum);
                        
            processList[i].remaining -= timeQuantum;

            if (numQueues == 2){
                cout << "Process " << processList[i].pid << ": switched to last queue at time: " << time << "\n";
                queueLast.emplace_back(processList[i]);
                processCount5++;
                flagLast = true;

            } else {
                cout << "Process " << processList[i].pid << ": switched to queue 2 at time: " << time << "\n";
                queue2.emplace_back(processList[i]);
                processCount2++;
                flag2 = true;
            }

            i++;
                
        } else {
            //cout << "dead end in queue 1 \n";
            time++;
        }
    }


    /*second queue*/
    cout << "second queue\n";
    for (int i = 0; i < queue2.size(); i++) {
        cout << queue2[i].pid << "\t";
    }
    if (flag2) {
        while (j < processCount2) {

            if (queue2[j].remaining <= (timeQuantum*2) && queue2[j].arrival <= time) {

                time = checkUnder(queue2, j, time);
                j++;

            } else if (queue2[j].remaining >= (timeQuantum*2) && queue2[j].arrival <= time) {

                time = checkOver(queue2, j, time, timeQuantum*2);

                queue2[j].remaining -= timeQuantum*2;
                

                if (numQueues == 3){
                    cout << "Process " << queue2[j].pid << ": switched to last queue at time: " << time << "\n";
                    queueLast.emplace_back(queue2[j]);
                    processCount5++;
                    flagLast = true;

                } else {
                    cout << "Process " << queue2[j].pid << ": switched to queue 3 at time: " << time << "\n";
                    queue3.emplace_back(queue2[j]);
                    processCount3++;
                    flag3 = true;
                }
                j++;

            } else  {
                time++;
            }
            
        }
    }

    /*third queue*/
    for (int i = 0; i < queue3.size(); i++) {
        cout << queue3[i].pid << "\t";
    }
    cout << "third queue\n";
    if (flag3) {
        while (k < processCount3) {

            if (queue3[k].remaining <= (timeQuantum*4) && queue3[k].arrival <= time) {

                time = checkUnder(queue3, k, time);
                k++;

            } else if (queue3[k].remaining >= (timeQuantum*4) && queue3[k].arrival <= time) {

                time = checkOver(queue3, k, time, timeQuantum*4);
                queue3[k].remaining -= timeQuantum*4;

                if (numQueues == 4){
                    cout << "Process " << queue3[k].pid << ": switched to last queue at time: " << time << "\n";
                    queueLast.emplace_back(queue3[k]);
                    processCount5++;
                    flagLast = true;

                } else {
                    cout << "Process " << queue3[k].pid << ": switched to queue 4 at time: " << time << "\n";
                    queue4.emplace_back(queue3[k]);
                    processCount4++;
                    flag4 = true;
                }
                k++;

            } else  {
                time++;
            }
            
        }
    }    

    /*fourth queue*/
    cout << "fourth queue\n";
    for (int i = 0; i < queue4.size(); i++) {
        cout << queue4[i].pid << "\t";
    }
    cout << "\n";
    if (flag4) {
        while (m < processCount4) {

            if (queue4[m].remaining <= (timeQuantum*8) && queue4[m].arrival <= time) {

                time = checkUnder(queue4, m, time);
                m++;

            } else if (queue4[m].remaining >= (timeQuantum*8) && queue4[m].arrival <= time) {

                time = checkOver(queue4, m, time, timeQuantum*8);
                queue4[m].remaining -= timeQuantum*8;

                cout << "Process " << queue4[m].pid << ": switched to last queue at time: " << time << "\n";
                queueLast.emplace_back(queue4[m]);
                flagLast = true;
                processCount5++;

                m++;

            } else  {
                time++;
            }
            
        }
    }    

    /*last queue*/
    cout << "last queue\n";
    for (int i = 0; i < queueLast.size(); i++) {
        cout << queueLast[i].pid << "\t";
    }
    if (flagLast) {
        while (n < processCount5) {

            cout << "Process " << queueLast[n].pid << ": runs in last queue at time: " << time << "\n";

            while (queueLast[n].remaining != 0) {

                time++;
                queueLast[n].remaining--;
            }

            cout << "Process " << queueLast[n].pid << ": finishes at time: " << time << "\n";

            n++;
            
        }
    }    

    return 0;

}
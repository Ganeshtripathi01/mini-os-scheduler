Mini OS Scheduler Simulator
A fully functional CPU scheduling simulator implementing FCFS, SJF, Priority, and Round Robin algorithms in C++.
Includes Gantt chart generation, waiting time, turnaround, and response time calculations.
🚀 Features
Implements four major OS scheduling algorithms
Generates Gantt charts for each run
Computes:
Waiting Time
Turnaround Time
Response Time
Clean OOP design with PCB (Process Control Block)
Uses STL containers (deque, priority_queue, vector)
Modular, extensible, interview-ready
📂 Project Structure
mini-os-scheduler/
│── main.cpp             # Scheduler implementation
│── run.sh               # Demo script to run all algorithms
│── example_input.txt    # Test input
│── README.md            # Project documentation
🧠 Supported Algorithms
Algorithm	Type	Description
FCFS	Non-preemptive	Processes handled in arrival order
SJF	Non-preemptive	Shortest burst job first
Priority	Non-preemptive	Lower priority number → higher priority
Round Robin	Preemptive	Uses configurable quantum
📌 How to Build & Run
Run all algorithms
./run.sh
Run manually
g++ -std=c++17 main.cpp -O2 -o scheduler
./scheduler --algo fcfs < example_input.txt
📝 Sample Input
4
1 0 5
2 1 3
3 2 8
4 3 6
📊 Sample Output (FCFS)
Gantt:
P1[0-5] P2[5-8] P3[8-16] P4[16-22]

P1: start=0 completion=5 waiting=0 turnaround=5 response=0  
P2: start=5 completion=8 waiting=4 turnaround=7 response=4  
P3: start=8 completion=16 waiting=6 turnaround=14 response=6  
P4: start=16 completion=22 waiting=13 turnaround=19 response=13
📐 ASCII Gantt Diagram
| P1 | P2 |    P3    |   P4   |
0    5    8          16       22
🧩 Internal Design
Process Control Block (PCB)
id
arrival_time
burst_time
priority
remaining_time
start_time
completion_time
Data Structures
deque → FCFS, RR
priority_queue → SJF, Priority
vector → store all processes
Timeline vector → generate Gantt chart
📈 Time Complexity
Algorithm	Complexity
FCFS	O(N)
SJF	O(N log N)
Priority	O(N log N)
Round Robin	O(N × slices)
🧭 Future Improvements
Add preemptive SJF
Add priority aging
Add GUI visualization
Export Gantt chart as an image

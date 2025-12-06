# Mini OS Scheduler Simulator

A fully functional **CPU scheduling simulator** implementing **FCFS, SJF, Priority, and Round Robin** algorithms in C++.  
Includes Gantt chart generation and calculation of waiting time, turnaround time, and response time.

---

## 🚀 Features

- Implements **four major OS scheduling algorithms** (FCFS, SJF, Priority, Round Robin)  
- Generates **Gantt charts** for each algorithm run  
- Computes per-process: **waiting time**, **turnaround time**, **response time**  
- Clean **OOP design** with a Process Control Block (PCB) structure  
- Uses STL containers: `vector`, `deque`, `priority_queue`  
- Modular and easy to extend — interview-ready

---

## 📂 Project Structure

mini-os-scheduler/
├── main.cpp # Scheduler implementation (C++)
├── run.sh # Demo script
├── example_input.txt # Example input for tests
└── README.md # This file

---

## 🧠 Supported Algorithms
| Algorithm | Type | Description |
|----------|------|-------------|
| **FCFS** | Non-preemptive | First-come, first-served |
| **SJF** | Non-preemptive | Selects smallest burst |
| **Priority** | Non-preemptive | Lower number = higher priority |
| **Round Robin** | Preemptive | Quantum-based scheduling |

---

## 🧪 How to Build & Run

### Build
```bash
g++ -std=c++17 main.cpp -O2 -o scheduler

Run all algorithms
./run.sh

Run single algorithm
./scheduler --algo fcfs < example_input.txt
./scheduler --algo rr --quantum 2 < example_input.txt

📥 Example Input

4
1 0 5
2 1 3
3 2 8
4 3 6

---

📊 Sample Output (FCFS)

Gantt:
P1[0-5] P2[5-8] P3[8-16] P4[16-22]

P1: start=0 completion=5 waiting=0 turnaround=5 response=0
P2: start=5 completion=8 waiting=4 turnaround=7 response=4
P3: start=8 completion=16 waiting=6 turnaround=14 response=6
P4: start=16 completion=22 waiting=13 turnaround=19 response=13

Avg waiting=5.75 avg turnaround=11.25 avg response=5.75

---

📐 ASCII Gantt Diagram

| P1 | P2 |    P3    |   P4   |
0    5    8         16       22


---

🧩 Internal Design

PCB Structure:

-id
-arrival_time
-burst_time
-priority
-remaining_time
-start_time
-completion_time

Data Structures:

-deque → FCFS, RR
-priority_queue → SJF, Priority
-vector → master list
-vector<tuple> → Gantt timeline

---

📈 Time Complexity

| Algorithm   | Complexity              |
| ----------- | ----------------------- |
| FCFS        | O(N)                    |
| SJF         | O(N log N)              |
| Priority    | O(N log N)              |
| Round Robin | O(N × number_of_slices) |

---

🔮 Future Improvements
-Add preemptive SJF (SRTF)
-Add priority aging
-GUI visualization
-Export Gantt as image

---

📄 License

MIT License (recommended)

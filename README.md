# Mini OS Scheduler Simulator

A C++ simulator implementing four fundamental CPU scheduling algorithms used in operating systems:

- **FCFS (First Come First Serve)**
- **SJF (Shortest Job First)**
- **Priority Scheduling**
- **Round Robin (RR)**

The simulator generates a **Gantt chart** and computes key performance metrics including:

- Waiting Time  
- Turnaround Time  
- Response Time  

This project demonstrates how real OS schedulers manage ready queues, select the next process, and measure scheduling efficiency.

---

## 🚀 Features

- Supports both **non-preemptive** (FCFS, SJF, Priority) and **time-sliced** algorithms (RR)
- Uses optimized data structures:
  - `deque<int>` for FCFS & Round Robin  
  - `priority_queue<int, vector<int>, Comparator>` for SJF & Priority  
- Stores processes in a vector sorted by arrival time for O(1) arrival handling  
- Logs execution intervals as `(pid, start, end)` to produce Gantt charts  
- Computes waiting, turnaround, and response times per process and averages

---

## 📁 Project Structure

```
mini-os-scheduler/
    ├── main.cpp          # Scheduler demo (replace with full implementation later)
    ├── example_input.txt # Sample process list
    ├── run.sh            # Build + run script
    └── README.md         # Documentation
```

---

## 🛠️ How to Run

```bash
git clone https://github.com/Ganeshtripathi01/mini-os-scheduler
cd mini-os-scheduler
./run.sh
```

---

## 📊 Example Output (Gantt Chart)

```
Gantt:
P1[0-5] P2[5-8] P4[8-14] P3[14-22]

P1: start=0 completion=5 waiting=0 turnaround=5 response=0
P2: start=5 completion=8 waiting=4 turnaround=7 response=4
P3: start=14 completion=22 waiting=12 turnaround=20 response=12
P4: start=8 completion=14 waiting=5 turnaround=11 response=5

Avg waiting=5.25, Avg turnaround=11.0, Avg response=5.25
```

---

## 🧠 Internal Design

### **Process Storage**
All processes are stored in:

```cpp
vector<Process> all;  // sorted by arrival time
```

This allows arrival handling in **O(1)** using:

```cpp
size_t next_arrival_idx = 0;
```

---

### **Ready Queue Data Structures**

| Algorithm     | Data Structure | Why                                                                 |
|---------------|----------------|---------------------------------------------------------------------|
| FCFS          | deque<int>     | FIFO behavior, O(1) push/pop                                        |
| Round Robin   | deque<int>     | Easy rotation after time quantum                                    |
| SJF / Priority | priority_queue<int, vector<int>, Comparator> | Efficient O(log n) selection of smallest burst or highest priority |

Using integer **indices** instead of Process objects avoids copying and allows updating `all[idx].remaining` directly.

---

## 🎤 Interview Notes (Quick Reference)

### **30-second explanation**
“I built a C++ CPU scheduling simulator that runs FCFS, SJF, Priority, and Round Robin. It uses efficient data structures like deque and priority_queue, generates a Gantt chart, and computes waiting, turnaround, and response times.”

### **90-second explanation**
“This project simulates how operating systems schedule processes. I load processes with arrival time, burst time, and priority, sort them by arrival, and track time as a simulation clock.

For FCFS and RR, I use a deque because they need FIFO behavior. For SJF and Priority, I use a priority_queue with a custom comparator so I can always pick the next shortest burst or highest priority efficiently.

During simulation, I record `(pid, start, end)` time slices to build the Gantt chart. After all processes finish, I compute waiting, turnaround, and response times. The project helped me understand scheduler design, preemption, time slicing, and OS-level process management.”

---

## ❓ Common Interview Questions & Answers

### **1. Why use `priority_queue` for SJF and Priority?**
Because selecting the smallest remaining burst or highest priority should be efficient.  
`priority_queue` gives **O(log n)** insert/remove operations.

### **2. Why store indices instead of Process objects?**
To avoid copying process structs and update remaining time in-place using:
```cpp
all[idx].remaining--;
```

### **3. How do you handle new arrivals?**
Processes are pre-sorted by arrival time.  
I maintain `next_arrival_idx` and push arrivals into the ready queue whenever:
```
arrival_time <= current_time
```

### **4. How is Round Robin implemented?**
Run each process for:
```
min(time_quantum, remaining_time)
```
Then push it back to the queue if it's not finished.

### **5. How to prevent starvation in Priority Scheduling?**
Use **aging** — increase priority of long-waiting processes.

### **6. What is the algorithm complexity?**
- Sorting processes: **O(N log N)**
- Per-queue operation: **O(1)** (deque) or **O(log N)** (priority_queue)
- Total: **O(N log N + S log N)**, where S = scheduling events

---

## 📌 Future Improvements

- Add preemptive SJF (Shortest Remaining Time First)  
- Add context-switch overhead  
- Add graphical Gantt chart visualization  
- Add test cases with automated output comparison  

---

## 📎 License
This project is released under the **MIT License**.


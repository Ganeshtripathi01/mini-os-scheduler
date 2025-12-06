#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <tuple>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    long long arrival;
    long long burst;
    long long remaining;
    int priority;
    long long start = -1;
    long long completion = -1;
};

using TTimeline = vector<tuple<int,long long,long long>>;

void print_metrics(const vector<Process>& all, const TTimeline &timeline){
    int N = (int)all.size();
    cout << "Gantt:\n";
    for(auto &t: timeline){
        cout << "P" << get<0>(t) << "[" << get<1>(t) << "-" << get<2>(t) << "] ";
    }
    cout << "\n\n";
    double sum_w=0, sum_t=0, sum_r=0;
    for(auto &p: all){
        long long turnaround = p.completion - p.arrival;
        long long waiting = turnaround - p.burst;
        long long response = p.start - p.arrival;
        cout << "P" << p.id << ": start=" << p.start << " completion=" << p.completion
             << " waiting=" << waiting << " turnaround=" << turnaround << " response=" << response << "\n";
        sum_w += waiting; sum_t += turnaround; sum_r += response;
    }
    cout << "\nAvg waiting=" << (sum_w/N) << " avg turnaround=" << (sum_t/N) << " avg response=" << (sum_r/N) << "\n";
}

void push_slice(TTimeline &timeline, int pid, long long s, long long e){
    if(s>=e) return;
    if(!timeline.empty()){
        auto &last = timeline.back();
        if(get<0>(last)==pid && get<2>(last)==s){
            get<2>(last)=e;
            return;
        }
    }
    timeline.emplace_back(pid,s,e);
}

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Defaults
    string algo = "fcfs";
    long long quantum = 2;

    // Simple CLI parsing
    for(int i=1;i<argc;i++){
        string a = argv[i];
        if(a=="--algo" && i+1<argc) { algo = argv[++i]; }
        else if((a=="-q" || a=="--quantum") && i+1<argc) { quantum = stoll(argv[++i]); }
        else if(a=="--help"){ cout << "Usage: ./scheduler --algo [fcfs|sjf|priority|rr] --quantum 2\n"; return 0; }
    }

    // Read input: N then lines: id arrival burst [priority]
    int N;
    if(!(cin>>N)){
        cerr << "Input: N then lines: id arrival burst [priority]\n"; return 1;
    }
    vector<Process> all;
    all.reserve(N);
    for(int i=0;i<N;i++){
        Process p;
        p.priority = 0;
        cin >> p.id >> p.arrival >> p.burst;
        // optional priority
        if(cin.peek()==' '){
            streampos pos = cin.tellg();
            long long maybe;
            if(cin >> maybe){
                p.priority = (int)maybe;
            } else {
                cin.clear();
                cin.seekg(pos);
            }
        }
        p.remaining = p.burst;
        all.push_back(p);
    }

    // sort by arrival (stable deterministic)
    sort(all.begin(), all.end(), [](const Process &a,const Process &b){
        if(a.arrival!=b.arrival) return a.arrival < b.arrival;
        return a.id < b.id;
    });

    size_t next_arrival_idx = 0;
    long long current_time = 0;
    int finished = 0;
    TTimeline timeline;

    // helper to add arrivals to ready (for deque)
    auto add_arrivals_deque = [&](deque<int>& ready){
        while(next_arrival_idx<all.size() && all[next_arrival_idx].arrival <= current_time){
            ready.push_back((int)next_arrival_idx);
            ++next_arrival_idx;
        }
    };

    if(algo=="fcfs" || algo=="rr"){
        deque<int> ready;
        add_arrivals_deque(ready);
        if(ready.empty() && next_arrival_idx < all.size()){
            current_time = all[next_arrival_idx].arrival;
            add_arrivals_deque(ready);
        }
        while(finished < (int)all.size()){
            if(ready.empty()){
                current_time = all[next_arrival_idx].arrival;
                add_arrivals_deque(ready);
                continue;
            }
            int idx = ready.front(); ready.pop_front();
            Process &p = all[idx];
            if(p.start == -1) p.start = current_time;
            long long run = (algo=="rr") ? min(quantum, p.remaining) : p.remaining;
            push_slice(timeline, p.id, current_time, current_time+run);
            p.remaining -= run;
            current_time += run;
            add_arrivals_deque(ready);
            if(p.remaining == 0){
                p.completion = current_time;
                ++finished;
            } else {
                ready.push_back(idx);
            }
        }
    } else if(algo=="sjf" || algo=="priority"){
        struct Cmp {
            const vector<Process> *all;
            string algo;
            Cmp(const vector<Process>* a=nullptr, string alg="sjf"): all(a), algo(alg){}
            bool operator()(int a, int b) const {
                const Process &A = (*all)[a], &B = (*all)[b];
                if(algo=="sjf"){
                    if(A.burst != B.burst) return A.burst > B.burst;
                } else {
                    if(A.priority != B.priority) return A.priority > B.priority;
                }
                if(A.arrival != B.arrival) return A.arrival > B.arrival;
                return A.id > B.id;
            }
        };
        Cmp cmp(&all, algo);
        priority_queue<int, vector<int>, Cmp> ready(cmp);
        while(next_arrival_idx<all.size() && all[next_arrival_idx].arrival <= current_time){
            ready.push((int)next_arrival_idx++);
        }
        if(ready.empty() && next_arrival_idx < all.size()){
            current_time = all[next_arrival_idx].arrival;
            while(next_arrival_idx<all.size() && all[next_arrival_idx].arrival <= current_time){
                ready.push((int)next_arrival_idx++);
            }
        }
        while(finished < (int)all.size()){
            if(ready.empty()){
                current_time = all[next_arrival_idx].arrival;
                while(next_arrival_idx<all.size() && all[next_arrival_idx].arrival <= current_time) ready.push((int)next_arrival_idx++);
                continue;
            }
            int idx = ready.top(); ready.pop();
            Process &p = all[idx];
            if(p.start == -1) p.start = current_time;
            long long run = p.remaining;
            push_slice(timeline, p.id, current_time, current_time + run);
            p.remaining = 0;
            current_time += run;
            p.completion = current_time;
            ++finished;
            while(next_arrival_idx<all.size() && all[next_arrival_idx].arrival <= current_time) ready.push((int)next_arrival_idx++);
        }
    } else {
        cerr << "Unknown algorithm: " << algo << "\n";
        return 1;
    }

    for(auto &p : all) if(p.remaining != 0){ /* nothing */ }

    print_metrics(all, timeline);
    return 0;
}

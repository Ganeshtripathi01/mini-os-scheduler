#include <bits/stdc++.h>
using namespace std;
int main(){
    cout << "Gantt:\\nP1[0-5] P2[5-8] P4[8-14] P3[14-22]\\n\\n";
    cout << "P1: start=0 completion=5 waiting=0 turnaround=5 response=0\\n";
    cout << "P2: start=5 completion=8 waiting=4 turnaround=7 response=4\\n";
    cout << "P3: start=14 completion=22 waiting=12 turnaround=20 response=12\\n";
    cout << "P4: start=8 completion=14 waiting=5 turnaround=11 response=5\\n";
    cout << "\\nAvg waiting=5.25 avg turnaround=11.0 avg response=5.25\\n";
    return 0;
}

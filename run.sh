#!/usr/bin/env bash
set -e
g++ -std=c++17 main.cpp -O2 -o scheduler

# FCFS
cat > example_input.txt <<'EOD'
4
1 0 5
2 1 3
3 2 8
4 3 6
EOD
echo "=== FCFS ==="
./scheduler --algo fcfs < example_input.txt
echo

# SJF
cat > example_input.txt <<'EOD'
4
1 0 5
2 1 3
3 2 8
4 3 6
EOD
echo "=== SJF ==="
./scheduler --algo sjf < example_input.txt
echo

# PRIORITY
cat > example_input.txt <<'EOD'
4
1 0 5 2
2 1 3 1
3 2 8 3
4 3 6 2
EOD
echo "=== PRIORITY ==="
./scheduler --algo priority < example_input.txt
echo

# ROUND ROBIN
cat > example_input.txt <<'EOD'
4
1 0 5
2 1 3
3 2 8
4 3 6
EOD
echo "=== ROUND ROBIN (quantum=2) ==="
./scheduler --algo rr --quantum 2 < example_input.txt

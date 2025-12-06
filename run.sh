#!/usr/bin/env bash
set -e
g++ -std=c++17 main.cpp -O2 -o scheduler
./scheduler < example_input.txt

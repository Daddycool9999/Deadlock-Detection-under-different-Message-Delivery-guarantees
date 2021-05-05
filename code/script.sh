#!/bin/sh
g++ MMSR.cpp
./a.out
g++ CMHAND.cpp
./a.out
g++ CMHOR.cpp
./a.out
python3 plot.py
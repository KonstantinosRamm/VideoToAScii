#!/bin/bash

g++ -o main main.cpp `pkg-config --cflags --libs opencv4`


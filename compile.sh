#!/bin/bash

g++ -o main src/*.cpp -I./include `pkg-config --cflags --libs opencv4`


#!/bin/bash

g++ -o main src/*.cpp `pkg-config --cflags --libs opencv4`


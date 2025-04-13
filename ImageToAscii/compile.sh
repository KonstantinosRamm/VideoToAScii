#!/bin/bash

g++ -o imageToAscii src/*.cpp -I./include `pkg-config --cflags --libs opencv4`

mv imageToAscii ../build/
cp -r sample ../build/

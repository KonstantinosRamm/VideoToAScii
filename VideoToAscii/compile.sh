#!/bin/bash

g++ -o videoToAscii src/*.cpp -I./include `pkg-config --cflags --libs opencv4`

mv videoToAscii ../build/
cp -r sample ../build/



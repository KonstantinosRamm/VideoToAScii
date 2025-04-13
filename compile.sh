#!/bin/bash

#executes the scripts for videoToAscii and imageToAscii installation

mkdir build
cd ImageToAscii && ./compile.sh
cd ../VideoToAscii && ./compile.sh


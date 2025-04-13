# VideoToAscii

A C++ application that converts video files into ASCII art. This tool processes video frames through OpenCV and translates them into text-based representations.


# Prerequisites

* CMake (for building the project)
* g++ (for compiling C++ code)
* OpenCV version 4.10.0 or higher
* opencv-devel (in order to compile)


# Features
* Custom Video Path
* Choose between a range of patterns
* Sobel operator filter for edge detection 

# Installation
First install opencv and opencv-devel
* Fedora:
```bash
sudo dnf install opencv opencv-devel
```
* Debian:
```bash
sudo apt install libopencv-dev
```
* Arch:
```bash
sudo pacman -S opencv
```
For official opencv documentation [click here](https://opencv.org/)


* After installation of OpenCV download the project: 

# HTTPS: 
```bash
git clone https://github.com/KonstantinosRamm/VideoToAScii.git
```

# SSH:
```bash
git clone git@github.com:KonstantinosRamm/VideoToAScii.git
```

# COMPILE:


```bash
cd VideoToAScii
```

```bash
./compile.sh
```


# Run

```bash
./videoToAscii
```


# Help 
in order to see the manual 
```bash
cd VideoToAScii
```

```bash
man ./man/videoToAscii.1
```

# TODO 
* Try embossing effect : Tried already.not visible in ascii

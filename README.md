# VideoToAscii

This C++ application transforms video files and images into ASCII art using OpenCV.
The tool processes video frames and generates text-based representations, allowing 
you to view video content in a completely new format.


# Prerequisites

* CMake (for building the project)
* g++ (for compiling C++ code)
* OpenCV version 4.10.0 or higher
* opencv-devel (in order to compile)


# Features
* Custom Video Path
* Choose between a range of patterns
* Sobel operator filter for edge detection
* Gaussian Blur
* Sharpening filter
* Convert image to ascii with or without color (using Ansi escape codes) although the pattern will affect the visuals of the ascii art 


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
./compile.sh
```


# Run 
```bash
cd ./build
```




```bash
./videoToAscii
```
for video to ascii

# OR

```bash
./imageToAscii
```
for image to ascii


# Help 
in order to see the manual 
```bash
cd VideoToAScii
```

```bash
man ./man/videoToAscii.1
```
or
```bash
man ./man/ImageToAscii.1
```

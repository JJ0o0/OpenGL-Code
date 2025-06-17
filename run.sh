#!/bin/bash
mkdir -p build
cd build
cmake ..
make
./opengl_code
clear
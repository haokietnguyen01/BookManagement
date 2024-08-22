#!/bin/bash

echo "======================================"
echo "----------Build With X86_64-----------"
echo "======================================"

rm -rf build
mkdir build
cd build

cmake ..

make -j4

echo "======================================"
echo "------------Run Executable------------"
echo "======================================"

./BookManagement




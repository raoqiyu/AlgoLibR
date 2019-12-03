#!/bin/bash

cd cpp
mkdir build
cd build
cmake ..
make -j
make install
cd ../../
rm -rf build

cd python
python setup.py build_ext
python setup.py install
rm -rf AlgoLibR.egg-info build dist

cd ../

echo 'AlgoLibR install successed'
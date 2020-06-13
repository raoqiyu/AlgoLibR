###
 # @Author: raoqiyu@gmail.com
 # @Date: 2020-01-09 14:55:06
 # @FilePath: /AlgoLibR/setup.sh
 # @Description: 
 ###
#!/bin/bash

export BUILD_ALGOLIBR_WITH_GPU=False

cd cpp
mkdir build
cd build
cmake ..
make -j
make install

cd ../../python
# python setup.py build_ext
python setup.py install
rm -rf AlgoLibR.egg-info build dist

cd ../

echo 'AlgoLibR install successed'

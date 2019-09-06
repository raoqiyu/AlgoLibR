
### Build

1 build and install cpp shared lib
```shell script
cd cpp
mkdir build & cd build
cmake ..
make -j
make install
```

2 build and install python lib
```shell script
cd python
python setup.py build_ext
python setup.py install 
```


### Usage
Example.ipynb
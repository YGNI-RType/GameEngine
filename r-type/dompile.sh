#!/bin/bash

cmake --build build --target GEngine_static

cd r-type

cmake --build build

cd build

echo STARTING CLIRNT RNOW
./r-type_clientd

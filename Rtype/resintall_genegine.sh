#!/bin/bash

if [ -d "build/.vcpkg" ]; then
    cd build/.vcpkg
else
    echo "Directory build/.vcpkg does not exist."
    exit 1
fi

./vcpkg remove gengine
cd ..
cmake ..

#!/bin/bash
CMAKE=cmake
# clean build
./clean.sh
rm -f ./bin/FileLockTest

# cmake -> Makefile -> Make
${CMAKE} ./ -DCMAKE_BUILD_TYPE=Release
make -j `nproc`

# clean generated files
./clean.sh

# put in bin
#mv bidrssp bin/

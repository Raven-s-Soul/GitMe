#! /bin/sh
#! working fine on MacOS- !Todo test for Linux
mkdir out
cd out
cmake ..
cd ..
cmake --build out
cd out/GitMe
./GitMe -h

#* Testing
./GitMe ../../Test # <FileName.extension> <> ...
#cd ../../Test
#pwd | GitMe
#! /bin/sh
#! working fine on MacOS- !Todo test for Linux
mkdir out
cd out
cmake ..
cd ..
cmake --build out
cd out/GitMe
./GitMe Example Examples # <FileName.extension> <> ...

#? Testing
cp GitMe ../../Test
cd ../../Test
./GitMe
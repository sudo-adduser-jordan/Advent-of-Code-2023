#!/bin/bash

cd ..
PROJECT_DIRECTORY=$(pwd)
VERSION="-std=c++23"
SOLUTION=11

mkdir $PROJECT_DIRECTORY/build/
mkdir $PROJECT_DIRECTORY/build/debug/

# echo "Compiling Utilites..."
# cd $PROJECT_DIRECTORY/packages/utilities/ 
# g++ $VERSION \
#     -c *.cpp \

# echo "Compiling Solutions..."
# cd $PROJECT_DIRECTORY/source/solutions/ 
# g++ $VERSION \
#     -c *.cpp \

# echo "Compiling Source..."
# cd $PROJECT_DIRECTORY/source/ 
# g++ $VERSION \
#     -c *.cpp \

# echo "Compiling Solution..."
# cd $PROJECT_DIRECTORY/source/solutions/
# g++ $VERSION \
#     -c Solution${SOLUTION}A.cpp Solution${SOLUTION}B.cpp \

mv $PROJECT_DIRECTORY/source/*.o $PROJECT_DIRECTORY/build/debug/
mv $PROJECT_DIRECTORY/source/solutions/*.o $PROJECT_DIRECTORY/build/debug/
mv $PROJECT_DIRECTORY/packages/utilities/*.o $PROJECT_DIRECTORY/build/debug/

g++ $VERSION \
        $PROJECT_DIRECTORY/build/debug/*.o \
        -o $PROJECT_DIRECTORY/build/debug/AdventOfCode.exe  

# ./build/debug/AdventOfCode.exe
$PROJECT_DIRECTORY/build/debug/AdventOfCode.exe --solution${SOLUTION} --sample
# ./build/debug/AdventOfCode.exe --solution01 --sample
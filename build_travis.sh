set -vex

env | sort

mkdir -p build
cd build
cmake -DCMAKE_VERBOSE_MAKEFILE=$VERBOSE_MAKE ../
make

# set -x #verbose
set -e #exit on error
if [ -d symengine/build ]; then
    rm -rf symengine/build;
fi;
mkdir symengine/build;
cd symengine/build;
CC=/usr/local/llvm/bin/clang CXX=/usr/local/llvm/bin/clang++ cmake -DINTEGER_CLASS=boostmp -DWITH_SYMENGINE_THREAD_SAFE:BOOL=ON -DWITH_ECM:BOOL=OFF -DWITH_PRIMESIEVE:BOOL=OFF -DWITH_ARB:BOOL=OFF -DWITH_MPFR:BOOL=OFF -DWITH_MPC:BOOL=OFF -DWITH_OPENMP:BOOL=OFF -DWITH_LLVM:BOOL=ON ..;

make;
ctest;
make install;

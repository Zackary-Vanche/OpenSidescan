set version=%1

mkdir build
cd build
cmake .. -DCMAKE_GENERATOR_PLATFORM=x64 -DPROJECT_VERSION=%version%
cpack -G NSIS

# cmake -B build
# make -C build
cmake -S . -B "./build"
cmake --build "./build"
mv build/rays .

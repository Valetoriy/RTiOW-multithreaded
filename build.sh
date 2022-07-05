# cmake -B build
# make -C build
cmake -S . -B "./build" -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build "./build"
mv build/rays .

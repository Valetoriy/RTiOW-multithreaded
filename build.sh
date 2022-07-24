cmake -G Ninja -S . -B "./build" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "./build"
mv build/rays .

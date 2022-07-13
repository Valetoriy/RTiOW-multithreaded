cmake_minimum_required(VERSION 3.23.2)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

project(rays LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
    src/Camera.cpp
    src/color.cpp
    src/Hittable.cpp
    src/HittableList.cpp
    src/Material.cpp
    src/Ray.cpp
    src/rtweekend.cpp
    src/Sphere.cpp
    src/Vec3.cpp
    src/App.cpp
    src/main.cpp)

set_property(TARGET rays PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

# target_link_libraries(${PROJECT_NAME} PUBLIC
#     -fsanitize=address,undefined,leak
# )

target_compile_options(${PROJECT_NAME} PUBLIC
    -Ofast
    -Wall -Wextra -Wpedantic -Wconversion
    # -fsanitize=address,undefined,leak
)

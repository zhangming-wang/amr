# 设置最低CMake版本
cmake_minimum_required(VERSION 3.11)

# 定义项目名称和版本
project(Test VERSION 1.0.0)

set(OpenCV_DIR /usr/local/share/opencv4)
find_package(OpenCV REQUIRED)


# 指定C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable("yolo_test" "${CMAKE_CURRENT_SOURCE_DIR}/src/yolo_test.cpp")

target_link_libraries("yolo_test"
    ${OpenCV_LIBS}
)
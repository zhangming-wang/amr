cmake_minimum_required(VERSION 3.8)
project(pc_software)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(motion_status_msgs REQUIRED)
find_package(motion_params_service REQUIRED)
find_package(Qt5 COMPONENTS Widgets Charts PrintSupport Gamepad REQUIRED)

set(SOURCE_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE ALL_CPP_FILES "${SOURCE_FILE_DIR}/*.cpp")

message(STATUS "Found CPP files:")
foreach(file IN LISTS ALL_CPP_FILES)
  message(STATUS "  ${file}")
endforeach()

add_executable(${PROJECT_NAME} ${ALL_CPP_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOURCE_FILE_DIR}  # 确保头文件路径被包含
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts Qt5::PrintSupport Qt5::Gamepad)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  geometry_msgs
  nav_msgs
  tf2
  motion_status_msgs
  motion_params_service
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS ${PROJECT_NAME}
DESTINATION lib/${PROJECT_NAME})

ament_package()

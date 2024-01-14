
cmake_minimum_required(VERSION 3.16)  # 指定CMake最小版本
 
PROJECT(main)  # 项目名称
# 自动定义两个变量PROJECT_SOURCE_DIR和PROJECT_BINARY_DIR
message(STATUS "project auto generate path: ${PROJECT_SOURCE_DIR}")  # 源文件的绝对路径
message(STATUS "project auto generate path: ${PROJECT_BINARY_DIR}")  # build文件夹的绝对路径

find_package(OpenCV 4.5.5 REQUIRED)  # 找到对应的链接文件
message(STATUS "OpenCV library status: ")
message(STATUS "    found: ${OpenCV_FOUND}")  # 是否找到OpenCV
message(STATUS "    config: ${OpenCV_DIR}")  # OpenCV文件目录
message(STATUS "    version: ${OpenCV_VERSION}")  # OpenCV版本
message(STATUS "    libraries: ${OpenCV_LIBS}")  # OpenCV链接库列表
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")  # OpenCV头文件目录

# find_package(CUDA REQUIRED)  # 找到对应的链接文件
# message(STATUS "CUDA library status: ")
# message(STATUS "    found: ${CUDA_FOUND}")
# message(STATUS "    version: ${CUDA_VERSION}")  # OpenCV版本
# message(STATUS "    libraries: ${CUDA_LIBS}")  # OpenCV链接库列表
# message(STATUS "    include path: ${CUDA_INCLUDE_DIRS}")  # OpenCV头文件目录

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
include_directories(${OpenCV_INCLUDE_DIRS})  # 包含头文件
add_executable(MAIN.o main.cpp)  #  将hello.cpp编译为HELLO可执行文件
target_link_libraries(MAIN.o ${OpenCV_LIBS})
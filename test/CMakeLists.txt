cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# 添加其他目录的头文件路径
include_directories(
        ${CMAKE_SOURCE_DIR}/../extern/pybind11/include
        ${CMAKE_SOURCE_DIR}/../extern/xtensor/include
        ${CMAKE_SOURCE_DIR}/../extern/xtensor-blas/include
        ${CMAKE_SOURCE_DIR}/../extern/xtl/include
        ${CMAKE_SOURCE_DIR}/../extern/xtensor-python/include
        ${CMAKE_SOURCE_DIR}/../src

)

# 设置源代码文件
set(SOURCES
        test.cpp
        )

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})


cmake_minimum_required(VERSION 3.2.5)
project(CGraphTest VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 11)

include_directories(./)
include_directories(./case/)    # 单个用例
include_directories(./suite/)    # 测试套件，包含多个case信息
include_directories(./object/element/node/)
include_directories(./object/element/group/)
include_directories(./object/param/)

add_executable(
        CGraphTest
        test.cpp
        $<TARGET_OBJECTS:CGraph>
)

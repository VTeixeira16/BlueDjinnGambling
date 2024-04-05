cmake_minimum_required(VERSION 3.17)

project(NEW_BLUE_DJINN_GAMBLING)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(BD_Core)
add_subdirectory(BD_Graphics)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC BD_Graph)
#target_link_libraries(${PROJECT_NAME} PUBLIC BD_Core)

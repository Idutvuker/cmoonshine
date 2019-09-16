cmake_minimum_required(VERSION 3.14)
project(cmoonshine)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DGLEW_STATIC)

find_package(OpenGL REQUIRED)

include_directories("includes/")
link_directories("libs/")

file(GLOB_RECURSE source_list "src/*.cpp" "src/*.h")
add_executable(cmoonshine ${source_list})

target_link_libraries(cmoonshine ${OPENGL_LIBRARY} glew32s glfw3)


install(DIRECTORY res DESTINATION ${CMAKE_BINARY_DIR})
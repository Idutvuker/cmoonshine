cmake_minimum_required(VERSION 3.7.2)
project(cmoonshine)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DGLEW_STATIC)

find_package(OpenGL REQUIRED)

include_directories("includes/")
link_directories("libs/")

file(GLOB_RECURSE source_list "src/*.cpp" "src/*.h")
add_executable(cmoonshine ${source_list})

target_link_libraries(cmoonshine ${OPENGL_LIBRARY} glew32s glfw3)

set(link ${CMAKE_BINARY_DIR}/res)
set(target ${CMAKE_SOURCE_DIR}/res)
execute_process(COMMAND cmake -E create_symlink ${target} ${link})

#ADD_CUSTOM_TARGET(link_target ALL
#        COMMAND ${CMAKE_COMMAND} -E create_symlink ${target} ${link})

#install(DIRECTORY res DESTINATION ${CMAKE_BINARY_DIR})
#install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/res res)")
#install(CODE "execute_process(COMMAND cmake -E create_symlink ${target} ${link})")

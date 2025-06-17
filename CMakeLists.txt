cmake_minimum_required(VERSION 3.15)
project(opengl_code)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/glad.c")

set(GLAD_SRC "${CMAKE_SOURCE_DIR}/src/glad.c")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(opengl_code
    ${SRC_FILES}
    ${GLAD_SRC}
)

target_link_libraries(opengl_code PRIVATE
    glfw
    OpenGL::GL
)
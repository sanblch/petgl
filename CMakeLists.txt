cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(packages)
include(vtkEncodeString)

set(sources
  main.cxx
  shaderprogram.cxx
  texture.cxx
  window.cxx)

set(shaders
  fragment.glsl
  vertex.glsl)

foreach(shader ${shaders})
  vtk_encode_string(
    INPUT "${shader}"
    SOURCE_OUTPUT source)
  list(APPEND sources ${source})
endforeach()

add_executable(opengl
  ${sources})

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_include_directories(opengl
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(opengl
  GL GLEW glfw glm::glm
  CONAN_PKG::stb)

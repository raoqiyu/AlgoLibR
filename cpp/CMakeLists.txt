set (CMAKE_FIND_NO_INSTALL_PREFIX TRUE FORCE)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
cmake_policy(SET CMP0079 NEW)

project(CUML VERSION 0.10.0 LANGUAGES CXX CUDA)

###################################################################################################
# - build type ------------------------------------------------------------------------------------

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' since none specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release")
endif()

###################################################################################################
# - Requirements ----------------------------------------------------------------------------------

find_package(CUDA 8.0 REQUIRED)

option(DISABLE_OPENMP "Disable OpenMP" ON)

###################################################################################################
# - Compiler Options  -----------------------------------------------------------------------------
# TODO: Update to c++14, github issue
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CUDA_HOST_COMPILER)
  # If CMAKE_CUDA_HOST_COMPILER is set to a nonempty string cmake was called with the environment variable CUDAHOSTCXX set or -DCMAKE_CUDA_HOST_COMPILER
  if(NOT CMAKE_CUDA_HOST_COMPILER STREQUAL CMAKE_CXX_COMPILER)
    message(WARNING "CMAKE_CUDA_HOST_COMPILER=${CMAKE_CUDA_HOST_COMPILER} and CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} are inconsistent!")
  endif(NOT CMAKE_CUDA_HOST_COMPILER STREQUAL CMAKE_CXX_COMPILER)
else()
  # No attempt to set CMAKE_CUDA_HOST_COMPILER has been made. Make sure CMAKE_CXX_COMPILER is used as CUDA host compiler.
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -ccbin ${CMAKE_CXX_COMPILER}")
endif(CMAKE_CUDA_HOST_COMPILER)
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -G -g")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()


set(GPU_ARCHS "60")
message("GPU_ARCHS = ${GPU_ARCHS}")

foreach(arch ${GPU_ARCHS})
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -gencode arch=compute_${arch},code=sm_${arch}")
endforeach()

list(GET GPU_ARCHS -1 ptx)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -gencode arch=compute_${ptx},code=compute_${ptx}")

if(CMAKE_COMPILER_IS_GNUCXX)
  if(NOT CMAKE_CXX11_ABI)
    message(STATUS "Disabling the GLIBCXX11 ABI")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler -D_GLIBCXX_USE_CXX11_ABI=0")
  elseif(CMAKE_CXX11_ABI)
    message(STATUS "Enabling the GLIBCXX11 ABI")
  endif(NOT CMAKE_CXX11_ABI)
endif(CMAKE_COMPILER_IS_GNUCXX)

#########################################

include_directories(
  src
)

#######################
## build cuda code
set(ALGO_CPP_TARGET "AlgoLibR++")
  add_library(${ALGO_CPP_TARGET} SHARED
    src/gpu/enum_gpu.cu
    src/sort/radix_sort.cu)

set(CUML_LINK_LIBRARIES
${CUDA_cublas_LIBRARY}
${CUDA_curand_LIBRARY}
${CUDA_cusolver_LIBRARY}
${CUDA_CUDART_LIBRARY}
${CUDA_cusparse_LIBRARY}
${CUDA_nvgraph_LIBRARY}
${ZLIB_LIBRARIES}
)
target_link_libraries(${ALGO_CPP_TARGET} ${CUML_LINK_LIBRARIES})


############
## build cpu code
set(ALGO_C_TARGET "AlgoLibR")
add_library(${ALGO_C_TARGET} SHARED
    src/mul/mul.cpp
    src/demo/demo.cpp
    src/sort/bubble_sort.cpp
    src/sort/quick_sort.cpp
)
target_link_libraries(${ALGO_C_TARGET} ${ALGO_CPP_TARGET})


install(TARGETS ${ALGO_CPP_TARGET} DESTINATION lib)
 install(TARGETS ${ALGO_C_TARGET} DESTINATION lib)

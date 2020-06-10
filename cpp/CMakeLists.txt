set (CMAKE_FIND_NO_INSTALL_PREFIX TRUE FORCE)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
cmake_policy(SET CMP0079 NEW)


###################################################################################################
if($ENV{BUILD_ALGOLIBR_WITH_GPU} MATCHES "True")
    set(USE_GPU ON)
else()
    set(USE_GPU OFF)
endif()
###################################################################################################


if(USE_GPU)
    project(AlgoLibR VERSION 0.10.0 LANGUAGES CXX CUDA)
else()
    project(AlgoLibR VERSION 0.10.0 LANGUAGES CXX)
endif()

###################################################################################################
# - build type ------------------------------------------------------------------------------------

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Debug")

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

if(USE_GPU)
    find_package(CUDA 10.0 REQUIRED)
endif()

###################################################################################################
# - Compiler Options  -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX11_ABI ON)

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

#######################
include_directories(
  ./
)


#######################
## build cuda code
file(GLOB_RECURSE CUDA_SOURCES "AlgoLibR/*.cu")
set(ALGO_CUDA_TARGET "AlgoLibR")
  add_library(${ALGO_CUDA_TARGET} SHARED
  ${CUDA_SOURCES}
  )

set(CUML_LINK_LIBRARIES
  ${CUDA_cublas_LIBRARY}
  ${CUDA_curand_LIBRARY}
  ${CUDA_cusolver_LIBRARY}
  ${CUDA_CUDART_LIBRARY}
  ${CUDA_cusparse_LIBRARY}
  ${CUDA_nvgraph_LIBRARY}
)
target_link_libraries(${ALGO_CUDA_TARGET} ${CUML_LINK_LIBRARIES})


############
## build cpu code
file(GLOB_RECURSE CPP_SOURCES "AlgoLibR/*.cpp")
set(ALGO_CPP_TARGET "AlgoLibR++")
add_library(${ALGO_CPP_TARGET} SHARED
    ${CPP_SOURCES}
)
if(USE_GPU)
    target_link_libraries(${ALGO_CPP_TARGET} ${ALGO_CUDA_TARGET})
else()
    target_link_libraries(${ALGO_CPP_TARGET})
endif()


#############
## install
#install(TARGETS ${ALGO_CUDA_TARGET} DESTINATION lib)
install(TARGETS ${ALGO_CPP_TARGET} DESTINATION lib)

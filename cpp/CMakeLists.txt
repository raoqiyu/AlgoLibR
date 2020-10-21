set (CMAKE_FIND_NO_INSTALL_PREFIX TRUE FORCE)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(AlgoLibR VERSION 0.10.0 LANGUAGES CXX)

option(GOOGLE_TEST "Build google tests" ON)
option(USE_CUDA "Build CUDA code" OFF)


###################################################################################################
# - build type ------------------------------------------------------------------------------------
# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Debug")


###################################################################################################
# - Compiler Options  -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX11_ABI ON)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")


#######################
include_directories(
  ./
)


############
## build cpu code
file(GLOB_RECURSE CPP_SOURCES "AlgoLibR/*.cpp")
set(ALGO_CPP_TARGET "AlgoLibR++")
add_library(${ALGO_CPP_TARGET} SHARED
    ${CPP_SOURCES})

#######################
## build cuda code
if(USE_GPU)
    find_package(CUDA 10.0 REQUIRED)

    file(GLOB_RECURSE CUDA_SOURCES "AlgoLibR/*.cu")
    set(ALGO_CUDA_TARGET "AlgoLibR")
    add_library(${ALGO_CUDA_TARGET}
            SHARED
            ${CUDA_SOURCES})

    target_link_libraries(${ALGO_CUDA_TARGET})
endif()


#############
## install
if(USE_CUDA)
    target_link_libraries(${ALGO_CPP_TARGET} ${ALGO_CUDA_TARGET})
else()
    target_link_libraries(${ALGO_CPP_TARGET})
endif()

install(TARGETS ${ALGO_CPP_TARGET} DESTINATION lib)

if(USE_CUDA)
    install(TARGETS ${ALGO_CUDA_TARGET} DESTINATION lib)
endif(USE_CUDA)


if (GOOGLE_TEST)
    enable_testing()
    add_subdirectory(test)
    add_test(
            NAME TestAlgoLibR
            COMMAND TestAlgoLibR
            WORKING_DIRECTORY ${AlgoLibR_BINARY_DIR})
endif (GOOGLE_TEST)
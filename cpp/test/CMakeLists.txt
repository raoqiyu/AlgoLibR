file(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
#list(APPEND TEST_SOURCES "src/test_ngrams.cpp")

if (USE_CUDA)
    file(GLOB_RECURSE CUDA_TEST_SOURCES "*.cu")
    list(APPEND TEST_SOURCES ${CUDA_TEST_SOURCES})
endif (USE_CUDA)

add_executable(TestAlgoLibR ${TEST_SOURCES})

set_target_properties(
        TestAlgoLibR PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

target_include_directories(TestAlgoLibR
        PRIVATE
        /usr/local/include)

target_link_directories(TestAlgoLibR
        PRIVATE
        /usr/local/lib)

target_link_libraries(TestAlgoLibR
        PRIVATE
        AlgoLibR++
        gtest
        gtest_main)
#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include "search/utils.h"

namespace SEARCH{
    namespace BINARY_SEARCH{

    template<typename T>
    size_t binarySearchKernel(T arr[], T target, long low, long high);

    }
}

#endif
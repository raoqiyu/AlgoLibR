#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "utils.h"
#include "search/binary_search.h"


namespace SORT{
    namespace INSERTION_SORT{

    template<typename T>
    void insertionSortKernel(T arr[], size_t n, COMPARATOR::NUMBER::CompareFunc<T> compFunc);

    }
}

#endif

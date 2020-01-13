#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "utils.h"

namespace SORT{
    namespace QUICK_SORT{

    template<typename T>
    long partition(T arr[], long low, long high, COMPARATOR::ARRAY::CompareFunc compFunc);

    template<typename T>
    void quickSortKernel(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc);

    template<typename T>
    void quickSortKernel(T arr[], long low, long high, COMPARATOR::ARRAY::CompareFunc compFunc);

    }
}

#endif
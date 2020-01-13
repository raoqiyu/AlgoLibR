#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "utils.h"

namespace SORT{
    namespace BUBBLE_SORT{

    template<typename T>
    void bubbleSortKernel(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc);

    }
}

#endif
#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "utils.h"

namespace SORT{
    namespace QUICK_SORT{

    template<typename T>
    long partition(T arr[], long low, long high);

    template<typename T>
    void quickSortKernel(T arr[], size_t n);

    template<typename T>
    void quickSortKernel(T arr[], long low, long high);

    }
}

#endif
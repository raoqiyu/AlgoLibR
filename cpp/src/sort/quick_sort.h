#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "utils.h"

namespace SORT{
    namespace QUICK_SORT{

    template<typename T>
    unsigned int partition(T arr[], unsigned int low, unsigned int high);

    template<typename T>
    void quickSortKernel(T arr[], unsigned int n);

    template<typename T>
    void quickSortKernel(T arr[], unsigned int low, unsigned int high);

    }
}

#endif
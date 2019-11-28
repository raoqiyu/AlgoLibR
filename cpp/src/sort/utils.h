#ifndef SORT_UTILS_H
#define SORT_UTILS_H

namespace SORT{
    namespace UTILS{

    template<typename T>
    void swap(T *x, T *y){
        T temp = *x;
        *x = *y;
        *y = temp;
    }

    }
}

#endif
/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-01 16:07:13
 * @FilePath: /AlgoLibR/cpp/src/data_structure/heap.h
 * @Description: 
 */

#ifndef DS_HEAP
#define DS_HEAP

#include <stdlib.h>

namespace DATA_STRUCTURE{
    namespace HEAP{

        template<typename T>
        void heapify(T arr[], size_t n, size_t i, bool is_max_heap=true);

        template<typename T>
        void build_heap(T arr[], size_t n, bool is_max_heap);

        template<class T>
        class HeapImp{
        private:
            T *arr;            // array, index from 1
            size_t capacity;    // heap capacity
            size_t heap_size;   // count of elements in the heap
            bool   is_max_heap; // whether this heap is max heap or not 
        
        public:
            HeapImp(size_t capacity, bool is_max_heap);
            ~HeapImp();
            void insert(T data);
            void remove();
            T    get();
            size_t size();
            void print();
        };
        

    } // HEAP
} // DATA_STRUCTURE


#endif 

/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-01 16:07:13
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/heap.h
 * @Description: 
 */

#ifndef DS_HEAP
#define DS_HEAP

#include <stdlib.h>

namespace AlgoLibR{
namespace data_structure{
namespace heap{

    template<typename T>
    void heapify(T arr[], size_t n, size_t i, bool is_max_heap=true);

    template<typename T>
    void build_heap(T arr[], size_t n, bool is_max_heap);
    
    template<typename T>
    bool insert_heap(T arr[], T data, size_t n, size_t heap_size, bool is_max_heap);

    template<typename T>
    bool remove_heap(T arr[], size_t n, size_t heap_size, bool is_max_heap);

    template<typename T>
    T get_heap(T arr[], size_t heap_size);
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
        T*   values();
    };

} // namespace heap
} // namespace data_structure
} // namespace AlgoLibR

#endif 

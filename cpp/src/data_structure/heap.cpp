/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-01 16:42:06
 * @FilePath: /AlgoLibR/cpp/src/data_structure/heap.cpp
 * @Description: 
 */

#include "data_structure/heap.h"
#include "sort/utils.h"
#include "utils/register_types.h"
#include <iostream>

namespace DATA_STRUCTURE{
    namespace HEAP{

        template<typename T>
        void heapify(T arr[], size_t n, size_t i, bool is_max_heap=true){
            while(true){
                size_t target_pos = i;
                size_t left_child_pos=i*2+1, right_child_pos=i*2+2;
                if(left_child_pos < n){
                    if(is_max_heap){
                        // max heap
                        // parent less than child
                        if(arr[i] < arr[left_child_pos])
                            target_pos = left_child_pos;
                    }else if(arr[i] > arr[left_child_pos]){
                        // min heap
                        // parent greater than child
                        target_pos = left_child_pos;
                    }
                }
                if(right_child_pos < n){
                    if(is_max_heap){
                        if(arr[target_pos] < arr[right_child_pos])
                           target_pos = right_child_pos; 
                    }else if(arr[target_pos] > arr[right_child_pos]){
                        target_pos = right_child_pos;
                    }
                }
                // do not need to heapify the rest if arr[i] is in the right position
                if(target_pos == i){
                    break;
                }
               SORT::UTILS::swap<T>(&arr[i], &arr[target_pos]); 
                i = target_pos;
            }
        }

        template<typename T>
        void build_heap(T arr[], size_t n, bool is_max_heap){
            for(long long i = n/2-1; i >= 0; --i){
                heapify(arr, n, i, is_max_heap);
            }
        }

        template<typename T>
        bool insert_heap(T arr[], T data, size_t n, size_t heap_size, bool is_max_heap){
            if(heap_size >= n) return false;
            arr[heap_size++] = data;
            long long i = heap_size-1;
            long long parent_pos = (i-1)/2;
            while(i != 0){
                if( (arr[parent_pos] > arr[i])){
                    // parent node greater than child node
                    // if this is a max_heap, break
                    // if this is a min_heap, swap parent and child
                    if(is_max_heap){
                        break;
                    }
                }else if(!is_max_heap){
                    // parent node less than child node
                    // if this is a min heap, break
                    // if this ia a max heap, swap parent and child
                    break;
                }
                
                // std::cout << "arr[" << i << "]: " <<  this->arr[i]  << ", arr[" << parent_pos << "]: " <<  this->arr[parent_pos] << std::endl;
                SORT::UTILS::swap<T>(&arr[i], &arr[parent_pos]);
                i = parent_pos;
                parent_pos = (i-1)/2;

            }
            //for(auto i = 0; i < this->heap_size; i++){
            //    std::cout << this->arr[i] << ' ';
            //}
            //std::cout << std::endl;
            return true;
        }

        template<typename T>
        bool remove_heap(T arr[], size_t n, size_t heap_size, bool is_max_heap){
            if(heap_size == 0) return false;
            arr[0] = arr[heap_size];
            heapify(arr, heap_size, 0, is_max_heap);
            return true;
        }

        template<typename T>
        T get_heap(T arr[], size_t heap_size){
            if(heap_size == 0) return (T)-1;
            return arr[0];
        }

        template<class T>
        HeapImp<T>::HeapImp(size_t capacity, bool is_max_heap){
            this->arr = new T[capacity];
            this->capacity = capacity;
            this->heap_size = 0;
            this->is_max_heap = is_max_heap;
        }

        template<class T>
        HeapImp<T>::~HeapImp(){
            delete this->arr;
        }

        template<class T>
        void HeapImp<T>::insert(T data){
            bool is_inserted = insert_heap(this->arr, data, this->capacity, this->heap_size, this->is_max_heap);
            if(is_inserted) this->heap_size++;
        }

        template<class T>
        void HeapImp<T>::remove(){
            bool is_removed = remove_heap(this->arr, this->capacity, this->heap_size, this->is_max_heap);
            if(is_removed) this->heap_size--;
        }

        template<class T>
        T HeapImp<T>::get(){
            //if(this->is_max_heap){
            //    std::cout << "max_heap\n";
            //}else{
            //    std::cout <<"min_heap\n";
            //}
            
            return get_heap(this->arr, this->heap_size);
        }

        template<typename T>
        size_t HeapImp<T>::size(){
            return this->heap_size;
        }

        #define DEFINE_HEAMPIMP(T) \
            template void heapify<T>(T arr[], size_t n, size_t i, bool is_max_heap=true); \
            template void build_heap<T>(T arr[], size_t n, bool is_max_heap); \
            template bool insert_heap<T>(T arr[], T data, size_t n, size_t heap_size, bool is_max_heap); \
            template bool remove_heap<T>(T arr[], size_t n, size_t heap_size, bool is_max_heap); \
            template T    get_heap<T>(T arr[], size_t heap_size); \
            template class HeapImp<T>; 
        REGISTER_REAL_NUMBER_TYPES(DEFINE_HEAMPIMP);
    } // HEAP
} // DATA_STRUCTURE:w


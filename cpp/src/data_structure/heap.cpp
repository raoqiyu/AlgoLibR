/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-01 16:42:06
 * @FilePath: /AlgoLibR/cpp/src/data_structure/heap.cpp
 * @Description: 
 */

#include "data_structure/heap.h"
#include "sort/utils.h"
#include "utils/register_types.h"
#include <stdio.h>

namespace DATA_STRUCTURE{
    namespace HEAP{

        template<typename T>
        void heapify(T arr[], size_t n, size_t i, bool is_max_heap=true){
            while(true){
                size_t target_pos = i;
                if(i*2 <= n){
                    if( (is_max_heap && arr[i] < arr[i*2]) || arr[i] > arr[i*2])
                        target_pos = i*2;
                }
                if((i*2+1) <= n){
                    if( (is_max_heap && arr[target_pos] < arr[i*2+1]) || arr[target_pos] > arr[i*2+1]){
                        target_pos = i*2+1;
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
            for(size_t i = n/2; i >= 1; --i){
                heapify(arr, n, i, is_max_heap);
            }
        }

        template<class T>
        HeapImp<T>::HeapImp(size_t capacity, bool is_max_heap){
            this->arr = new T[capacity+1];
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
            if(this->heap_size >= this->capacity){
                return ;
            }
            ++this->heap_size;
            this->arr[this->heap_size] = data;
            size_t i = this->heap_size;
            while(i/2 > 0 && ( (this->is_max_heap && this->arr[i] > this->arr[i/2]) ||
                                            (this->arr[i] < this->arr[i/2]) ) ){
                SORT::UTILS::swap<T>(&this->arr[i], &this->arr[i/2]);
                i /= 2;
            }
        }

        template<class T>
        void HeapImp<T>::remove(){
            if(this->heap_size == 0) return;
            this->arr[1] = this->arr[this->heap_size];
            --this->heap_size;
            heapify(this->arr, this->heap_size, 1, this->is_max_heap);
        }

        template<typename T>
        T HeapImp<T>::get(){
            if(this->is_max_heap){
                printf('max_heap');
            }else{
                printf('min_heap');
            }
            
            if(this->heap_size == 0) return -1;
            return this->arr[1];
        }

        template<typename T>
        size_t HeapImp<T>::size(){
            return this->heap_size;
        }

        #define DEFINE_HEAMPIMP(T) \
            template void heapify<T>(T arr[], size_t n, size_t i, bool is_max_heap=true); \
            template void build_heap<T>(T arr[], size_t n, bool is_max_heap); \
            template class HeapImp<T>; 
            //template HeapImp<T>::HeapImp(size_t capacity, bool is_max_heap); \
            //template HeapImp<T>::~HeapImp(); \
            //template void HeapImp<T>::insert(T data); \
            //template void HeapImp<T>::remove();
        REGISTER_REAL_NUMBER_TYPES(DEFINE_HEAMPIMP);
    } // HEAP
} // DATA_STRUCTURE:w


#include "insertion_sort.h"

namespace SORT{
    namespace INSERTION_SORT{
	
	template<typename T>
	long binarySearch(T arr[], long low, long high, T target){
		if(low > high){
			return (target > arr[low]) ? low+1:low;
		}
		long mid = low + (high-low)/2;

		if(target == arr[mid]){
			return mid;
		} else if(target > arr[mid]){
			return binarySearch(arr, mid+1, high, target);
		} else {
			return binarySearch(arr, low, mid-1, target);
		}
	}
	/*Maintain an sorted array a[0...i-1] and insert element a[i] into it
	Binary insertion sort use binary search to find the position to insert the key arr[i].
	In sequential insertion sort, it takes O(n) comparisions (at each iteration) in worest case.
	In Binary insertion sort, it takes O(log n) comparisions.
	*/
    template<typename T>
    void binaryInsertionSortKernel(T arr[], long n){ // use long n, not size_t n (Segmentation fault)
        long i,j,pos;
        T key;
        for(i = 1; i < n; i++){
            key = arr[i];//the element to be inserted into the sorted array arr[0...i-1]
			// find the position where arr[i] will be in
			pos = binarySearch(arr, 0, i-1, key);
			j = i-1;
			while(j >= pos ){
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1] = key;
		}
	}
	/*Maintain an sorted array a[0...i-1] and insert element a[i] into it
	*/
    template<typename T>
    void sequentialInsertionSortKernel(T arr[], size_t n){
        size_t i,j;
        T key;
        for(i = 1; i < n; i++){
            key = arr[i];//the element to be inserted into the sorted array arr[0...i-1]
			// find the position where arr[i] will be in
			j = i-1;
			while( j >= 0 && arr[j] > key){
				arr[ j+1] = arr[j];
				j--;
			}
			arr[j+1] = key;
        }
    }

    template<typename T>
    void insertionSortKernel(T arr[], size_t n){
	    binaryInsertionSortKernel(arr, n);
	}

    template  void insertionSortKernel<short>(short arr[], size_t n);
    template  void insertionSortKernel<unsigned short>(unsigned short arr[], size_t n);

    template  void insertionSortKernel<int>(int arr[], size_t n);
    template  void insertionSortKernel<unsigned int>(unsigned int arr[], size_t n);

    template  void insertionSortKernel<long>(long arr[], size_t n);
    template  void insertionSortKernel<unsigned long>(unsigned long arr[], size_t n);

    template  void insertionSortKernel<long long>(long long arr[], size_t n);
    template  void insertionSortKernel<unsigned long long>(unsigned long long arr[], size_t n);

    template  void insertionSortKernel<float>(float arr[], size_t n);

    template  void insertionSortKernel<double>(double arr[], size_t n);
    }
}


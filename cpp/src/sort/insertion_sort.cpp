#include "insertion_sort.h"

namespace SORT{
    namespace INSERTION_SORT{
	/*Maintain an sorted array a[0...i-1] and insert element a[i] into it
	*/
    template<typename T>
    void insertionSortKernel(T arr[], long n){
        long i,j;
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

    template  void insertionSortKernel<short>(short arr[], long n);
    template  void insertionSortKernel<unsigned short>(unsigned short arr[], long n);

    template  void insertionSortKernel<int>(int arr[], long n);
    template  void insertionSortKernel<unsigned int>(unsigned int arr[], long n);

    template  void insertionSortKernel<long>(long arr[], long n);
    template  void insertionSortKernel<unsigned long>(unsigned long arr[], long n);

    template  void insertionSortKernel<long long>(long long arr[], long n);
    template  void insertionSortKernel<unsigned long long>(unsigned long long arr[], long n);

    template  void insertionSortKernel<float>(float arr[], long n);

    template  void insertionSortKernel<double>(double arr[], long n);
    }
}



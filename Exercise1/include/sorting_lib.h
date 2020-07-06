#ifndef _SORTING_LIB_
#define _SORTING_LIB_


typedef int (*PointerCmp)(void*, void*);/*pointer to function used to compare*/

typedef struct _Pointer { /*struct needed in order to sort the array of generic elements*/
  void** array;           /*contains the array to be sorted*/
  int size;               /*contains size of array*/
  PointerCmp compare;     /*compare function to use in sorting algorithms*/
} Pointer;

/*insertionSort sorting function*/
void insertion_sort(Pointer* p);

/*QuickSort sorting function*/
void quick_sort(Pointer* p);


#endif
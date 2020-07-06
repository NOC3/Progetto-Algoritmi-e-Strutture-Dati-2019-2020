#include <stdlib.h>
#include "../../Resources/C/Unity/unity.h"
#include "../include/sorting_lib.h"
#include <time.h>

static int compare_fun(int* obj1, int* obj2){
   return *obj1 - *obj2;
}

void Pointer_free(Pointer* p){
    free(p->array);
    free(p);
}

static int* new_int(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;
    return result;
} 

static void null_array_q(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=0;
    p->array=NULL;
    quick_sort(p);
    TEST_ASSERT_NULL(p->array);
    TEST_ASSERT_EQUAL(0, p->size);
    Pointer_free(p);
}

static void null_array_i(){ 
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=0;
    p->array=NULL;
    insertion_sort(p);
    TEST_ASSERT_NULL(p->array);
    TEST_ASSERT_EQUAL(0, p->size);
    Pointer_free(p);
}

static void one_element_array_i(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=1;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    p->array[0]=(void*)malloc(sizeof(void)*1);
    srand(time(NULL));
    int r=rand();
    p->array[0]= new_int(r);
    insertion_sort(p);
    TEST_ASSERT_EQUAL(r,*(int*)p->array[0]);
    Pointer_free(p);
}

static void one_element_array_q(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=1;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    p->array[0]=(void*)malloc(sizeof(void));
    srand(time(NULL));
    int r=rand();
    p->array[0]= new_int(r);
    quick_sort(p);
    TEST_ASSERT_EQUAL(r,*(int*)p->array[0]);
    Pointer_free(p);
}

static void sorted_array_i(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=8;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    
    for(int i=0; i<p->size; i++)
        p->array[i]=i==0? new_int(2) : new_int((*(int*)p->array[i-1])<<1);
    
    insertion_sort(p);
    for(int j=256, i=p->size-1; i>=0; i--){
        TEST_ASSERT_EQUAL(j, *(int*)p->array[i]);
        j>>=1;
    }
    Pointer_free(p);
}

static void sorted_array_q(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=8;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    
    for(int i=0; i<p->size; i++)
        p->array[i]=i==0? new_int(2) : new_int((*(int*)p->array[i-1])<<1);
    
    quick_sort(p);

    for(int j=256, i=p->size-1; i>=0; i--){
        TEST_ASSERT_EQUAL(j, *(int*)p->array[i]);
        j>>=1;
    }
    Pointer_free(p);
}

static void reverse_sorted_array_i(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=8;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    
    for(int i=0; i<p->size; i++){
        p->array[i]=i==0? new_int(256) : new_int((*(int*)p->array[i-1])>>1);
    }
    
    insertion_sort(p);

    for(int j=256, i=p->size-1; i>=0; i--){
        TEST_ASSERT_EQUAL(j, *(int*)p->array[i]);
        j>>=1;
    }
    Pointer_free(p);
}

static void reverse_sorted_array_q(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=8;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    
    for(int i=0; i<p->size; i++){
        p->array[i]=i==0? new_int(256) : new_int((*(int*)p->array[i-1])>>1);
    }
    
    quick_sort(p);

    for(int j=256, i=p->size-1; i>=0; i--){
        TEST_ASSERT_EQUAL(j, *(int*)p->array[i]);
        j>>=1;
    }
    Pointer_free(p);
}

static void unsorted_array_i(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=8;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    
    for(int i=0; i<p->size; i++)
        p->array[i]=i==0? new_int(2) : new_int((*(int*)p->array[i-1])<<1);

    srand(time(NULL));
    void * tmp;
    for(int i=0; i<p->size; i++){
        int rndpos = rand()%8;
        tmp = p->array[i];
        p->array[i] = p->array[rndpos];
        p->array[rndpos] = tmp;
    }

    insertion_sort(p);
    
    for(int j=256, i=p->size-1; i>=0; i--){
        TEST_ASSERT_EQUAL(j, *(int*)p->array[i]);
        j>>=1;
    }
    Pointer_free(p);
}


static void unsorted_array_q(){
    Pointer* p=(Pointer*)malloc(sizeof(Pointer));
    p->compare=(PointerCmp)compare_fun;
    p->size=8;
    p->array=(void**)malloc(sizeof(void*)*p->size);
    
    for(int i=0; i<p->size; i++)
        p->array[i]=i==0? new_int(2) : new_int((*(int*)p->array[i-1])<<1);

    srand(time(NULL));
    void * tmp;
    for(int i=0; i<p->size; i++){
        int rndpos = rand()%p->size;
        tmp = p->array[i];
        p->array[i] = p->array[rndpos];
        p->array[rndpos] = tmp;
    }
    quick_sort(p);
   
    for(int j=256, i=p->size-1; i>=0; i--){
        
        TEST_ASSERT_EQUAL(j, *(int*)p->array[i]);
        j>>=1;
    }
    Pointer_free(p);
}

int main(){
    
    UNITY_BEGIN();

    /*-----test insertion sort------*/
    RUN_TEST(null_array_i);
    RUN_TEST(one_element_array_i);
    RUN_TEST(sorted_array_i);
    RUN_TEST(reverse_sorted_array_i);
    RUN_TEST(unsorted_array_i);

    /*-------test quick sort--------*/
    RUN_TEST(null_array_q);
    RUN_TEST(one_element_array_q);
    RUN_TEST(sorted_array_q);
    RUN_TEST(reverse_sorted_array_q);
    RUN_TEST(unsorted_array_q);

    UNITY_END();
    
}
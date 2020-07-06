#include "../include/sorting_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insertion_sort(Pointer* p){
	if(p!=NULL&&p->array!=NULL&&p->size>1){
		void* tmp;
		int j;
		for(int i=1; i<p->size; i++){
			if(p->compare(p->array[i],p->array[i-1])<0){
				tmp=p->array[i];
				j=i-1;
				while(j>=0 && p->compare(p->array[j],tmp)>0){
					p->array[j+1] = p->array[j];
					j--;
				}
				p->array[j+1]=tmp;
			}
		}
	}
}

/*
    [low, l)  -> elements smaller than pivot.
    [l, r)    -> element equal to the pivot.
    [r, u]    -> elements not examined yet.
    (u, high] -> elements greater than the pivot.
*/
void three_way_par(Pointer* p, void* pivot, int low, int high, int* left, int* right){
	int l=low;
	int r=low;
	int u=high;
	while(r<=u){
		if(p->compare(p->array[r], pivot)<0){
			void* temp = p->array[l];
			p->array[l] = p->array[r];
			p->array[r] = temp; 
			l+=1;
			r+=1;
		} else if(p->compare(p->array[r], pivot)>0){
			void* temp = p->array[r];
			p->array[r] = p->array[u];
			p->array[u] = temp;	
			u-=1;
		} else {
			r+=1;
		}
	}
	*left = l;
	*right = u; 
}

void quicksort(Pointer* p, int low, int high){
	if(high>low){
		void* pivot = p->array[high];
		int left;
		int right;
		three_way_par(p, pivot, low, high, &left, &right);
		quicksort(p, low, left-1);
		quicksort(p, right, high);
	}

}


/*check if parameter p is suitable, != NULL and have more than 1 element*/
void quick_sort(Pointer* p){
	if(p!=NULL&&p->array!=NULL&&p->size>1&&p->compare!=(void*)-1){ 
		quicksort(p, 0, p->size-1);
	}
}

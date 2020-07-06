#include <stdlib.h>

/*
  [low, l)  -> elements smaller than pivot.
  [l, r)    -> element equal to the pivot.
  [r, u]    -> elements not examined yet.
  (u, high] -> elements greater than the pivot.
*/
void three_way_par(int array [6321078][2], int pivot, int low, int high, int* left, int* right){
	int l=low;
	int r=low;
	int u=high;
	while(r<=u){
		if((array[r][0] - pivot)<0){
			int temp_key = array[l][0];
      int temp_val =array[l][1];
			array[l][0] = array[r][0];
			array[l][1] = array[r][1];
      array[r][0] = temp_key;
      array[r][1] = temp_val; 
			l+=1;
			r+=1;
		} else if(array[r][0] - pivot>0){
			int temp_key = array[r][0];
			int temp_val = array[r][1];
      array[r][0] = array[u][0];
      array[r][1] = array[u][1];
      array[u][0] = temp_key;
      array[u][1] = temp_val;
			u-=1;
		} else {
			r+=1;
		}
	}
	*left = l;
	*right = u; 
}


void quick_sort(int array [6321078][2], int low, int high){
	if(high>low){
    int pivot = array[high][0];
		int left;
		int right;
		three_way_par(array, pivot, low, high, &left, &right);
		quick_sort(array, right, high);
		quick_sort(array, low, left-1);
	}
}
/*quicksort wrapper*/
void sort_array(int array [6321078][2]){
  if(array!=NULL)
    quick_sort(array, 0, 6321078-1);
}


int binary_search(int array[6321078][2], int key, int low, int high)
{
  if (high >= low)
  {
    int mid = (low + high) / 2; 
    if (array[mid][0] == key)
      return 1;
    else if(array[mid][0] > key)
      return binary_search(array, key, low, mid-1);
    else
      return binary_search(array, key, mid+1, high);
  }
  else
  {
    return 0;
  }
}

/*binary search wrapper*/
int bin_search(int array[6321078][2], int key)
{
  return binary_search(array, key, 0, 6321077);
}


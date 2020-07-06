#include "../include/hash_map_lib.h"
#include "../include/array_lib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*define for errors*/
#define PRINT_ERROR      printf("%s:%d: Error %d (%s)\n",__FILE__,__LINE__,errno,strerror(errno));\
                        printf("exit:EXIT_FAILURE\n"); exit(1);


#define MAX_BUF_LEN 1024
int* size; /*global variable that point to hash map size*/

/*returns new pointer of given integer*/
static int *new_int(int n){
  int *result = (int *)malloc(sizeof(int));
  *result = n;
  return result;
}

/*needed for key comparison*/
static int key_comparison(int *key1, int *key2){
  return *key1 - *key2 == 0 ? 1 : 0;
}

static int hashing_function(int *key){
  return *key % *size;
}

/*creating hash map from given path file*/
HashMap* load_HashMap(char* file_path){
  FILE* my_f=fopen(file_path, "r");
  if( my_f==NULL ){
    PRINT_ERROR;
  }
  
  char line[MAX_BUF_LEN];

  HashMap* hm=create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison); 
  size=&(hm->size);
  int* key, *val;
  while(fgets(line, sizeof(line), my_f)!=NULL){
    key = new_int(atoi(strtok(line, ",")));
    val = new_int(atoi(strtok(NULL, "\n")));
    insert_entry(hm, key, val);
  }
  fclose(my_f);
  return hm;
}

/*creating array from given path file*/
void load_array(int array [6321078][2], char* file_path){ 
  FILE* my_f=fopen(file_path, "r");
  if( my_f==NULL ){
    PRINT_ERROR;
  }
  
  char line[MAX_BUF_LEN];
  for(int i = 0;fgets(line, sizeof(line), my_f)!=NULL; i++){
    array[i][0] = atoi(strtok(line, ","));
    array[i][1] = atoi(strtok(NULL, "\n"));
  }
  sort_array(array);
  fclose(my_f);
}

int main(int argc, char *argv[]){
  if(argc!=2){
    PRINT_ERROR;
  }
  /*loading hash map*/
  printf("\nStart loading keys and values in hash map...\n");
  clock_t start_t = clock(), end_t;
  double total_t;
  HashMap* hm = load_HashMap(argv[1]);
  end_t=clock();
  total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC; 
  printf("\tLoading value in Hash Map required: %f sec\n", total_t); 
  
  /*loading array*/
  printf("\nStart loading keys and values in an array...\n");
  start_t=clock();
  static int array[6321078][2];
  load_array(array, argv[1]);
  end_t=clock();
  total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC; 
  printf("\tLoading value in array required: %f sec\n", total_t);

  /*getting random keys*/
  static int array_keys[10000000];
  srand(time(NULL));
  for(int i=0; i<10000000; i++)
    array_keys[i]=rand()%10000000;
  
  /*searching random keys in hash map*/
  start_t=clock();
  int found_hm=0;
  for(int i=0; i<10000000; i++)
    (!has_key(hm, new_int(array_keys[i])))? : found_hm++;
  end_t=clock();
  total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;
  printf("\nFinding value in Hash Map required: %f sec\n", total_t); 

  /*searching random keys in array*/
  start_t=clock();
  int found_st_arr=0;
  for(int i=0; i<10000000; i++)
    (!bin_search(array, array_keys[i]))? : found_st_arr++;
  end_t=clock();
  total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;
  printf("\nFinding value in static allocated array required: %f sec\n", total_t); 

  /*result of searches*/
  printf("\nKeys found are equal? %s, number of found keys %d\n", found_hm==found_st_arr? "YES":"NO", found_hm);
}
  
  

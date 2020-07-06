#include "../include/sorting_lib.h" 
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_BUF_LEN 1024

typedef struct {
  int id;
  char* field1;
  int field2;
  float field3;
} Record;

char* str_copy(char* str){
  int lenStr = strlen(str);
  char* newStr = (char*)malloc(sizeof(char)*(lenStr+1));
  for(int i=0; i<lenStr;i++){
    newStr[i]=str[i];
  }
  newStr[lenStr+1]='\0';
  return newStr;
}

void print_err(int line) {
    printf("Error at line: %d\n", line);
    printf("sorting_lib_app  <filename> < 1 | 2 | 3 > < q | s >\n");
    printf("    1: sort according to the field1 ascending order\n");
    printf("    2: sort according to the field2 ascending order\n");
    printf("    3: sort according to the field3 ascending order\n");
    printf("    q: sort using quicksort\n");
    printf("    i: sort using insertionsort\n");
    printf("    csv must have following structure: <int>,<char*>,<int>,<float>\\n\n");
}

/*sort char* */
int sort_field_1(Record* rec1, Record* rec2) {
  return strcmp(rec1->field1, rec2->field1);
}

/*sort int */
int sort_field_2(Record* rec1, Record* rec2) {
    return  (rec1->field2 - rec2->field2);
}

/*sort float */
int sort_field_3(Record* rec1, Record* rec2) {
    float j = rec1->field3 - rec2->field3;
    if(j>0){
      return 1;
    }else if(j<0){
      return -1;
    }else{
      return 0;
    }
}

/*read input parameters and fill struct Pointer*/
Pointer* read_csv(char* filename, char* s_field){
  FILE* my_f = fopen(filename, "r");
  Pointer* p;

  if(my_f!=NULL){
    char line[MAX_BUF_LEN];
    p=(Pointer*)malloc(sizeof(Pointer));
    int j;
    int r;
    /*evaluate size of given file for malloc*/
    for (r=0;fgets(line, sizeof(line), my_f)!=NULL; r++); 
    rewind(my_f);
    p->array=(void**)malloc(sizeof(void*)*r);

    for (j=0;fgets(line, sizeof(line), my_f)!=NULL; j++){
      Record* record=(Record*)malloc(sizeof(Record));
      record->id = atoi(strtok(line, ","));
      record->field1 = str_copy(strtok(NULL, ","));
      record->field2 = atoi(strtok(NULL, ","));
      record->field3 = atof(strtok(NULL, "\n"));
      p->array[j]=record;
    }
    p->size=j;
   
    if(s_field[0]=='1'){
      p->compare=(PointerCmp)sort_field_1;
    } else if(s_field[0]=='2'){
      p->compare=(PointerCmp)sort_field_2;
    } else if(s_field[0]=='3'){
      p->compare=(PointerCmp)sort_field_3;
    } else { 
      print_err(__LINE__);
    }
  } else {
    print_err(__LINE__);
  }
  return p;
}

/*free struct Pointer*/
void Pointer_free(Pointer* p){
    free(p->array);
    free(p);
}

/*free Records data*/
void free_data(Pointer* p) {
    for(int i=0; i<p->size; ++i) {
        Record* rec = (Record*)p->array[i];
        free(rec->field1);
        free(rec);
    }
    Pointer_free(p);
}

/*write result of sorting in file*/
void print_array(Pointer* p){
  if(p!=NULL&&p->array!=NULL&&p->size>1){
    FILE* my_f=fopen("../../dataset/sorted_records.csv", "w");
    if( my_f==NULL ) {
      print_err(__LINE__);
      exit(1);
    }
    for(int i=0; i<p->size; i++){
      fprintf(my_f,"%d,%s,%d,%f\n", ((Record*)p->array[i])->id,\
        ((Record*)p->array[i])->field1,((Record*)p->array[i])->field2,((Record*)p->array[i])->field3);
    }
    fclose(my_f);
  }
}

int main(int argc, char *argv[]){

  if(argc!=4)
    print_err(__LINE__);
  
  Pointer* data = read_csv(argv[1], argv[2]);

  double total_t;
  printf("start\n");
  clock_t  start_t=clock(), end_t;
  
  if(*argv[3]=='q'){
    quick_sort(data);  
  }else if(*argv[3]=='i'){
    insertion_sort(data);
  }else{
    print_err(__LINE__);
  }
  
  end_t=clock();
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("stop, time: %f\n",total_t);
  print_array(data);
  return 0;
}

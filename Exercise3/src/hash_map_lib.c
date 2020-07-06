#include "../include/hash_map_lib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

HashMap* create_hash_map(HashFun hash_fun, CmpKeyFun key_fun){
  HashMap* hm=(HashMap*)malloc(sizeof(HashMap));
  hm->array = (struct Entry**)malloc(sizeof(struct Entry*)*DEFAULT_SIZE);
  hm->size = DEFAULT_SIZE;
  for(int i = 0; i<hm->size; i++){
    hm->array[i] = NULL;
  }
  hm->entry_number=0;
  hm->load_factor=DEFAULT_LOAD;
  hm->threshold=(int)(hm->size)*(hm->load_factor);
  hm->hashing =(HashFun)hash_fun;
  hm->eqk=(CmpKeyFun)key_fun;
  return hm;
}

HashMap* create_hash_map_custom(HashFun hash_fun, CmpKeyFun key_fun, int initial_size, float load_factor){
  HashMap* hm=(HashMap*)malloc(sizeof(HashMap));
  hm->entry_number=0;
  hm->size=initial_size;
  hm->array=(struct Entry**)malloc(sizeof(struct Entry*)*hm->size);
   for(int i = 0; i<hm->size; i++){
    hm->array[i] = NULL;
  }
  hm->load_factor=load_factor;
  hm->threshold=(int)(hm->size)*(hm->load_factor);
  hm->hashing=(HashFun)hash_fun;
  hm->eqk=(CmpKeyFun)key_fun;
  return hm;
}

void destroy_hash_map(HashMap* hm){
  if(hm!=NULL&&hm->array!=NULL){
    if(hm->entry_number!=0)
      delete_all_entry(hm);
    free(hm->array);
    hm->size=0;
    hm->entry_number=0;
    hm->load_factor=0;
    hm->threshold=0;
    free(hm);
  }
}

int is_empty(HashMap* hm){
  if(hm!=NULL){
    return hm->size==0;
  }
}

int entry_number(HashMap* hm){
  if(hm!=NULL&&hm->array!=NULL)
    return hm->entry_number;
}

/*recursive deleting of given entry list*/
void delete_entry_list(struct Entry* element){
  if(element->next!=NULL){
    delete_entry_list(element->next);
  } 
  free(element->key);
  free(element->val);
  free(element);
}

void delete_all_entry(HashMap* hm){
  if(hm!=NULL&&hm->array!=NULL){
    for(int i=0; i<hm->size; i++){
      if(hm->array[i]!=NULL) /*if index have at least one entry*/
        delete_entry_list(hm->array[i]); /*delete all entries in i position*/
    }
    hm->entry_number=0; /*update entries number*/
  }
}

int has_key(HashMap* hm, void* key){
  if(hm!=NULL&&key!=NULL&&hm->array!=NULL){
    int hash = hm->hashing(key);
    struct Entry* e=hm->array[hash];
    while(e!=NULL){ /*scan entire list*/
      if(hm->eqk(e->key, key)){ /*check if key are equal with function that compares keys*/
        return 1;
      }
      e=e->next;
    }
  }
  return 0;
}

void insert_entry_array(struct Entry** array, int hash, void* key, void* val){
  struct Entry* e=array[hash];
    while(e!=NULL && e->next!=NULL){ /*scanning untill last not-null element*/
      e=e->next;
    }
    struct Entry* new_entry=(struct Entry*)malloc(sizeof(struct Entry));
    new_entry->key = key;
    new_entry->val = val;
    new_entry->next=NULL;
    if(e!=NULL){
      e->next = new_entry;
    }else{ /*if target index doesn't have any entry yet*/
      array[hash]= new_entry;
    }
}

void rehash_map(HashMap* hm){
  int old_size = hm->size;
  int new_size =(REHASH_FACTOR*hm->size)+1;/*doubleing old size, adding one to change numerical parity*/
  struct Entry** new_array=(struct Entry**)malloc(sizeof(struct Entry*)*new_size);
  hm->size = new_size;
  for(int i=0; i<old_size; i++){/*copying element in new array*/
    struct Entry* e=hm->array[i];
    while(e!=NULL){/*scan entire list*/
      int hash = hm->hashing(e->key);
      insert_entry_array(new_array,hash, e->key, e->val);/*insert element in new array*/ 
      e=e->next;
    }
  }
  free(hm->array);/*free pointer to old array (non deleting elements)*/
  
  hm->threshold=(int)((hm->load_factor)*(hm->size));/*updating treshold*/
  hm->array=new_array;/*pointing to new array*/
}

void insert_entry(HashMap* hm, void* key, void* val){
  if(hm!=NULL && hm->array!=NULL){
    if((++hm->entry_number)>=hm->threshold){/*check if rehash is needed*/
      rehash_map(hm);
    }
    int hash =hm->hashing(key);
    insert_entry_array(hm->array, hash, key, val);/*insert element in hash map*/
  }
}

void* get_val(HashMap* hm, void* key){
  if(hm!=NULL&&key!=NULL&&hm->array!=NULL){
    int hash = hm->hashing(key);
    struct Entry* e=hm->array[hash];
    while(e!=NULL){/*scan entire list*/
      if(hm->eqk(e->key, key)){ /*check if key are equal with function that compares keys*/
        return e->val;
      }
      e=e->next;
    }
  }
  printf("Inexistent key:\n");
  return (void*)-1;
}

int delete_entry(HashMap* hm, void* key){
  int hash = hm->hashing(key);
  struct Entry* e = hm->array[hash], *e_prev;
  if(e!=NULL && hm->eqk(e->key, key)){ /*if target entry is the head of the list*/
    hm->array[hash]=hm->array[hash]->next;      
    free(e);      
    hm->entry_number-=1;
    return 1;
  }
  while(e!=NULL && !hm->eqk(e->key,key)){ /*scanning untill element has matching key*/
    e_prev=e;
    e=e->next;
  }
  if(e==NULL){ /*if target key has no matching entries*/
    return 0;
  }
  e_prev->next = e->next;
  free(e); /*freeing target entry*/
  hm->entry_number-=1;
  return 1;
}

void** get_keys(HashMap* hm){
  if(hm!=NULL&&hm->array!=NULL){
    void** key_array = (void**)malloc(hm->entry_number*sizeof(void*));
    for(int i = 0, j=0; i<hm->size; i++){
      struct Entry* e = hm->array[i];
      while(e!=NULL){ /*scan entire list*/
        key_array[j]=e->key;
        j++;
        e=e->next;
      }
    }
    return key_array;/*return array of existing keys in hash map*/
  }
}

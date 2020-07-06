#ifndef _HASH_MAP_LIB_
#define _HASH_MAP_LIB_

/*default values for HashMap*/
#define DEFAULT_SIZE 10
#define DEFAULT_LOAD 0.8
#define REHASH_FACTOR 2 

/*pointer to hashing function*/
typedef int (*HashFun)(void*);
/*pointer to key compare function*/
typedef int (*CmpKeyFun)(void*, void*);
/*list of entryes*/
struct Entry{
  void* key; /*value used by hashing function*/
  void* val; /*value stored in entry*/
  struct Entry* next; /*pointer to next Entry*/
};

typedef struct _HashMap{
  struct Entry** array; /*array of struct Entry*/
  int entry_number; /*present entries, including chaining*/
  int size; /*dimension of array*/
  float load_factor;  /*max filling percentage of  */
  int threshold; /*max entries number*/
  HashFun hashing; 
  CmpKeyFun eqk;
} HashMap;

/*hash map creation with default parameters*/
HashMap* create_hash_map(HashFun, CmpKeyFun);

/*hash map creation with custom parameters*/
HashMap* create_hash_map_custom(HashFun,CmpKeyFun, int, float);//con size definita dall'utente

/*free memory pointed by hash map*/
void destroy_hash_map(HashMap*);

/*check if hash map exist*/
int is_empty(HashMap*);

/*return number of present entries, including chaining*/
int entry_number(HashMap*);

/*delete all entries of hash map, without freeing memory*/
void delete_all_entry(HashMap*);

/*check if a key exist in hash map, return [exists==1 | !exists==0] */
int has_key(HashMap*, void*);

/*insert new entry*/
void insert_entry(HashMap*, void*, void*);

/*return value associated to a given key*/
void* get_val(HashMap*, void*);


/*return 1 and delete target entries if present, return 0 otherwise*/
int delete_entry(HashMap*, void*);

/*return pointer of all keys in hash map*/
void** get_keys(HashMap*);

#endif
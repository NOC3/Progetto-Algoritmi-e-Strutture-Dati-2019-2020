#include "../../Resources/C/Unity/unity.h"
#include "../include/hash_map_lib.h"
#include <stdlib.h>
#include <string.h>

int* size; /*global variable that point to hash map size*/

static int *new_int(int n)
{
  int *result = (int *)malloc(sizeof(int));
  *result = n;
  return result;
}

static int hashing_function(int *key)
{
  return *key % *size;
}

static int key_comparison(int *key1, int *key2)
{
  return *key1 - *key2 == 0 ? 1 : 0;
}

static void map_is_void()
{
  HashMap *hm = create_hash_map_custom((HashFun)hashing_function, (CmpKeyFun)key_comparison, 0, DEFAULT_LOAD);
  size=&(hm->size);
  TEST_ASSERT_EQUAL(1, is_empty(hm));
  destroy_hash_map(hm);
}

static void one_entry(){
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);
  int *key = new_int(3);
  size = &(hm->size);
  char* val= (char *)malloc(sizeof(char) * 6);
  strcpy(val, "valore");
  insert_entry(hm, key, val);
  TEST_ASSERT_EQUAL(1, hm->entry_number);
  TEST_ASSERT_EQUAL(DEFAULT_SIZE, hm->size);
  TEST_ASSERT_EQUAL(3, *(int *)hm->array[hashing_function(key)]->key);
  TEST_ASSERT_EQUAL_STRING(val, (char *)hm->array[hashing_function(key)]->val);
  destroy_hash_map(hm);
}

static void check_destroy(){
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);
  size = &(hm->size);
  for (int i = 0; i < 5; i++)
    insert_entry(hm, new_int(i), new_int(i * 2));
    
  destroy_hash_map(hm);
  for (int i = 0; i < 5; i++)
  {
    int has = has_key(hm, new_int(i));
    TEST_ASSERT_EQUAL(0, has);
  }
}

static void check_rehash(){
  int i;
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);
  size = &(hm->size);
  for (i = 0; i < 5; i++)
    insert_entry(hm, new_int(i), new_int(i * 2));

  for (i = 0; i < 5; i++)
  {
    TEST_ASSERT_EQUAL(1, has_key(hm, new_int(i)));
  }
  for (i = 5; i < 15; i++)
    insert_entry(hm, new_int(i), new_int(i * 2));

  for (i = 0; i < 15; i++)
    TEST_ASSERT_EQUAL(1, has_key(hm, new_int(i)));

  TEST_ASSERT_EQUAL(21, hm->size); //new size = (old_size*2)+1
  TEST_ASSERT_EQUAL(15, hm->entry_number);
  destroy_hash_map(hm);
}

static void check_key()
{
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);  
  size=&(hm->size);
  insert_entry(hm, new_int(1), new_int(2));
  insert_entry(hm, new_int(2), new_int(2));
  insert_entry(hm, new_int(3), new_int(2));
  TEST_ASSERT_EQUAL(1, has_key(hm, new_int(2)));
  TEST_ASSERT_EQUAL(0,has_key(hm, new_int(4)));
  destroy_hash_map(hm);
}

static void check_get_keys(){
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);
  size=&(hm->size);
  for(int i = 0; i<7; i++)
    insert_entry(hm, new_int(i), new_int(i*2));

  void** array = get_keys(hm);
  
  for(int i = 0; i<7; i++)
    TEST_ASSERT_EQUAL(i, *(int*)array[i]);

}

static void check_get_val(){
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);
  size = &(hm->size);
  char *str1= (char *)malloc(sizeof(char) * 8);
  strcpy(str1, "value 1");
  char *str2= (char *)malloc(sizeof(char) * 8);
  strcpy(str2, "value 2");
  insert_entry(hm, new_int(1), str1);
  insert_entry(hm, new_int(2), str2);
  TEST_ASSERT_EQUAL_STRING("value 2", (char*)get_val(hm,new_int(2)));
  destroy_hash_map(hm);
}

static void check_delete_entry(){
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);
  size=&(hm->size);
  insert_entry(hm, new_int(1), new_int(1));
  insert_entry(hm, new_int(2), new_int(2));
  insert_entry(hm, new_int(12), new_int(12));
  insert_entry(hm, new_int(3), new_int(3));

  TEST_ASSERT_EQUAL(1, has_key(hm, new_int(12)));
  delete_entry(hm, new_int(12)); 
  
  TEST_ASSERT_EQUAL(0, has_key(hm, new_int(12)));
  destroy_hash_map(hm);
}

static void check_delete_all_entry(){
  HashMap *hm = create_hash_map((HashFun)hashing_function, (CmpKeyFun)key_comparison);
  size = &(hm->size);
  insert_entry(hm, new_int(1), new_int(1));
  insert_entry(hm, new_int(2), new_int(2));
  insert_entry(hm, new_int(3), new_int(3));
  delete_all_entry(hm);
  for(int i = 0; i<3; i++)
    TEST_ASSERT_EQUAL(0, has_key(hm, new_int(i)));
  destroy_hash_map(hm);
}


int main()
{
  UNITY_BEGIN();

  RUN_TEST(map_is_void); //is_empty

  RUN_TEST(one_entry); //entry_number ==1

  RUN_TEST(check_destroy); //destroy_hash_map

  RUN_TEST(check_rehash); //check if reash works

  RUN_TEST(check_key); //check if has_key works

  RUN_TEST(check_get_val);//check if get_val works
              
  RUN_TEST(check_get_keys);//check if get_keys works
  
  RUN_TEST(check_delete_entry);//check if delete_entry works

  RUN_TEST(check_delete_all_entry);//check if delete_all_entry works

  UNITY_END();
}

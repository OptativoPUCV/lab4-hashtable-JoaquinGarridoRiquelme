#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  Pair *par = createPair(key, value);
  long pos = hash(key, map->capacity);
  
  while(map->buckets[pos % map->capacity] != NULL)
  {
    pos++;
  }
  map->buckets[pos % map-> capacity] = par;
  map->size++;
  map->current = pos % map->capacity;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *mapa = malloc(sizeof(HashMap));
  mapa-> buckets = (Pair**)calloc(capacity, sizeof(Pair*));
  mapa->capacity = capacity;
  mapa->current = -1;
  mapa->size = 0;
  return mapa;
}

void eraseMap(HashMap * map,  char * llave) 
{
  long pos = hash(llave, map -> capacity);
  while(true)
  {
    if(map->buckets[pos] == NULL) return ;
    if(strcmp(llave, map->buckets[pos]->key) == 0) break;
    pos++;
  }
  map->buckets[pos]->key = NULL;
  map->size--;
}

Pair * searchMap(HashMap * map,  char * llave) 
{   
  long pos = hash(llave, map->capacity);
  while(true)
  {
    if(map->buckets[pos] == NULL) return NULL;
    if(strcmp(llave, map->buckets[pos]->key) == 0) break;
    pos++;
  }
  map-> current = pos;
  return map->buckets[pos];
}

Pair * firstMap(HashMap * map) 
{
  for(size_t i = 0; i <= map-> capacity; i++)
  {
    if(map->buckets[i] != NULL && map->buckets[i]-> key != NULL)
    {
      map -> current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}

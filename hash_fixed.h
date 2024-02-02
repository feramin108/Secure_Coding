/**
*
* @Name : hash_fixed.h
*
**/
#ifndef HASH_H
#define HASH_H

#include <stddef.h>

#define KEY_STRING_MAX 255
#define MAP_MAX 128

typedef struct PairValue PairValue;

struct PairValue {
    char KeyName[KEY_STRING_MAX];
    int  ValueCount;
    PairValue* Next;
};

typedef struct {
    PairValue* data[MAP_MAX];
} HashMap;

HashMap* HashInit();
void HashAdd(HashMap* map, PairValue* value);
void HashDelete(HashMap* map, const char* key);
PairValue* HashFind(HashMap* map, const char* key);
void HashDump(HashMap* map);
void HashDestroy(HashMap* map);

#endif

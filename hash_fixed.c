/**
*
* @Name : hash_fixed.c
*
**/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_fixed.h"

unsigned HashIndex(const char* key) {
    unsigned sum = 0;
    for (const char* c = key; *c != '\0'; c++) {
        sum += *c;
    }
    return sum;
}

HashMap* HashInit() {
    return malloc(sizeof(HashMap));
}

void HashAdd(HashMap* map, PairValue* value) {
    unsigned idx = HashIndex(value->KeyName);

    PairValue* existing = HashFind(map, value->KeyName);
    if (existing) {
        // Key already exists, handle accordingly (update or return an error).
    } else {
        // Key doesn't exist, add the new value.
        value->Next = map->data[idx];
        map->data[idx] = value;
    }
}

PairValue* HashFind(HashMap* map, const char* key) {
    unsigned idx = HashIndex(key);

    for (PairValue* val = map->data[idx]; val != NULL; val = val->Next) {
        if (strcmp(val->KeyName, key) == 0)
            return val;
    }

    return NULL;
}

void HashDelete(HashMap* map, const char* key) {
    unsigned idx = HashIndex(key);

    for (PairValue* val = map->data[idx], *prev = NULL; val != NULL; prev = val, val = val->Next) {
        if (strcmp(val->KeyName, key) == 0) {
            if (prev)
                prev->Next = val->Next;
            else
                map->data[idx] = val->Next;
            free(val); // Free the memory allocated for the deleted value.
            return;
        }
    }
}

void HashDump(HashMap* map) {
    for (unsigned i = 0; i < MAP_MAX; i++) {
        for (PairValue* val = map->data[i]; val != NULL; val = val->Next) {
            printf("%s", val->KeyName);
        }
    }
}

void HashDestroy(HashMap* map) {
    for (unsigned i = 0; i < MAP_MAX; i++) {
        PairValue* current = map->data[i];
        while (current != NULL) {
            PairValue* next = current->Next;
            free(current);
            current = next;
        }
        map->data[i] = NULL;
    }
    free(map);
}

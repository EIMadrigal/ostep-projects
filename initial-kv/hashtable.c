#include "hashtable.h"

int hashcode(int key) {
    return (key % SIZE + SIZE) % SIZE;
}

struct KVPair* get(int key) {
    int index = hashcode(key);
    while (hashArray[index] != NULL) {
        if (hashArray[index]->key == key) {
            return hashArray[index];
        }
        ++index;
        index %= SIZE;
    }
    return NULL;
}

void insert(int key, char *val) {
    delete(key);
    struct KVPair *pair = (struct KVPair *)malloc(sizeof(struct KVPair)); 
    pair->key = key;
    pair->val = (char *)malloc(strlen(val) + 1);
    strcpy(pair->val, val);

    int index = hashcode(key);
    while (hashArray[index] != NULL) {
        ++index;
        index %= SIZE;
    }
    hashArray[index] = pair;
}

void delete(int key) {
    int index = hashcode(key);
    while (hashArray[index] != NULL) {
        if (hashArray[index]->key == key) {
            free(hashArray[index]->val);
            free(hashArray[index]);
            hashArray[index] = NULL;
            return;
        }
        ++index;
        index %= SIZE;
    }
}

void display() {
    for (int i = 0; i < SIZE; ++i) {
        if (hashArray[i] != NULL) {
            printf("%d,%s\n", hashArray[i]->key, hashArray[i]->val);
        }
    }
}

void clear() {
    for (int i = 0; i < SIZE; ++i) {
        if (hashArray[i] != NULL) {
            free(hashArray[i]->val);
            free(hashArray[i]);
            hashArray[i] = NULL;
        }
    }
}
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 5000

struct KVPair {
    int key;
    char* val;
};

extern struct KVPair* hashArray[SIZE];

int hashcode(int key);
struct KVPair* get(int key);
void insert(int key, char *val);
void delete(int key);
void display();
void clear();

#endif  /* HASHTABLE_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 7

int hash(int value) {
    return (value*value + 1)% TABLE_SIZE;
}

int search(int value, int* table, int* isDeleted) {
    // zwraca index
    int idx = hash(value);
    int beginIdx = idx;
    while (table[idx] != NULL) {
        if (table[idx] == value && !isDeleted[idx]) {
            return idx;
        }
        idx = (idx + 1) % TABLE_SIZE;
        if (idx == beginIdx)
            break;
    }
    return -1;
}

void insert(int value, int *table, int* isDeleted) {
    int idx = hash(value);
    int beginIdx = idx;
    while (table[idx] != NULL || isDeleted[idx]) {
        idx = (idx + 1) % TABLE_SIZE;
        if (idx == beginIdx)
            return;
    }
    table[idx] = value;
}

int main(void) {
    int table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
    int isDeleted[TABLE_SIZE];
    memset(isDeleted, 0, TABLE_SIZE*sizeof(int));
    insert(1, table, isDeleted);
    insert(2, table, isDeleted);
    insert(3, table, isDeleted);
    insert(5, table, isDeleted);
    insert(8, table, isDeleted);
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("%d\n", table[i]);
    printf("-------------------------\n");
    printf("%d\n", search(3, table, isDeleted));
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int intValue;
    char stringValue[50];
} Data;

typedef struct {
    Data* arr;
    int size;
    int capacity;
} DynamicArray;

DynamicArray new_array() {
    DynamicArray dynArray;
    dynArray.arr = NULL;
    dynArray.size = 0;
    dynArray.capacity = 0;
    return dynArray;
}


void extend(DynamicArray* dynArray) {
    int newCapacity = (dynArray->capacity == 0) ? 1 : dynArray->capacity * 2;
    dynArray->arr = realloc(dynArray->arr, newCapacity * sizeof(Data));

    if (dynArray->arr == NULL) {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }

    dynArray->capacity = newCapacity;
}

void add(DynamicArray* dynArray, int intValue, const char* stringValue) {
    if (dynArray->size == dynArray->capacity) {
        // If the array is full, double its size using extend()
        extend(dynArray);
    }

    dynArray->arr[dynArray->size].intValue = intValue;
    strncpy(dynArray->arr[dynArray->size].stringValue, stringValue, sizeof(dynArray->arr[dynArray->size].stringValue) - 1);
    dynArray->arr[dynArray->size].stringValue[sizeof(dynArray->arr[dynArray->size].stringValue) - 1] = '\0';

    dynArray->size++;
}

int search(const DynamicArray* dynArray, const char* target) {
    for (int i = 0; i < dynArray->size; ++i) {
        if (strcmp(dynArray->arr[i].stringValue, target) == 0) {
            return dynArray->arr[i].intValue;
        }
    }
    
    printf("Error while interpreting: trying to access the type value of an undeclared variable '%s'.", target);
    exit(0);
}

void print_array(const DynamicArray* dynArray) {
    for (int i = 0; i < dynArray->size; ++i) {
        printf("%i - (%d, %s)\n", i, dynArray->arr[i].intValue, dynArray->arr[i].stringValue);
    }
    printf("\n");
}
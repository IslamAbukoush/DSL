#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float floatValue;
    char stringValue[50];
} FloatData;

typedef struct {
    FloatData* arr;
    int size;
    int capacity;
} DynamicArrayFloat;

DynamicArrayFloat float_new_array() {
    DynamicArrayFloat dynArray;
    dynArray.arr = NULL;
    dynArray.size = 0;
    dynArray.capacity = 0;
    return dynArray;
}

void float_extend(DynamicArrayFloat* dynArray) {
    int newCapacity = (dynArray->capacity == 0) ? 1 : dynArray->capacity * 2;
    dynArray->arr = realloc(dynArray->arr, newCapacity * sizeof(FloatData));

    if (dynArray->arr == NULL) {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }

    dynArray->capacity = newCapacity;
}

void float_add(DynamicArrayFloat* dynArray, float floatValue, const char* stringValue) {
    for (int i = 0; i < dynArray->size; ++i) {
        if (strcmp(dynArray->arr[i].stringValue, stringValue) == 0) {
            printf("Error while interpreting: Variable '%s' has already been declared.\n", stringValue);
            exit(0);
        }
    }

    if (dynArray->size == dynArray->capacity) {
        float_extend(dynArray);
    }

    dynArray->arr[dynArray->size].floatValue = floatValue;
    strncpy(dynArray->arr[dynArray->size].stringValue, stringValue, sizeof(dynArray->arr[dynArray->size].stringValue) - 1);
    dynArray->arr[dynArray->size].stringValue[sizeof(dynArray->arr[dynArray->size].stringValue) - 1] = '\0';

    dynArray->size++;
}

float float_search(const DynamicArrayFloat* dynArray, const char* target) {
    for (int i = 0; i < dynArray->size; ++i) {
        if (strcmp(dynArray->arr[i].stringValue, target) == 0) {
            return dynArray->arr[i].floatValue;
        }
    }
    
    printf("Error while interpreting: trying to access the value of an undeclared variable '%s'.", target);
    exit(0);
}

void float_modify(DynamicArrayFloat* dynArray, const char* target, float floatValue) {
    for (int i = 0; i < dynArray->size; ++i) {
        if (strcmp(dynArray->arr[i].stringValue, target) == 0) {
            dynArray->arr[i].floatValue = floatValue;
            return;
        }
    }

    printf("Error while interpreting: trying to modify the value of an undeclared variable '%s'.", target);
    exit(0);
}

void float_print_array(const DynamicArrayFloat* dynArray) {
    for (int i = 0; i < dynArray->size; ++i) {
        printf("%i - (%f, %s)\n", i, dynArray->arr[i].floatValue, dynArray->arr[i].stringValue);
    }
    printf("\n");
}

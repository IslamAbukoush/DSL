#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

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

DynamicArray new_array();
void add(DynamicArray* dynArray, int intValue, const char* stringValue);
void extend(DynamicArray* dynArray);
int search(const DynamicArray* dynArray, const char* target);
void print_array(const DynamicArray* dynArray);

#endif
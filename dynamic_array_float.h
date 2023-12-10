#ifndef DYNAMIC_ARRAY_FLOAT_H
#define DYNAMIC_ARRAY_FLOAT_H

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

DynamicArrayFloat float_new_array();
void float_extend(DynamicArrayFloat* dynArray);
void float_add(DynamicArrayFloat* dynArray, float floatValue, const char* stringValue);
void float_print_array(const DynamicArrayFloat* dynArray);
float float_search(const DynamicArrayFloat* dynArray, const char* target);
void float_modify(DynamicArrayFloat* dynArray, const char* target, float floatValue);

#endif
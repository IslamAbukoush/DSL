#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lexer.h"
#include "parser.h"
#include "dynamic_array_float.h"
#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float str_to_float(char* str);
int str_to_int(char* str);
float interpret_math(TreeNode* AST);
float interpret_print(TreeNode* AST);
void add_new_var(char* id, float value, int type);
void interpret_declare(TreeNode* AST);
void interpret_var_mod(TreeNode* AST);
float base_interpret(TreeNode* AST);
void interpret(TreeNode* AST, DynamicArrayFloat* GLOBAL_VARIABLES_arg, DynamicArray* GLOBAL_VARIABLES_TYPES_arg);

#endif
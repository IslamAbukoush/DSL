#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <string.h>

typedef struct TreeNode {
    int type;
    char value[50];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* new_node(int type, char* value);
TreeNode* parse_expression(DynamicArray tokens, int start, int end, int* ptr);
TreeNode* parse_binary(DynamicArray tokens, int start, int end, int* ptr);
TreeNode* parse_add_sub(DynamicArray tokens, int start, int end, int* ptr);
TreeNode* parse_mult_div(DynamicArray tokens, int start, int end, int* ptr);
TreeNode* parse_expo(DynamicArray tokens, int start, int end, int* ptr);
TreeNode* parse_factor(DynamicArray tokens, int start, int end, int* ptr);
void print_ast(TreeNode* root, int depth, char* s);
void free_ast(TreeNode* root);
TreeNode* parse_if_while_statement(DynamicArray tokens, int start, int end, int if_or_while, int* ptr);
TreeNode* parse_print(DynamicArray tokens, int start, int end, int* ptr);
TreeNode* parse_declaration(DynamicArray tokens, int start, int end, int type, int* ptr);
TreeNode* parse_assignment(DynamicArray tokens, int start, int end, int type, int* ptr);
int is_end(int type);
TreeNode* parse_code(DynamicArray tokens, int start, int end, TreeNode* right);
TreeNode* parse(DynamicArray tokens);

#endif
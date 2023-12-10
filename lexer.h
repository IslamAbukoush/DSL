#ifndef LEXER_H
#define LEXER_H

#include "dynamic_array.h"

enum Token_Type {
    DECLARE_INT,
    DECLARE_FLOAT,
    ASSIGN,
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    RAISE,
    DIVIDE,
    CMP_MORE,
    CMP_LESS,
    CMP_MORE_EQUAL,
    CMP_LESS_EQUAL,
    CMP_EQL,
    CMP_NOT_EQUAL,
    CMP_NOT,
    IF,
    WHILE,
    PRINT,
    SEMICOLON,
    ID,
    END,
    L_PAREN,
    R_PAREN,
    L_CURLY,
    R_CURLY,
    EXECUTE,
    NEW_LINE,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MULT_ASSIGN,
    DIV_ASSIGN,
    AND,
    OR
};

int is_alpha(char ch);
int is_numeric(char ch);
int are_same(const char* str1, const char* str2);
int str_is_num(const char* str);
int str_is_identifier(const char* str);
DynamicArray separate(char* sourceCode);
DynamicArray identify(DynamicArray array);
DynamicArray lex(char* sourceCode);

#endif
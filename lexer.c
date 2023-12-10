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

int is_alpha(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int is_numeric(char ch) {
    return ch >= '0' && ch <= '9';
}

int are_same(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return 0;
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

int str_is_num(const char* str) {
    int dotCount = 0;

    while (*str != '\0') {
        if (!is_numeric(*str)) {
            if (*str == '.' && dotCount < 1) {
                dotCount++;
            } else {
                return 0;
            }
        }
        str++;
    }

    return 1;
}

int str_is_identifier(const char* str) {
    if (!str || !is_alpha(*str)) {
        // If the string is NULL or doesn't start with an alphabetic character
        return 0;
    }

    while (*str != '\0') {
        if (!(is_alpha(*str) || is_numeric(*str) || *str == '_')) {
            return 0;
        }
        str++;
    }
    return 1;
}

DynamicArray separate(char* sourceCode) {
    DynamicArray tokens = new_array();
    int src_idx = 0;

    while(sourceCode[src_idx] != '\0') {
        char token[50];
        memset(token, 0, 50);
        int token_idx = 0;

        while(sourceCode[src_idx] == ' ') {
            src_idx++;
        }

        if(is_alpha(sourceCode[src_idx])) {
            while(is_alpha(sourceCode[src_idx]) || is_numeric(sourceCode[src_idx])) {
                token[token_idx++] = sourceCode[src_idx++];
            }
        }

        else if((is_numeric(sourceCode[src_idx]) || sourceCode[src_idx] == '.') && sourceCode[src_idx] != ' ') {
            while(is_numeric(sourceCode[src_idx]) || sourceCode[src_idx] == '.' || is_alpha(sourceCode[src_idx])) {
                token[token_idx++] = sourceCode[src_idx++];
            }
        }

        // other cases
        else {
            if(sourceCode[src_idx] == '=' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '=';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '>' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '>';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '<' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '<';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '!' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '!';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '+' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '+';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '-' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '-';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '*' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '*';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '/' && sourceCode[src_idx+1] == '=') {
                token[token_idx++] = '/';
                token[token_idx++] = '=';
                src_idx++;
            }
            else if(sourceCode[src_idx] == '/' && sourceCode[src_idx+1] == '/') {
                while(sourceCode[++src_idx] != '\n' && sourceCode[src_idx] != '\0');
                src_idx--;
            }
            else {
                token[token_idx] = sourceCode[src_idx];
            }
            if(sourceCode[src_idx] != '\0') {
                src_idx++;
            }
        }
        if(strlen(token)) {
            add(&tokens, -1, token);
        }
    }
    return tokens;
}

DynamicArray identify(DynamicArray array) {
    for(int i = 0; i < array.size; i++) {
        if(are_same(array.arr[i].stringValue, "int")) {
            array.arr[i].intValue = DECLARE_INT;
        } else if(are_same(array.arr[i].stringValue, "float")) {
            array.arr[i].intValue = DECLARE_FLOAT;
        } else if(are_same(array.arr[i].stringValue, "=")) {
            array.arr[i].intValue = ASSIGN;
        } else if(are_same(array.arr[i].stringValue, "+")) {
            array.arr[i].intValue = PLUS;
        } else if(are_same(array.arr[i].stringValue, "-")) {
            array.arr[i].intValue = MINUS;
        } else if(are_same(array.arr[i].stringValue, "*")) {
            array.arr[i].intValue = MULTIPLY;
        } else if(are_same(array.arr[i].stringValue, "^")) {
            array.arr[i].intValue = RAISE;
        } else if(are_same(array.arr[i].stringValue, "/")) {
            array.arr[i].intValue = DIVIDE;
        } else if(are_same(array.arr[i].stringValue, ">")) {
            array.arr[i].intValue = CMP_MORE;
        } else if(are_same(array.arr[i].stringValue, "<")) {
            array.arr[i].intValue = CMP_LESS;
        } else if(are_same(array.arr[i].stringValue, ">=")) {
            array.arr[i].intValue = CMP_MORE_EQUAL;
        } else if(are_same(array.arr[i].stringValue, "<=")) {
            array.arr[i].intValue = CMP_LESS_EQUAL;
        } else if(are_same(array.arr[i].stringValue, "==")) {
            array.arr[i].intValue = CMP_EQL;
        } else if(are_same(array.arr[i].stringValue, "!=")) {
            array.arr[i].intValue = CMP_NOT_EQUAL;
        } else if(are_same(array.arr[i].stringValue, "+=")) {
            array.arr[i].intValue = ADD_ASSIGN;
        } else if(are_same(array.arr[i].stringValue, "-=")) {
            array.arr[i].intValue = SUB_ASSIGN;
        } else if(are_same(array.arr[i].stringValue, "*=")) {
            array.arr[i].intValue = MULT_ASSIGN;
        } else if(are_same(array.arr[i].stringValue, "/=")) {
            array.arr[i].intValue = DIV_ASSIGN;
        } else if(are_same(array.arr[i].stringValue, "!")) {
            array.arr[i].intValue = CMP_NOT;
        } else if(are_same(array.arr[i].stringValue, "(")) {
            array.arr[i].intValue = L_PAREN;
        } else if(are_same(array.arr[i].stringValue, ")")) {
            array.arr[i].intValue = R_PAREN;
        } else if(are_same(array.arr[i].stringValue, "{")) {
            array.arr[i].intValue = L_CURLY;
        } else if(are_same(array.arr[i].stringValue, "}")) {
            array.arr[i].intValue = R_CURLY;
        } else if(are_same(array.arr[i].stringValue, "if")) {
            array.arr[i].intValue = IF;
        } else if(are_same(array.arr[i].stringValue, "while")) {
            array.arr[i].intValue = WHILE;
        } else if(are_same(array.arr[i].stringValue, "print")) {
            array.arr[i].intValue = PRINT;
        } else if(are_same(array.arr[i].stringValue, "and")) {
            array.arr[i].intValue = AND;
        } else if(are_same(array.arr[i].stringValue, "or")) {
            array.arr[i].intValue = OR;
        } else if(are_same(array.arr[i].stringValue, ";")) {
            array.arr[i].intValue = SEMICOLON;
        } else if(are_same(array.arr[i].stringValue, "\n")) {
            array.arr[i].intValue = NEW_LINE;
        } else if(str_is_num(array.arr[i].stringValue)) {
            array.arr[i].intValue = NUMBER;
        } else if(str_is_identifier(array.arr[i].stringValue)) {
            array.arr[i].intValue = ID;
        } else {
            printf("Error while lexing: Invalid token: \"%s\"", array.arr[i].stringValue);
            exit(0);
        }
    }
    add(&array, END, "END");
    return array;
}

DynamicArray lex(char* sourceCode) {
    DynamicArray tokens = separate(sourceCode);
    tokens = identify(tokens);
    return tokens;
}
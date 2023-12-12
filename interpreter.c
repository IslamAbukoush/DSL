#include "lexer.h"
#include "parser.h"
#include "dynamic_array_float.h"
#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

DynamicArrayFloat* GLOBAL_VARIABLES;
DynamicArray* GLOBAL_VARIABLES_TYPES;

float str_to_float(char* str);
int str_to_int(char* str);
float interpret_math(TreeNode* AST);
float interpret_print(TreeNode* AST);
void add_new_var(char* id, float value, int type);
void interpret_declare(TreeNode* AST);
void interpret_var_mod(TreeNode* AST);
float base_interpret(TreeNode* AST);
void interpret(TreeNode* AST, DynamicArrayFloat* GLOBAL_VARIABLES_arg, DynamicArray* GLOBAL_VARIABLES_TYPES_arg);

float str_to_float(char* str) {
    char *endptr;
    float floatValue = strtof(str, &endptr);
    if (*endptr != '\0') {
        printf("Conversion error: Not a valid float '%s'\n", str);
        exit(0);
    } else {
        return floatValue;
    }
}

int str_to_int(char* str) {
    char *endptr;
    float floatValue = strtol(str, &endptr, 10);
    if (*endptr != '\0') {
        printf("Conversion error: Not a valid float '%s'\n", str);
        exit(0);
    } else {
        return floatValue;
    }
}

float interpret_math(TreeNode* AST) {
    float initial_value = 0;
    float left;
    float right;
    if(AST->left == NULL) {
        left = 0;
        if(AST->type != PLUS && AST->type != MINUS) {
            printf("Error while interpreting: left operand missing in the folowing operation '%s'.", AST->value);
            exit(0);
        }
    } else {
        left = base_interpret(AST->left);
    }
    if(AST->right == NULL) {
        printf("Error while interpreting: right operand missing in the folowing operation '%s'.", AST->value);
        exit(0);
    } else {
        right = base_interpret(AST->right);
    }
    float result;
    switch (AST->type) {
    case PLUS:
        result = left + right;
        break;
    case MINUS:
        result = left - right;
        break;
    case MULTIPLY:
        result = left * right;
        break;
    case DIVIDE:
        if (right == 0) {
            printf("Error while interpreting: division by zero.");
            exit(0);
        }
        result = left / right;
        break;
    case CMP_EQL:
        result = left == right;
        break;
    case CMP_LESS:
        result = left < right;
        break;
    case CMP_LESS_EQUAL:
        result = left <= right;
        break;
    case CMP_MORE:
        result = left > right;
        break;
    case CMP_MORE_EQUAL:
        result = left >= right;
        break;
    case CMP_NOT_EQUAL:
        result = left != right;
        break;
    case AND:
        result = left && right;
        break;
    case OR:
        result = left || right;
        break;
    case RAISE:
        if (right == 0 && left == 0) {
            printf("Error while interpreting: zero to the power of zero.");
            exit(0);
        }
        result = pow(left, right);
        break;
    default:
        printf("Error while interpreting: attempt to use an undefined operation: '%s'.", AST->value);
        exit(0);
        break;
}
    return result;
}

float interpret_print(TreeNode* AST) {
    float result = base_interpret(AST->left);
    int truncated = result;
    if(result == truncated) {
        printf("Output: %d\n", truncated);
    } else {
        printf("Output: %f\n", result);
    }
    return result;
}

void add_new_var(char* id, float value, int type) {
    float_add(GLOBAL_VARIABLES, value, id);
    add(GLOBAL_VARIABLES_TYPES, type, id);
}

void interpret_declare(TreeNode* AST) {
    float result = 0;
    if(AST->right != NULL) {
        result = base_interpret(AST->right);
        result = AST->type == DECLARE_INT ? truncf(result) : result;
    }
    add_new_var(AST->left->value, result, AST->type);
}

void interpret_var_mod(TreeNode* AST) {
    float result = base_interpret(AST->right);
    int is_int = search(GLOBAL_VARIABLES_TYPES, AST->left->value) == DECLARE_INT;
    float old = float_search(GLOBAL_VARIABLES, AST->left->value);

    switch (AST->type) {
        case ASSIGN:
            break;
        case ADD_ASSIGN:
            result = old + result;
            break;
        case SUB_ASSIGN:
            result = old - result;
            break;
        case MULT_ASSIGN:
            result = old * result;
            break;
        case DIV_ASSIGN:
            result = old / result;
            break;
        default:
            printf("Error while interpreting: the assignment operator '%s' is not defined.", AST->value);
            exit(0);
    }
    result = is_int ? truncf(result) : result;
    float_modify(GLOBAL_VARIABLES, AST->left->value,  result);
}

float ask_for_input() {
    float number;
    int validInput;

    printf("Input: ");
    validInput = scanf("%f", &number);
    if(validInput == 1) {
        return number;
    }
    if (validInput == 0) {
        printf("Input error: invalid input format.\n");
        exit(0);
    } else {
        printf("Input error: input failure or end-of-file reached.\n");
        exit(0);
    }
}

float base_interpret(TreeNode* AST) {
    if(AST == NULL) return 0;
    switch (AST->type) {
        case EXECUTE:
            if (AST->right != NULL) {
                base_interpret(AST->right);
            }
            if (AST->left != NULL) {
                base_interpret(AST->left);
            }
            break;
        case PRINT:
            return interpret_print(AST);
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE:
        case CMP_EQL:
        case CMP_LESS:
        case CMP_LESS_EQUAL:
        case CMP_MORE:
        case CMP_MORE_EQUAL:
        case CMP_NOT_EQUAL:
        case RAISE:
        case OR:
        case AND:
            return interpret_math(AST);
        case NUMBER:
            return str_to_float(AST->value);
        case ID:
            return float_search(GLOBAL_VARIABLES, AST->value);
        case INPUT:
            return ask_for_input();
        case IF:
            if (base_interpret(AST->left)) {
                if(AST->right != NULL) {
                    base_interpret(AST->right);
                }
            }
            break;
        case WHILE:
            while (base_interpret(AST->left)) {
                if(AST->right != NULL) {
                    base_interpret(AST->right);
                }
            }
            break;
        case DECLARE_FLOAT:
        case DECLARE_INT:
            interpret_declare(AST);
            break;
        case ASSIGN:
        case ADD_ASSIGN:
        case SUB_ASSIGN:
        case MULT_ASSIGN:
        case DIV_ASSIGN:
            interpret_var_mod(AST);
            break;
        default:
            printf("Error while interpreting: unknown operation '%s'.", AST->value);
            exit(0);
    }
    return 0;
}

void interpret(TreeNode* AST, DynamicArrayFloat* GLOBAL_VARIABLES_arg, DynamicArray* GLOBAL_VARIABLES_TYPES_arg) {
    GLOBAL_VARIABLES = GLOBAL_VARIABLES_arg;
    GLOBAL_VARIABLES_TYPES = GLOBAL_VARIABLES_TYPES_arg;
    base_interpret(AST);
}

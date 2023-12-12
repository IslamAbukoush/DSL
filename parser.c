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

TreeNode* new_node(int type, char* value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = type;
    strcpy(node->value, value);
    node->left  = NULL;
    node->right = NULL;
    return node;
}

TreeNode* parse_expression(DynamicArray tokens, int start, int end, int* ptr) {
    int b_count = 0;
    for(int i = end; i >= start; i--) {
        int type = tokens.arr[i].intValue;
        char* value = tokens.arr[i].stringValue;
        if(type == L_PAREN) {
            b_count++;
        } else if(type == R_PAREN) {
            b_count--;
        }
        if((type == AND || type ==  OR) && b_count == 0) {
            TreeNode* root = new_node(type, value);
            root->right = parse_binary(tokens, i+1, end, ptr);
            root->left = parse_expression(tokens, start, i-1, ptr);
            return root;
        } else if(!(
            type == NUMBER ||
            type == ID || 
            type == L_PAREN || 
            type == R_PAREN || 
            type == PLUS || 
            type == MULTIPLY || 
            type == MINUS || 
            type == DIVIDE || 
            type == RAISE || 
            type == CMP_EQL || 
            type ==  CMP_NOT_EQUAL || 
            type == CMP_LESS || 
            type ==  CMP_LESS_EQUAL || 
            type == CMP_MORE || 
            type ==  CMP_MORE_EQUAL || 
            type == OR || 
            type == INPUT || 
            type == AND)) {
            printf("Error while parsing: unexpected token in an expression '%s' .", value);
            exit(0);
        }
    }
    if(b_count < 0) {
        printf("Error while parsing: opening bracket not found...");
        exit(0);
    } else if(b_count > 0) {
        printf("Error while parsing: closing bracket not found...");
        exit(0);
    }
    return parse_binary(tokens, start, end, ptr);
}

TreeNode* parse_binary(DynamicArray tokens, int start, int end, int* ptr) {
    int b_count = 0;
    for(int i = end; i >= start; i--) {
        int type = tokens.arr[i].intValue;
        char* value = tokens.arr[i].stringValue;
        if(type == L_PAREN) {
            b_count++;
        } else if(type == R_PAREN) {
            b_count--;
        }
        if((type == CMP_EQL || type ==  CMP_NOT_EQUAL || type == CMP_LESS || type ==  CMP_LESS_EQUAL || type == CMP_MORE || type ==  CMP_MORE_EQUAL) && b_count == 0) {
            TreeNode* root = new_node(type, value);
            root->right = parse_add_sub(tokens, i+1, end, ptr);
            root->left = parse_binary(tokens, start, i-1, ptr);
            return root;
        }
    }
    if(b_count < 0) {
        printf("Error while parsing: opening bracket not found...");
        exit(0);
    } else if(b_count > 0) {
        printf("Error while parsing: closing bracket not found...");
        exit(0);
    }
    return parse_add_sub(tokens, start, end, ptr);
}

TreeNode* parse_add_sub(DynamicArray tokens, int start, int end, int* ptr) {
    int b_count = 0;
    for(int i = end; i >= start; i--) {
        int type = tokens.arr[i].intValue;
        char* value = tokens.arr[i].stringValue;
        if(type == L_PAREN) {
            b_count++;
        } else if(type == R_PAREN) {
            b_count--;
        }
        if((type == PLUS || type ==  MINUS) && b_count == 0) {
            TreeNode* root = new_node(type, value);
            root->right = parse_mult_div(tokens, i+1, end, ptr);
            if(start <= i-1) {
                root->left = parse_add_sub(tokens, start, i-1, ptr);
            }
            return root;
        }
    }
    if(b_count < 0) {
        printf("Error while parsing: opening bracket not found...");
        exit(0);
    } else if(b_count > 0) {
        printf("Error while parsing: closing bracket not found...");
        exit(0);
    }
    return parse_mult_div(tokens, start, end, ptr);
}

TreeNode* parse_mult_div(DynamicArray tokens, int start, int end, int* ptr) {
    int b_count = 0;
    for(int i = end; i >= start; i--) {
        int type = tokens.arr[i].intValue;
        char* value = tokens.arr[i].stringValue;
        if(type == L_PAREN) {
            b_count++;
        } else if(type == R_PAREN) {
            b_count--;
        }
        if((type == MULTIPLY || type ==  DIVIDE) && b_count == 0) {
            TreeNode* root = new_node(type, value);
            root->right = parse_expo(tokens, i+1, end, ptr);
            root->left = parse_mult_div(tokens, start, i-1, ptr);
            return root;
        }
    }
    if(b_count < 0) {
        printf("Error while parsing: opening bracket not found...");
        exit(0);
    } else if(b_count > 0) {
        printf("Error while parsing: closing bracket not found...");
        exit(0);
    }
    return parse_expo(tokens, start, end, ptr);
}

TreeNode* parse_expo(DynamicArray tokens, int start, int end, int* ptr) {
    int b_count = 0;
    for(int i = end; i >= start; i--) {
        int type = tokens.arr[i].intValue;
        char* value = tokens.arr[i].stringValue;
        if(type == L_PAREN) {
            b_count++;
        } else if(type == R_PAREN) {
            b_count--;
        }
        if(type == RAISE && b_count == 0) {
            TreeNode* root = new_node(type, value);
            root->right = parse_factor(tokens, i+1, end, ptr);
            root->left = parse_expo(tokens, start, i-1, ptr);
            return root;
        }
    }
    if(b_count < 0) {
        printf("Error while parsing: opening bracket not found...");
        exit(0);
    } else if(b_count > 0) {
        printf("Error while parsing: closing bracket not found...");
        exit(0);
    }
    return parse_factor(tokens, start, end, ptr);
}

TreeNode* parse_factor(DynamicArray tokens, int start, int end, int* ptr) {
    if(start == end) {
        int type = tokens.arr[start].intValue;
        if(type == NUMBER) {
            TreeNode* num = new_node(NUMBER, tokens.arr[start].stringValue);
            return num;
        } else if(type == ID) {
            TreeNode* id = new_node(ID, tokens.arr[start].stringValue);
            return id;
        } else if(type == INPUT) {
            TreeNode* input = new_node(INPUT, "input");
            return input;
        } else {
            printf("Error while parsing: this token does not make sense in the current context '%s'.", tokens.arr[start].stringValue);
            exit(0);
        }
    } else if(start < end) {
        int first = tokens.arr[start].intValue;
        int last = tokens.arr[end].intValue;
        if(first == L_PAREN && last == R_PAREN) {
            return parse_expression(tokens, start + 1, end - 1, ptr);
        } else {
            printf("Error while parsing: invalid expression, starts at %i, ends at %i, try adding operators in between values.", start, end);
            exit(0);
        }
    } else {
        return NULL;
    }
}


void print_ast(TreeNode* root, int depth, char* s) {
    if (root == NULL) return;
    for(int i = 0; i < depth*6; i++) {
        printf(" ");
    }
    printf("%s: %s\n", s, root->value);
    print_ast(root->right, depth+1, "Right node");
    print_ast(root->left, depth+1, "Left  node");
}

void free_ast(TreeNode* root) {
    if (root != NULL) {
        free_ast(root->left);
        free_ast(root->right);
        free(root);
    }
}

TreeNode* parse_if_while_statement(DynamicArray tokens, int start, int end, int if_or_while, int* ptr) {
    start = *ptr + 1;
    if(tokens.arr[start].intValue != L_PAREN) {
        if(if_or_while == IF) {
            printf("Error while parsing: if statement should be followed by a left bracket.");
        } else {
            printf("Error while parsing: while statement should be followed by a left bracket.");
        }
        exit(0);
    }
    int i = start+1;
    int b_count = 1;
    while(b_count != 0) {
        if(tokens.arr[i].intValue == L_PAREN) {
            b_count++;
        } else if(tokens.arr[i].intValue == R_PAREN) {
            b_count--;
        } else if(tokens.arr[i].intValue == END) {
            printf("\nError while parsing: closing bracket for condition not found.");
            exit(0);
        }
        i++;
    }
    int cond_start = start + 1;
    int cond_end = i - 2;
    if(cond_start > cond_end) {
        if(if_or_while == IF) {
            printf("\nError while parsing: no condition provided to the if statement.");
        } else {
            printf("\nError while parsing: no condition provided to the while statement.");
        }
        exit(0);
    }

    TreeNode* condition = parse_expression(tokens, cond_start, cond_end, ptr);
    if(tokens.arr[i].intValue != L_CURLY) {
        if(if_or_while == IF) {
            printf("Error while parsing: the condition in if statement should be followed by a left curly bracket.");
        } else {
            printf("Error while parsing: the condition in while statement should be followed by a left curly bracket.");
        }
        exit(0);
    }

    b_count = 1;
    int j = i + 2;
    while(b_count != 0) {
        if(tokens.arr[j].intValue == L_CURLY) {
            b_count++;
        } else if(tokens.arr[j].intValue == R_CURLY) {
            b_count--;
        } else if(tokens.arr[j].intValue == END) {
            if(if_or_while == IF) {
                printf("\nError while parsing: closing curly bracket for if statement not found.");
            } else {
                printf("\nError while parsing: closing curly bracket for while statement not found.");
            }
            exit(0);
        }
        j++;
    }
    int stat_start = i + 1;
    int stat_end = j - 2;
    TreeNode* statement = parse_code(tokens,stat_start, stat_end, NULL);
    TreeNode* node;
    if(if_or_while == IF) {
        node = new_node(IF, "if");
    } else {
        node = new_node(WHILE, "while");
    }
    node->left = condition;
    node->right = statement;
    *ptr = j;
    return node;
}

TreeNode* parse_print(DynamicArray tokens, int start, int end, int* ptr) {
    start = *ptr + 1;
    if(tokens.arr[start].intValue != L_PAREN) {
        printf("Error while parsing: print function call should have an opening bracket.");
        exit(0);
    }
    int b_count = 1;
    int i = start + 1;
    while(b_count != 0) {
        if(tokens.arr[i].intValue == L_PAREN) {
            b_count++;
        } else if(tokens.arr[i].intValue == R_PAREN) {
            b_count--;
        } else if(tokens.arr[i].intValue == END) {
            printf("\nError while parsing: closing bracket for print function was not found.");
            exit(0);
        }
        i++;
    }
    int exp_start = start + 1;
    int exp_end = i - 2;
    TreeNode* exp;
    if(exp_start > exp_end) {
        exp = NULL;
    } else {
        exp= parse_expression(tokens, exp_start, exp_end, ptr);
    }
    TreeNode* print_node = new_node(PRINT, "print");
    print_node->left = exp;
    *ptr = i;
    return print_node;
}

TreeNode* parse_exit(DynamicArray tokens, int start, int end, int* ptr) {
    start = *ptr + 1;
    if(tokens.arr[start].intValue != L_PAREN) {
        printf("Error while parsing: exit function call should have an opening bracket.");
        exit(0);
    }
    if(tokens.arr[start+1].intValue != R_PAREN) {
        printf("\nError while parsing: closing bracket for exit function was not found.");
        exit(0);
    }
    TreeNode* exit_node = new_node(EXIT, "exit");
    *ptr = start+3;
    return exit_node;
}

TreeNode* parse_declaration(DynamicArray tokens, int start, int end, int type, int* ptr) {
    if(tokens.arr[start+1].intValue != ID) {
        printf("Error while parsing: declaration statement must be followed by a variable name, instead got '%s'", tokens.arr[start+1].stringValue);
        exit(0);
    }
    TreeNode* id_node = new_node(ID, tokens.arr[start+1].stringValue);
    TreeNode* dec_node = new_node(type, tokens.arr[start].stringValue);
    dec_node->left = id_node;
    if(tokens.arr[start+2].intValue == ASSIGN) {
        if(start+3 > end) {
            printf("Error while parsing: variabe assignment '=' must be followed by an expression, instead got '%s'", tokens.arr[start+3].stringValue);
            exit(0);
        }
        TreeNode* exp_node = parse_expression(tokens, start+3, end, NULL);
        dec_node->right = exp_node;
        return dec_node;
    }
    return dec_node;
}

TreeNode* parse_assignment(DynamicArray tokens, int start, int end, int type, int* ptr) {
    TreeNode* id_node = new_node(ID, tokens.arr[start].stringValue);
    TreeNode* assign_node = new_node(ASSIGN, "=");
    assign_node->left = id_node;
    if(start+2 > end) {
        printf("Error while parsing: variabe assignment '=' must be followed by an expression, instead got '%s'", tokens.arr[start+2].stringValue);
        exit(0);
    }
    TreeNode* exp_node = parse_expression(tokens, start+2, end, NULL);
    assign_node->right = exp_node;
    return assign_node;
}

TreeNode* parse_change(DynamicArray tokens, int start, int end, int type, int* ptr) {
    TreeNode* id_node = new_node(ID, tokens.arr[start].stringValue);
    TreeNode* assign_node = new_node(type, tokens.arr[start+1].stringValue);
    assign_node->left = id_node;
    if(start+2 > end) {
        printf("Error while parsing: variabe assignment change '%s' must be followed by an expression, instead got '%s'", tokens.arr[start+1].stringValue, tokens.arr[start+2].stringValue);
        exit(0);
    }
    TreeNode* exp_node = parse_expression(tokens, start+2, end, NULL);
    assign_node->right = exp_node;
    return assign_node;
}

int is_end(int type) {
    return (type == IF || type == WHILE || type == SEMICOLON || type == DECLARE_FLOAT || type == DECLARE_INT || type == END || type == L_CURLY || type == R_CURLY || type == NEW_LINE || type == PRINT);
}

TreeNode* parse_code(DynamicArray tokens, int start, int end, TreeNode* right) {
    while(tokens.arr[start].intValue == NEW_LINE || tokens.arr[start].intValue == SEMICOLON) {
        start++;
    }
    int type = tokens.arr[start].intValue;
    int next_type = tokens.arr[start + 1].intValue;
    TreeNode* result;
    if(start >= tokens.size || start > end) {
        return right;
    } else if(type == IF || type == WHILE) {
        result = parse_if_while_statement(tokens, start, end, type, &start);
    }  else if(type == DECLARE_INT || type == DECLARE_FLOAT) {
        int j = start+1;
        while(!is_end(tokens.arr[j].intValue)) {
            j++;
        }
        result = parse_declaration(tokens, start, j-1, type, &start);
        start = j;
    } else if(type == ID && next_type == ASSIGN) {
        int j = start;
        while(!is_end(tokens.arr[j].intValue)) {
            j++;
        }
        result = parse_assignment(tokens, start, j-1, type, &start);
        start = j;
    } else if(type == ID && (next_type == ADD_ASSIGN || next_type == SUB_ASSIGN || next_type == MULT_ASSIGN || next_type == DIV_ASSIGN)) {
        int j = start;
        while(!is_end(tokens.arr[j].intValue)) {
            j++;
        }
        result = parse_change(tokens, start, j-1, next_type, &start);
        start = j;
    } else if(type == PRINT) {
        result = parse_print(tokens, start, end, &start);
    } else if(type == EXIT) {
        result = parse_exit(tokens, start, end, &start);
    } else {
        int j = start;
        while(!is_end(tokens.arr[j].intValue)) {
            j++;
        }
        if(start >= j) {
            return right;
        }
        result = parse_expression(tokens, start, j-1 > end ? end : j-1, &start);
        start = j+1;
    }

    TreeNode* e_node = new_node(EXECUTE, "execute");
    e_node->left = result;
    e_node->right = right;
    parse_code(tokens, start, end, e_node);
}

TreeNode* parse(DynamicArray tokens) {
    return parse_code(tokens, 0, tokens.size - 1, NULL);
}

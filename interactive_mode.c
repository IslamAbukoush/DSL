#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    DynamicArrayFloat GLOBAL_VARIABLES = float_new_array();
    DynamicArray GLOBAL_VARIABLES_TYPES = new_array();
    char buffer[1001];
    int counter = 0;
    printf("\nInteractive mode: (submit 0 to exit)\n");
    while (++counter) {
        printf("%i- ", counter);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input or end of file reached. Exiting.\n");
            break;
        }
        if(strlen(buffer) == 2 && buffer[0] == '0') {
            printf("Exiting program...");
            break;
        }
        DynamicArray tokens = lex(buffer);
        // print_array(&tokens);
        TreeNode* AST = parse(tokens);
        // print_ast(AST, 0, "Root node");
        
        interpret(AST, &GLOBAL_VARIABLES, &GLOBAL_VARIABLES_TYPES);
        free(tokens.arr);
        free_ast(AST);
        fflush(stdin);
    }

    return 0;
}
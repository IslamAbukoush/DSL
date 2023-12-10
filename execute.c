#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    long fileSize = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        fileSize++;
    }
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);

    return buffer;
}

int main(int argc,char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    char *source_code = readFile(filename);

    printf("Processing file: %s\n", filename);

    DynamicArray tokens = lex(source_code);
    // print_array(&tokens);
    TreeNode* AST = parse(tokens);
    // print_ast(AST, 0, "Root node");
    DynamicArrayFloat GLOBAL_VARIABLES = float_new_array();
    DynamicArray GLOBAL_VARIABLES_TYPES = new_array();
    interpret(AST, &GLOBAL_VARIABLES, &GLOBAL_VARIABLES_TYPES);
    free(tokens.arr);
    free(source_code);
    free_ast(AST);
}
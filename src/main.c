#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    char* input = "SELECT * FROM customers";
    struct Lexer* lexer = create_lexer(input);
    if (!lexer) {
        printf("Could not create lexer");
        return EXIT_FAILURE;
    }

    while (lexer_next(lexer)) {
        struct Token* token = lexer_token(lexer);
        if (!token) {
            printf("Could not get token");
            return EXIT_FAILURE;
        }

        printf("%d: '%s'\n", token->type, token->value);
        token_free(token);
    }

    lexer_free(lexer);
    return EXIT_SUCCESS;
}

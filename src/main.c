#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    char* input = "SELECT * FROM customers";

    struct Lexer lexer;
    if (!create_lexer(&lexer, input)) {
        printf("Could not create lexer");
        return EXIT_FAILURE;
    }

    while (lexer_next(&lexer)) {
        struct Token token;
        if (!lexer_token(&lexer, &token)) {
            printf("Could not get token");
            return EXIT_FAILURE;
        }

        printf("%d: '%s'\n", token.type, token.value);
        token_free(&token);
    }

    lexer_free(&lexer);
    return EXIT_SUCCESS;
}

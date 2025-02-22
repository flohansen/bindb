#include "lexer.h"
#include <stdio.h>

int main() {
    char* input = "SELECT * FROM customers";
    struct Lexer* lexer = create_lexer(input);

    struct Token token;
    while (lexer_next(lexer, &token)) {
        printf("%d: '%s'\n", token.type, token.value);
        free_token(token);
    }

    free_lexer(lexer);
    return 0;
}

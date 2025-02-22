#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lexer* create_lexer(char* input) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    memset(lexer, 0, sizeof(Lexer));

    lexer->input = input;
    lexer->position = 0;
    lexer->length = strlen(input);

    return lexer;
}

bool lexer_next(Lexer* lexer, Token* token) {
    char c;
    if (!lexer_next_char(lexer, &c)) {
        return false;
    }

    if (is_letter(c)) {
        *token = lexer_parse_literal(lexer, c);
    } else if (c == '*') {
        set_token(token, TOKEN_ASTERISK, c);
    } else {
        set_token(token, TOKEN_UNKNOWN, c);
    }

    return true;
}

void set_token(Token* token, TokenType type, char c) {
    token->type = type;
    token->value = (char*)calloc(2, sizeof(char));
    memset(token->value, c, 1);
}

bool lexer_next_char(Lexer* lexer, char* c) {
    if (lexer->position >= lexer->length) {
        return false;
    }

    *c = lexer->input[lexer->position];
    lexer->position++;
    return true;
}

bool lexer_peek_char(Lexer* lexer, char* c) {
    if (lexer->position >= lexer->length) {
        return false;
    }

    *c = lexer->input[lexer->position];
    return true;
}

Token lexer_parse_literal(Lexer* lexer, char c) {
    Token token;
    memset(&token, 0, sizeof(Token));
    token.type = TOKEN_LITERAL;

    size_t start = lexer->position;

    for (;;) {
        char c;
        if (!lexer_peek_char(lexer, &c)) {
            break;
        }

        if (!is_letter(c)) {
            break;
        }

        lexer->position++;
    }

    size_t n = lexer->position - start + 1;
    token.value = (char*)malloc(n);
    memset(token.value, c, 1);
    memcpy(token.value+1, lexer->input+start, n-1);

    return token;
}

bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void free_lexer(Lexer* lexer) {
    free(lexer);
}

void free_token(Token token) {
    free(token.value);
}

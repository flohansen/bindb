#include "lexer.h"
#include <stdlib.h>
#include <string.h>

struct Lexer* create_lexer(const char* input) {
    struct Lexer* lexer = (struct Lexer*)malloc(sizeof(struct Lexer));
    if (!lexer) {
        return NULL;
    }

    memset(lexer, 0, sizeof(struct Lexer));
    unsigned int input_len = strlen(input);
    lexer->input_len = input_len;
    lexer->input = strdup(input);

    if (!lexer->input) {
        free(lexer);
        return NULL;
    }

    return lexer;
}

void lexer_free(struct Lexer* lexer) {
    free(lexer->input);
    free(lexer);
}

bool lexer_next(struct Lexer* lexer) {
    char c;
    if (!lexer_next_char(lexer, &c)) {
        return false;
    }

    if (is_whitespace(c)) {
        return lexer_next(lexer);
    } else if (is_alpha(c)) {
        lexer_parse_literal(lexer);
    } else if (c == '*') {
        lexer_parse_char(lexer, TOKEN_OPERATOR);
    } else {
        lexer_parse_char(lexer, TOKEN_UNKNOWN);
    }

    return true;
}

bool lexer_next_char(struct Lexer* lexer, char* c) {
    if (lexer->pos >= lexer->input_len) {
        return false;
    }

    *c = lexer->input[lexer->pos];
    lexer->pos++;
    return true;
}

bool lexer_peek_char(struct Lexer* lexer, char* c) {
    if (lexer->pos >= lexer->input_len) {
        return false;
    }

    *c = lexer->input[lexer->pos];
    return true;
}

void lexer_parse_char(struct Lexer* lexer, enum TokenType type) {
    lexer->type = type;
    lexer->start = lexer->pos-1;
    lexer->len = 1;
}

void lexer_parse_literal(struct Lexer* lexer) {
    lexer->type = TOKEN_LITERAL;
    lexer->start = lexer->pos-1;
    lexer->len = 1;

    for (;;) {
        char c;
        if (!lexer_peek_char(lexer, &c)) {
            break;
        }
        if (!is_alpha(c)) {
            break;
        }

        lexer->pos++;
        lexer->len++;
    }
}

struct Token* lexer_token(struct Lexer* lexer) {
    struct Token* token = (struct Token*)malloc(sizeof(struct Token));
    if (!token) {
        return NULL;
    }

    memset(token, 0, sizeof(struct Token));
    token->type = lexer->type;
    token->value = (char*)calloc(lexer->len, sizeof(char));

    if (!token->value) {
        free(token);
        return NULL;
    }

    strncpy(token->value, lexer->input + lexer->start, lexer->len);
    return token;
}

void token_free(struct Token* token) {
    free(token->value);
    free(token);
}

bool is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

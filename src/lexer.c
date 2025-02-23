#include "lexer.h"
#include <stdlib.h>
#include <string.h>

bool create_lexer(struct Lexer* lexer, const char* input) {
    memset(lexer, 0, sizeof(struct Lexer));

    unsigned int input_len = strlen(input);
    lexer->input_len = input_len;
    lexer->input = strdup(input);

    if (!lexer->input) {
        return false;
    }

    return true;
}

void lexer_free(struct Lexer* lexer) {
    free(lexer->input);
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

bool lexer_token(struct Lexer* lexer, struct Token* token) {
    memset(token, 0, sizeof(struct Token));
    token->type = lexer->type;
    token->value = (char*)calloc(lexer->len+1, sizeof(char));

    if (!token->value) {
        free(token);
        return false;
    }

    strncpy(token->value, lexer->input + lexer->start, lexer->len);
    return true;
}

void token_free(struct Token* token) {
    free(token->value);
}

bool is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

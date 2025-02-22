#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <stdbool.h>

enum TokenType {
    TOKEN_LITERAL,
    TOKEN_ASTERISK,
    TOKEN_UNKNOWN,
};

struct Token {
    enum TokenType type;
    char* value;
};

struct Lexer {
    char* input;
    struct Token token;
    size_t position;
    size_t length;
};

/**
 * Creates a new lexer instance.
 */
struct Lexer* create_lexer(char* input);

/**
 * Retrieves the next character from the lexer input.
 */
bool lexer_next_char(struct Lexer* lexer, char* c);

/**
 * Peeks at the next character in the lexer input without advancing the position.
 */
bool lexer_peek_char(struct Lexer* lexer, char* c);

/**
 * Retrieves the next token from the lexer.
 */
bool lexer_next(struct Lexer* lexer, struct Token* token);

/**
 * Sets the type and value of a token.
 */
void set_token(struct Token* token, enum TokenType type, char c);

/**
 * Parses a literal from the lexer input.
 */
struct Token lexer_parse_literal(struct Lexer* lexer, char c);

/**
 * Checks if the character is a letter [a-zA-Z].
 */
bool is_letter(char c);

/**
 * Frees memory of the lexer.
 */
void free_lexer(struct Lexer* lexer);

/**
 * Frees memory of the token.
 */
void free_token(struct Token token);

#endif // LEXER_H

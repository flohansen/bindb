#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TOKEN_LITERAL,
    TOKEN_ASTERISK,
    TOKEN_UNKNOWN,
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

typedef struct {
    char* input;
    size_t position;
    size_t length;
} Lexer;

/**
 * Creates a new lexer instance.
 */
Lexer* create_lexer(char* input);

/**
 * Retrieves the next character from the lexer input.
 */
bool lexer_next_char(Lexer* lexer, char* c);

/**
 * Peeks at the next character in the lexer input without advancing the position.
 */
bool lexer_peek_char(Lexer* lexer, char* c);

/**
 * Retrieves the next token from the lexer.
 */
bool lexer_next(Lexer* lexer, Token* token);

/**
 * Sets the type and value of a token.
 */
void set_token(Token* token, TokenType type, char c);

/**
 * Parses a literal from the lexer input.
 */
Token lexer_parse_literal(Lexer* lexer, char c);

/**
 * Checks if the character is a letter [a-zA-Z].
 */
bool is_letter(char c);

/**
 * Frees memory of the lexer.
 */
void free_lexer(Lexer* lexer);

/**
 * Frees memory of the token.
 */
void free_token(Token token);

#endif // LEXER_H

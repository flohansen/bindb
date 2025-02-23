#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

/**
 * Enum values describing the type of a token.
 */
enum TokenType {
    TOKEN_LITERAL,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN,
};

/**
 * The `Token` struct represents one token of a lexical analysis.
 */
struct Token {
    enum TokenType type;
    char* value;
};

/**
 * The `Lexer` struct holds information about the input string and the current
 * token. It acts like an iterator over the input string identifying tokens.
 */
struct Lexer {
    char* input;
    unsigned int input_len;
    unsigned int pos;
    enum TokenType type;
    unsigned int start;
    unsigned int len;
};

/**
 * Creates a new instance of a lexer using the input string that it should
 * tokenize. You need to call `lexer_free` after you are done with it.
 */
struct Lexer* create_lexer(const char* input);

/**
 * Frees the memory used by the lexer.
 */
void lexer_free(struct Lexer* lexer);

/**
 * Moves the lexer to the next token of the input string and returns true, if it
 * read one, false otherwise.
 */
bool lexer_next(struct Lexer* lexer);

/**
 * Tries to read the next character of the input string of the lexer. If there
 * is a next character, the lexer position is being incremented and the function
 * returns `true`, otherwise `false`.
 */
bool lexer_next_char(struct Lexer* lexer, char* c);

/**
 * Tries to read the next character of the input string of the lexer. If there
 * is a next character without updating the position. Returns `true`, otherwise
 * `false`.
 */
bool lexer_peek_char(struct Lexer* lexer, char* c);

/**
 * Reads the next character as a token and sets the type of it.
 */
void lexer_parse_char(struct Lexer* lexer, enum TokenType type);

/**
 * Reads from the token as a string literal from the input string.
 */
void lexer_parse_literal(struct Lexer* lexer);

/**
 * Returns the current token of the lexer. You need to call `token_free` to
 * release resources.
 */
struct Token* lexer_token(struct Lexer* lexer);

/**
 * Frees the memory used by the token.
 */
void token_free(struct Token* token);

/**
 * Checks whether the given character is a whitespace character (like space, new
 * line, ...).
 */
bool is_whitespace(char c);

/**
 * Checks whether the given character is an alpha character.
 */
bool is_alpha(char c);

#endif // LEXER_H

/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "json-128.h"

J128_EXPORT bool j128_next_token(j128_codepoint codepoint, j128_token *token, j128 *additional_data) {
    switch(codepoint) {
        case 0x0000: // NULL
            token->type = J128_TOKEN_EOF;
            token->token = "EOF";
            token->n = 3;
            return true;

        case 0x0020: // SPACE
        case 0x0009: // CHARACTER TABULATION
        case 0x000A: // LINE FEED (LF)
        case 0x000D: // CARRIAGE RETURN (CR)
            return false;

        // Structural tokens
        case 0x007B: // LEFT CURLY BRACE
            token->type = J128_TOKEN_LEFT_BRACKET;
            token->token = "LEFT_BRACE";
            token->n = 11;
            return true;

        case 0x007D: // RIGHT CURLY BRACE
            token->type = J128_TOKEN_RIGHT_BRACKET;
            token->token = "RIGHT_BRACE";
            token->n = 12;
            return true;

        case 0x005B: // LEFT SQUARE BRACKET
            token->type = J128_TOKEN_LEFT_BRACKET;
            token->token = "LEFT_BRACKET";
            token->n = 13;
            return true;

        case 0x005D: // RIGHT SQUARE BRACKET
            token->type = J128_TOKEN_RIGHT_BRACKET;
            token->token = "RIGHT_BRACKET";
            token->n = 14;
            return true;

        case 0x002C: // COMMA
            token->type = J128_TOKEN_COMMA;
            token->token = "COMMA";
            token->n = 5;
            return true;

        case 0x003A:
            token->type = J128_TOKEN_COLON;
            token->token = "COLON";
            token->n = 5;
            return true;

        // Literal tokens
        // J128_TOKEN_TRUE, // true
        // J128_TOKEN_FALSE, // false
        // J128_TOKEN_NULL, // null
        // Number token
        // J128_TOKEN_NUMBER, // number
        // String token
        // J128_TOKEN_STRING, // string

        default:
            return J128_TOKEN_ERROR;
    }

    return J128_TOKEN_ERROR;
}

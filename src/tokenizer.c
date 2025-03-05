/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "json-128.h"

J128_EXPORT j128_token j128_next_token(j128_codepoint codepoint) {
    switch(codepoint) {
        case 0x0020: // SPACE
        case 0x0009: // CHARACTER TABULATION
        case 0x000A: // LINE FEED (LF)
        case 0x000D: // CARRIAGE RETURN (CR)
            return J128_TOKEN_IGNORE;
        // Structural tokens
        case 0x007B: // LEFT CURLY BRACE
            return J128_TOKEN_LEFT_BRACE;

        case 0x007D: // RIGHT CURLY BRACE
            return J128_TOKEN_RIGHT_BRACE;

        case 0x005B: // LEFT SQUARE BRACKET
            return J128_TOKEN_LEFT_BRACKET;

        case 0x005D: // RIGHT SQUARE BRACKET
            return J128_TOKEN_RIGHT_BRACKET;

        case 0x002C: // COMMA
            return J128_TOKEN_COMMA;

        case 0x003A:
            return J128_TOKEN_COLON;

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
}

/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#ifndef J128_JSON_128_H
#define J128_JSON_128_H

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#error "C11 or a later version is required"
#endif

#if defined(_WIN32) || defined(_WIN64)
#error "Windows is not supported"
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define J128_VERSION          "0.0.1"
#define J128_VERSION_NUMBER   0x1 // MAJOR << 8 && MINOR << 4 && REVISION
#define J128_VERSION_MAJOR    0
#define J128_VERSION_MINOR    0
#define J128_VERSION_REVISION 1

#ifndef J128_EXTERN
#define J128_EXTERN extern
#endif

#ifndef J128_EXPORT
#define J128_EXPORT __attribute__((visibility("default")))
#endif

#define J128_CODEPOINT_MIN         0x0
#define J128_CODEPOINT_MAX         0x10FFFF // Maximum valid unicode code point
#define J128_CODEPOINT_REPLACEMENT 0xFFFD   // The character used when there is invalid data
#define J128_CODEPOINT_NOT_VALID   0x110000 // Not a valid codepoint

#define J128_HUGE_NUMBERS_FAIL         0x00000001
#define J128_NOT_VALID_UNICODE_REPLACE 0x00000002
#define J128_NOT_VALID_UNICODE_FAIL    0x00000004
#define J128_UTF8_BOM_FAIL             0x00000008

typedef enum j128_encoding {
    J128_ENCODING_ERROR,
    J128_ENCODING_ASCII,
    J128_ENCODING_UTF_8,
    J128_ENCODING_UTF_16_BE,
    J128_ENCODING_UTF_16_LE,
    J128_ENCODING_UTF_32_BE,
    J128_ENCODING_UTF_32_LE
} j128_encoding;

typedef enum j128_token {
    J128_TOKEN_IGNORE,
    J128_TOKEN_ERROR,
    J128_TOKEN_EOF,
    // Structural tokens
    J128_TOKEN_LEFT_BRACE, // {
    J128_TOKEN_RIGHT_BRACE, // }
    J128_TOKEN_LEFT_BRACKET, // [
    J128_TOKEN_RIGHT_BRACKET, // ]
    J128_TOKEN_COMMA, // ,
    J128_TOKEN_COLON, // :
    // Literal tokens
    J128_TOKEN_TRUE, // true
    J128_TOKEN_FALSE, // false
    J128_TOKEN_NULL, // null
    // Number token
    J128_TOKEN_NUMBER, // number
    // String token
    J128_TOKEN_STRING, // string
} j128_token;

/**
 * A unicode codepoint, a value in the range 0 to 0x10FFFF
 * [see: https://www.unicode.org/glossary/#code_point]
 */
typedef uint32_t j128_codepoint;

/**
 * A callback function that is called when a token is found
 */
typedef void (*j128_tokenizer_callback)(size_t index, size_t string_index, j128_codepoint codepoint, j128_token token);

typedef struct j128 {
    j128_tokenizer_callback tokenizer_callback;
} j128;

// Return the string encoding (the most probable)
j128_encoding j128_encoding_from_bom(const char *buffer, size_t length, int *start);

bool j128_parse_json(const char *json, size_t size, int flags, j128 *additional_data);

bool j128_parse_json_utf8(const char *json, size_t size, int flags, j128 *additional_data);
bool j128_parse_json_utf16(const char *json, size_t size, bool big_endian, int flags, j128 *additional_data);

j128_token j128_next_token(j128_codepoint codepoint);

// Output the current library version (J128_VERSION)
char *j128_version(void);

// Output the current library version number (J128_VERSION_NUMBER)
unsigned int j128_version_number(void);

#ifdef __cplusplus
}
#endif

#endif // J128_JSON_128_H

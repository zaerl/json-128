/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "../src/json-128.h"
#include "test.h"

static j128_codepoint *codepoints;

static void tokenizer_callback(size_t index, size_t string_index, j128_codepoint codepoint, j128_token token) {
    char str[128];
    snprintf(str, sizeof(str), "Codepoint 0x%x: %zu, %zu, %d\n", codepoint, index, string_index, token);

    ATT_ASSERT(codepoint, codepoints[index], str);
}

void *test_unicode_utf8(void *arg) {
    j128 add = { .tokenizer_callback = tokenizer_callback };

    #define J128_TEST_STRING(STR, LENGTH, REPLACE, DESCRIPTION) \
        ATT_ASSERT(j128_parse_json_utf8(STR, LENGTH, 0, &add), true, DESCRIPTION ": but not by default"); \
        ATT_ASSERT(j128_parse_json_utf8(STR, LENGTH, J128_NOT_VALID_UNICODE_FAIL, &add), false, DESCRIPTION); \
        codepoints[REPLACE] = J128_CODEPOINT_REPLACEMENT; \
        ATT_ASSERT(j128_parse_json_utf8(STR, LENGTH, J128_NOT_VALID_UNICODE_REPLACE, &add), true, DESCRIPTION ": replace");

    #define J128_TEST_VALID_STRING(STR, LENGTH) \
        ATT_ASSERT(j128_parse_json_utf8(STR, LENGTH, 0, &add), true, STR); \
        ATT_ASSERT(j128_parse_json_utf8(STR, LENGTH, J128_NOT_VALID_UNICODE_FAIL, &add), true, STR " fail"); \
        ATT_ASSERT(j128_parse_json_utf8(STR, LENGTH, J128_NOT_VALID_UNICODE_REPLACE, &add), true, STR " replace");

    // Test valid UTF-8 sequences
    j128_codepoint cafe_test[] = { 0x43, 0x61, 0x66, 0x0, 0xE9 };
    codepoints = (j128_codepoint*)cafe_test;
    J128_TEST_VALID_STRING("Café", 5);

    // Mixed 2-byte and 3-byte sequences
    j128_codepoint euro_yen_test[] = { 0x0, 0x0, 0x20AC, 0x75, 0x72, 0x6F, 0x20, 0x0, 0xA5, 0x65, 0x6E };
    codepoints = (j128_codepoint*)euro_yen_test;
    J128_TEST_VALID_STRING("€uro ¥en", 11);

    // Hello 🌍 World!
    j128_codepoint hello_world_test[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x0, 0x0, 0x0, 0x1F30D, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21 };
    codepoints = (j128_codepoint*)hello_world_test;
    J128_TEST_VALID_STRING("Hello 🌍 World!", 17);

    // ABC\xC3XYZ
    j128_codepoint alphabet_test[] = { 0x41, 0x42, 0x43, 0x0, 0x0, 0x59, 0x5A };
    codepoints = (j128_codepoint*)alphabet_test;
    J128_TEST_STRING("ABC\xC3XYZ", 7, 4, "Fail after ABC");

    #undef J128_TEST_STRING
    #undef J128_TEST_VALID_STRING

    return NULL;
}

void *test_unicode_utf16(void *arg) {
    j128 add = { .tokenizer_callback = tokenizer_callback };

    #define J128_TEST_VALID_STRING(STR, LENGTH, BIG_ENDIAN, DESCRIPTION) \
        ATT_ASSERT(j128_parse_json_utf16(STR, LENGTH, BIG_ENDIAN, 0, &add), true, DESCRIPTION);

    // Test valid UTF-16 sequences
    // Little-endian: "Hello 🌍 World!"
    static const char le_hello[] = "\x48\x00\x65\x00\x6c\x00\x6c\x00\x6f\x00\x20\x00\x3c\xd8\x0d\xdf\x20\x00\x57\x00\x6f\x00\x72\x00\x6c\x00\x64\x00\x21\x00";
    j128_codepoint hello_world_test[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x32, 0x1F30D, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21 };
    codepoints = (j128_codepoint*)hello_world_test;
    J128_TEST_VALID_STRING(le_hello, 30, false, "UTF-16LE Hello World");

    #undef J128_TEST_VALID_STRING

    return NULL;
}

/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "../src/json-128.h"
#include "test.h"

static j128_codepoint *codepoints;

static void codepoint_callback(size_t index, size_t string_index, j128_codepoint codepoint) {
    char str[32];
    snprintf(str, sizeof(str), "Codepoint: %x at index %zu, string index %zu\n", codepoint, index, string_index);

    ATT_ASSERT(codepoint, codepoints[index], str);
}

void *test_unicode(void *arg) {
    j128 add = { .codepoint_callback = codepoint_callback };

    // Test valid UTF-8 sequences
    // Mixed ASCII and 2-byte sequences
    // j128_parse_string(&add, "Café", 5);  // Codepoints: 67, 97, 102, 233

    // Mixed 2-byte and 3-byte sequences
    // j128_parse_string(&add, "€uro ¥en", 9);  // Codepoints: 8364, 117, 114, 111, 32, 165, 101, 110

    // Mixed sequences with emojis
    // j128_parse_string(&add, "Hello 🌍 World!", 15);  // Codepoints: 72,101,108,108,111,32,127757,32,87,111,114,108,100,33

    // Complex Unicode text with various scripts
    // j128_parse_string(&add, "你好，世界！", 15);  // Codepoints: 20320, 22909, 65292, 19990, 30028, 65281

    // Test invalid UTF-8 sequences
    // String with incomplete sequence in the middle
    // j128_parse_string(&add, "ABC\xC3XYZ", 7);  // Should fail after "ABC"

    j128_codepoint codepoints_test[] = { 65, 66, 67, 0, 0, 89, 90 };
    codepoints = (j128_codepoint *)codepoints_test;
    ATT_ASSERT(j128_parse_json_utf8("ABC\xC3XYZ", 7, 0, &add), true, "Fail after ABC, but not by default");
    ATT_ASSERT(j128_parse_json_utf8("ABC\xC3XYZ", 7, J128_NOT_VALID_UNICODE_FAIL, &add), false, "Fail after ABC");

    codepoints_test[4] = J128_CODEPOINT_REPLACEMENT;
    ATT_ASSERT(j128_parse_json_utf8("ABC\xC3XYZ", 7, J128_NOT_VALID_UNICODE_REPLACE, &add), true, "Replace after ABC");

    // String with invalid continuation bytes
    // j128_parse_string(&add, "Test\xC3\x28\x29", 8);  // Should fail after "Test"

    // String with overlong encoding
    // j128_parse_string(&add, "Start\xC0\xA4End", 10);  // Should fail after "Start"

    // String with sequence exceeding Unicode range
    // j128_parse_string(&add, "Begin\xF7\xBF\xBF\xBFStop", 12);  // Should fail after "Begin"

    return NULL;
}

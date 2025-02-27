/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "../src/json-128.h"
#include "test.h"

static void codepoint_callback(size_t index, size_t string_index, j128_codepoint codepoint) {}

void *test_parse_json(void *arg) {
    // ["😐"]
    const char *hw = "[\"\xF0\x9F\x98\x90\"]";
    const char *wrong_hw = "[\"\xF0\x9F\x98\"]";
    size_t hw_size = 8;
    size_t wrong_hw_size = 7;

    j128 add = { 0 };
    ATT_ASSERT(j128_parse_json(hw, hw_size, 0, &add), true, "[\"😐\"]");
    ATT_ASSERT(j128_parse_json(wrong_hw, wrong_hw_size, 0, &add), true, "[\"\\xF0\\x9F\\x98\"]");
    ATT_ASSERT(j128_parse_json(wrong_hw, wrong_hw_size, J128_NOT_VALID_UNICODE_FAIL, &add), false, "Wrong encoding, fail");
    ATT_ASSERT(j128_parse_json(wrong_hw, wrong_hw_size, J128_NOT_VALID_UNICODE_REPLACE, &add), true, "Wrong encoding, replace");

    add.codepoint_callback = codepoint_callback;

    return NULL;
}

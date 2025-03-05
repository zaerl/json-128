/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "../src/json-128.h"
#include "test.h"

static j128_token *tokens;

static void tokenizer_callback(size_t index, size_t string_index, j128_codepoint codepoint, j128_token token) {
    char str[128];
    snprintf(str, sizeof(str), "Codepoint 0x%x: %zu, %zu, %d\n", codepoint, index, string_index, token);

    ATT_ASSERT(token, tokens[index], str);
}

void *test_tokenizer(void *arg) {
    j128 add = { .tokenizer_callback = tokenizer_callback };
    j128_token token_test[] = { J128_TOKEN_LEFT_BRACE, J128_TOKEN_RIGHT_BRACE };
    tokens = (j128_token*)token_test;

    ATT_ASSERT(j128_parse_json("{}", 2, 0, &add), true, "{}");

    return NULL;
}

/**
 * The mojibake library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "../src/json-128.h"
#include "test.h"

void *test_encoding(void *arg) {
    int start = 0;

    ATT_ASSERT(j128_encoding_from_bom(0, 10, &start), J128_ENCODING_ERROR, "Void string")
    ATT_ASSERT(j128_encoding_from_bom("", 0, &start), J128_ENCODING_ERROR, "Void length");
    ATT_ASSERT(j128_encoding_from_bom(0, 0, &start), J128_ENCODING_ERROR, "Void string and length");

    const char *test1 = "The quick brown fox jumps over the lazy dog";
    ATT_ASSERT(j128_encoding_from_bom(test1, 43, &start), J128_ENCODING_UTF_8, "Plain ASCII (and UTF-8)");

    const char *test2 = "\xEF\xBB\xBFThe quick brown fox jumps over the lazy dog";
    ATT_ASSERT(j128_encoding_from_bom(test2, 43 + 3, &start), J128_ENCODING_UTF_8, "UTF-8 BOM");

    const char *test3 = "\xFE\xFFThe quick brown fox jumps over the lazy dog";
    ATT_ASSERT(j128_encoding_from_bom(test3, 43 + 2, &start), J128_ENCODING_UTF_16_BE, "UTF-16-BE BOM");

    const char *test4 = "\xFF\xFEThe quick brown fox jumps over the lazy dog";
    ATT_ASSERT(j128_encoding_from_bom(test4, 43 + 2, &start), J128_ENCODING_UTF_16_LE, "UTF-16-LE BOM");

    return NULL;
}

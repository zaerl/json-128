/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "../src/json-128.h"
#include "test.h"

void *test_version(void *arg) {
    ATT_ASSERT(strcmp(j128_version(), J128_VERSION), 0, "Valid version");
    ATT_ASSERT(j128_version_number(), J128_VERSION_NUMBER, "Valid version number");
    ATT_ASSERT(j128_version_number(), J128_VERSION_NUMBER, "Valid version number");

    return NULL;
}

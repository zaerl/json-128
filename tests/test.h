/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#ifndef JSON_128_TEST_H
#define JSON_128_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/json-128.h"
#include "./attractor/attractor.h"

#ifdef __cplusplus
extern "C" {
#endif

// Start tests declarations.
void *test_version(void *arg);
void *test_encoding(void *arg);
void *test_parse_json(void *arg);

#ifdef __cplusplus
}
#endif

#endif // JSON_128_TEST_H

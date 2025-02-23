/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include "json-128.h"

// Output the current library version (J128_VERSION)
J128_EXPORT char *j128_version(void) {
    return J128_VERSION;
}

// Output the current library version number (J128_VERSION_NUMBER)
J128_EXPORT unsigned int j128_version_number(void) {
    return J128_VERSION_NUMBER;
}

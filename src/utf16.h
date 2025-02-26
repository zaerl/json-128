/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include <stdint.h>
#include <stdbool.h>

#define J128_UTF16_ACCEPT 0
#define J128_UTF16_REJECT 0xF
#define J128_UTF16_EXPECT_LOW 0x10

static inline uint32_t __used j128_utf16_decode_step(uint32_t state, uint16_t byte, uint32_t* codepoint, bool big_endian) {
    if(state == J128_UTF16_ACCEPT) {
        if(big_endian) {
            byte = (byte >> 8) | (byte << 8);
        }

        if(byte >= 0xD800 && byte <= 0xDBFF) {
            // High surrogate
            *codepoint = (byte - 0xD800) << 10;

            return J128_UTF16_EXPECT_LOW;
        } else if(byte >= 0xDC00 && byte <= 0xDFFF) {
            // Unexpected low surrogate
            return J128_UTF16_REJECT;
        } else {
            // Basic Multilingual Plane character
            *codepoint = byte;

            return J128_UTF16_ACCEPT;
        }
    } else if(state == J128_UTF16_EXPECT_LOW) {
        if(big_endian) {
            byte = (byte >> 8) | (byte << 8);
        }

        if(byte >= 0xDC00 && byte <= 0xDFFF) {
            // Valid low surrogate
            *codepoint = (*codepoint | (byte - 0xDC00)) + 0x10000;

            return J128_UTF16_ACCEPT;
        }

        return J128_UTF16_REJECT;
    }

    return J128_UTF16_REJECT;
}

/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include <string.h>

#include "json-128.h"
#include "utf8.h"
#include "utf16.h"

#define J128_ENCODING_UTF_8_BOM "\xEF\xBB\xBF"
#define J128_ENCODING_UTF_16_BE_BOM "\xFE\xFF"
#define J128_ENCODING_UTF_16_LE_BOM "\xFF\xFE"
#define J128_ENCODING_UTF_32_BE_BOM "\x00\x00\xFE\xFF"
#define J128_ENCODING_UTF_32_LE_BOM "\xFF\xFE\x00\x00"

/**
 * Return the encoding from the BOM (if possible).
 */
J128_EXPORT j128_encoding j128_encoding_from_bom(const char *buffer, size_t length, int *start) {
    if(buffer == NULL || length == 0) {
        // Empty string.
        return J128_ENCODING_ERROR;
    }

    if(length < 2) {
        // BOM are at least 2 characters. Assume UTF-8.
        return J128_ENCODING_UTF_8;
    }

    if(length >= 3) {
        if(memcmp(buffer, J128_ENCODING_UTF_8_BOM, 3) == 0) {
            if(length == 3) {
                // The BOM is the only thing in the file.
                return J128_ENCODING_ERROR;
            }

            *start = 3;

            return J128_ENCODING_UTF_8;
        }
    }

    j128_encoding bom_encoding = J128_ENCODING_UTF_8;

    if(length >= 2) {
        if(memcmp(buffer, J128_ENCODING_UTF_16_BE_BOM, 2) == 0) {
            bom_encoding = J128_ENCODING_UTF_16_BE;
        } else if(memcmp(buffer, J128_ENCODING_UTF_16_LE_BOM, 2) == 0) {
            bom_encoding = J128_ENCODING_UTF_16_LE;
        }

        if(bom_encoding != J128_ENCODING_UTF_8) {
            if(length == 2) {
                // The BOM is the only thing in the file.
                return J128_ENCODING_ERROR;
            }

            *start = 2;
        }
    }

    return bom_encoding;
}

J128_EXPORT bool j128_parse_json_utf8(const char *json, size_t size, int flags, j128 *additional_data) {
    if(json == NULL || size == 0) {
        return false;
    }

    uint8_t state = J128_UTF8_ACCEPT;
    j128_codepoint current_codepoint;
    const char *index = json;
    size_t string_index = 0;

    // Loop through the string.
    for(; *index && (size_t)(index - json) < size; ++index) {
        // Find next codepoint.
        state = j128_utf8_decode_step(state, *index, &current_codepoint);

        if(state == J128_UTF8_REJECT) {
            // The string is not well-formed.
            if(flags & J128_NOT_VALID_UNICODE_FAIL) {
                // Fail the parsing.
                return false;
            }

            state = J128_UTF8_ACCEPT;

            if(flags & J128_NOT_VALID_UNICODE_REPLACE) {
                // Replace the invalid character with the replacement character.
                current_codepoint = J128_CODEPOINT_REPLACEMENT;
            } else {
                // Do nothing.
                continue;
            }
        }

        // Still not found a UTF-8 character, continue.
        if(state != J128_UTF8_ACCEPT) {
            continue;
        }

        // Call the callback and continue.
        if(additional_data->tokenizer_callback != NULL) {
            additional_data->tokenizer_callback(index - json, string_index, current_codepoint, j128_next_token(current_codepoint));
            ++string_index;

            continue;
        }
    }

    return state == J128_UTF8_ACCEPT;
}

J128_EXPORT bool j128_parse_json_utf16(const char *json, size_t size, bool big_endian, int flags, j128 *additional_data) {
    if(json == NULL || size == 0) {
        return false;
    }

    // Size must be even for UTF-16.
    if(size % 2 != 0) {
        return false;
    }

    uint8_t state = J128_UTF16_ACCEPT;
    j128_codepoint current_codepoint;
    size_t utf16_len = size / 2;
    size_t string_index = 0;

    const uint16_t *utf16_json = (const uint16_t *)json;

    // Loop through the string.
    for(size_t i = 0; i < utf16_len; ++i) {
        // Get next code unit and decode.
        state = j128_utf16_decode_step(state, utf16_json[i], &current_codepoint, big_endian);

        if(state == J128_UTF16_REJECT) {
            // The string is not well-formed.
            if(flags & J128_NOT_VALID_UNICODE_FAIL) {
                return false;
            }

            state = J128_UTF16_ACCEPT;

            if(flags & J128_NOT_VALID_UNICODE_REPLACE) {
                current_codepoint = J128_CODEPOINT_REPLACEMENT;
            } else {
                continue;
            }
        }

        // Still not found a complete UTF-16 character, continue.
        if(state != J128_UTF16_ACCEPT) {
            continue;
        }

        // Call the callback.
        if(additional_data->tokenizer_callback != NULL) {
            additional_data->tokenizer_callback(i, string_index, current_codepoint, j128_next_token(current_codepoint));
            ++string_index;
        }
    }

    return state == J128_UTF16_ACCEPT;
}

J128_EXPORT bool j128_parse_json(const char *json, size_t size, int flags, j128 *additional_data) {
    if(json == NULL || size == 0) {
        return false;
    }

    int start = 0;
    j128_encoding encoding = j128_encoding_from_bom(json, size, &start);

    if(encoding == J128_ENCODING_ERROR) {
        return false;
    }

    size_t real_size = size - start;

    return encoding == J128_ENCODING_UTF_8 ?
        j128_parse_json_utf8(json + start, real_size, flags, additional_data) :
        j128_parse_json_utf16(json + start, real_size, encoding == J128_ENCODING_UTF_16_BE, flags, additional_data);
}

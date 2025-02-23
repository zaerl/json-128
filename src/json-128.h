/**
 * The json-128 library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#ifndef J128_JSON_128_H
#define J128_JSON_128_H

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#error "C11 or a later version is required"
#endif

#if defined(_WIN32) || defined(_WIN64)
#error "Windows is not supported"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define J128_VERSION          "0.0.1"
#define J128_VERSION_NUMBER   0x1 // MAJOR << 8 && MINOR << 4 && REVISION
#define J128_VERSION_MAJOR    0
#define J128_VERSION_MINOR    0
#define J128_VERSION_REVISION 1

#ifndef J128_EXTERN
#define J128_EXTERN extern
#endif

#ifndef J128_EXPORT
#define J128_EXPORT __attribute__((visibility("default")))
#endif

// Output the current library version (J128_VERSION)
char *j128_version(void);

// Output the current library version number (J128_VERSION_NUMBER)
unsigned int j128_version_number(void);

#ifdef __cplusplus
}
#endif

#endif // J128_JSON_128_H

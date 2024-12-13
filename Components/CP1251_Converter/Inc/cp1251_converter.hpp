#ifndef __CP1251_CONVERTER_HPP_
#define __CP1251_CONVERTER_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>

int utf8_buf_to_cp1251(const char *utf8, char *windows1251, size_t n);
char *utf8_string_to_cp1251(const char *utf8, char *windows1251);

#endif

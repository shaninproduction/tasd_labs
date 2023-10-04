#ifndef IO_H
#define IO_H

#include "constants.h"
#include "libs.h"

void print_integer(big_int *num);
void print_float(big_float *num);
void copy(char *buffer, big_int *num);
int check_integer(char *integer, size_t len);
int read_integer(big_int *num);
int read_str_in_buffer(char *buffer, size_t *len);
int check_sign(char *buffer, bool *is_negative, size_t len);
int get_mantissa(char *buffer, big_float *num);
int get_exponent(char *buffer, size_t len, big_float *num, bool is_two_parts);
int get_float(char *buffer, big_float *num);
int read_float(big_float *num);
void split_buffer_by_parts(char *buffer, char parts[MAX_PARTS][MAX_FLOAT_LEN_IN], int *parts_count);
int normalize(big_float *num);
#endif
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BASE 10

#define OK 0
#define OVERFLOW_ERR 1
#define READ_ERR 2
#define INVALID_INPUT 3
#define NORM_ERR 4
#define EXP_ERR 5

#define MAX_LEN_INT 40

#define MAX_FLOAT_LEN_IN 100
#define MAX_LEN_MANTISSA_OUT 40
#define MAX_LEN_MANTISSA_IN 30
#define MAX_EXP 5
#define MAX_PARTS 3
#define MAX_RESULT 71

typedef struct
{
    int nums[MAX_LEN_INT];
    size_t len;
    bool is_negative;
} big_int;

typedef struct
{
    int mantissa[MAX_LEN_MANTISSA_IN];
    int point_index;
    size_t len_mantissa;
    int exp;
    bool is_negative;
} big_float;

typedef struct
{
    int mantissa[MAX_RESULT];
    size_t start;
    size_t len_mantissa;
    int exp;
    bool is_negative;
} big_float_result;

#endif
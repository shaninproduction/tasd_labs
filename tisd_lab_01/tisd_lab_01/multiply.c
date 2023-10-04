#include "libs.h"
#include "constants.h"

void to_round(big_float_result *result)
{
    size_t len = result->len_mantissa;
    int start = len - MAX_LEN_MANTISSA_OUT;

    if (result->mantissa[start - 1] >= 5)
    {
        result->mantissa[start]++;
        result->exp++;
    }

    if (result->mantissa[start] >= 10)
    {
        long remainder = 0;

        for (size_t i = start; i < len; i++)
        {
            result->mantissa[i] += remainder;
            remainder = result->mantissa[i] / 10;
            result->mantissa[i] %= 10;
        }

        int cur = len;
        while (remainder)
        {
            for (size_t i = start - 1; i < len - 1; i++)
            {
                result->mantissa[i] = result->mantissa[i + 1];
            }
            
            result->mantissa[cur] = remainder % 10;
            cur++;
            remainder /= 10;

            start--;
        }

    }

    result->start = start;
}

int mult(big_int *integer, big_float *floating, big_float_result *result)
{
    if (integer->nums[0] == 0 || floating->mantissa[0] == 0)
    {
        result->len_mantissa = 1;
        return OK;
    }


    size_t len_int = integer->len;
    size_t len_float = floating->len_mantissa;

    for (size_t i = 0; i < len_int; i++)
    {
        long remainder = 0;
        for (size_t j = 0; j < len_float; j++)
        {
            int cur = result->mantissa[i + j] + integer->nums[len_int - i - 1] * floating->mantissa[len_float - j - 1] + remainder;
            remainder = cur / 10;
            result->mantissa[i + j] = cur % 10;
        }
       
        int cur = len_float;
        while (remainder)
        {
            result->mantissa[i + cur] = remainder % 10;
            cur++;
            remainder /= 10;
        }
    }

    size_t result_len = MAX_RESULT;
    for (size_t i = MAX_RESULT - 1; result->mantissa[i] == 0; i--)
    {
        result_len--;
    }
    
    result->len_mantissa = result_len;
    result->exp = result_len - floating->point_index + floating->exp;
    
    if (integer->is_negative && floating->is_negative)
    {
        result->is_negative = false;
    }
    else if (!integer->is_negative && !floating->is_negative)
    {
        result->is_negative = false;
    }
    else
    {
        result->is_negative = true;
    }

    if (result_len > MAX_LEN_MANTISSA_OUT)
    {
        to_round(result);
    }

    if (result->exp > 99999 || result->exp < -99999)
    {
        puts("ERR: TOO LARGE EXP");
        return EXP_ERR;
    }

    return OK;
}
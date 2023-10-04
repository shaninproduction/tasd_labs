#include "libs.h"
#include "constants.h"

void print_integer(big_int *num)
{
    for (size_t i = 0; i < num->len; i++)
    {
        printf("%d", num->nums[i]);
    }
    puts("");
}

void copy(char *buffer, big_int *num, bool has_sign, size_t len)
{
    bool no_zeros = false;
    int cur = 0;

    for (size_t i = has_sign; i < len; i++)
    {
        int digit = buffer[i] - '0';
        
        if (digit == 0 && !no_zeros)
            continue;
        
        if (digit)
            no_zeros = true;

        num->nums[cur++] = digit;
    }

    if (!no_zeros)
    {
        num->nums[0] = 0;
        num->len = 1;
        num ->is_negative = false;
        return;
    }

    num->len = cur;
}

int check_integer(char *integer, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(integer[i]))
        {
            if (i == 0 && (integer[i] == '+' || integer[i] == '-'))
                continue;
            puts("INVALID INTEGER");
            return INVALID_INPUT;
        }
    }
    
    return OK;
}

static int read_str_in_buffer(char *buffer, size_t *len, int size)
{
    if (!fgets(buffer, size, stdin))
    {
        puts("READ INPUT ERROR");    
        return READ_ERR;
    }

    if (buffer[0] == '\n')
    {
        puts("INVALID INTEGER INPUT");
        return INVALID_INPUT;
    }

    *len = strlen(buffer);
 
    if (buffer[*len - 1] != '\n')
    {
        puts("OVERFLOW INPUT");
        return OVERFLOW_ERR; 
    }

    buffer[*len - 1] = '\0';
    (*len)--;

    return OK;
}

int check_sign(char *buffer, bool *is_negative, size_t len, bool *has_sign)
{
    if (buffer[0] == '-')
    {
        *has_sign = true;
        *is_negative = true;
        if (len == 1)
        {
            puts("INVALID INTEGER");
            return INVALID_INPUT;
        }
    }
    else if (buffer[0] == '+')
    {
        *has_sign = true;
        *is_negative = false;
        if (len == 1)
        {
            puts("INVALID INTEGER");
            return INVALID_INPUT;
        }
    }
    else
    {
        *is_negative = false;
    }

    return OK;
}

int read_integer(big_int *num)
{
    int err;
    bool has_sign = false;
    char buffer[MAX_LEN_INT + 3];
    size_t len;

    err = read_str_in_buffer(buffer, &len, MAX_LEN_INT + 3);

    if (err)
        return err;

    err = check_sign(buffer, &num->is_negative, len, &has_sign);

    if (err)
        return err;

    if (!has_sign)
    {
        if (len == MAX_LEN_INT + 1)
        {
            puts("INVALID INTEGER INPUT");
            return INVALID_INPUT;
        }
    }

    err = check_integer(buffer, len);

    if (err)
        return err;

    copy(buffer, num, has_sign, len);

    return OK;
}
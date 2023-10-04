#include "libs.h"
#include "constants.h"

int normalize(big_float *num)
{
    size_t counter = 0;
    
    for (size_t i = 0; num->mantissa[i] == 0 && counter != num->len_mantissa; i++)
    {
        counter++;
    }

    if (counter == num->len_mantissa)
    {
        return OK;
    }

    for (size_t i = 0; i < counter; i++)
    {
        for (size_t j = 0; j < num->len_mantissa - 1; j++)
        {
            num->mantissa[j] = num->mantissa[j + 1];
        }
        num->len_mantissa--;
    }

    num->exp -= counter;

    if (counter)
        num->point_index = num->len_mantissa;
    return OK;   
}

static int read_str_in_buffer(char *buffer, size_t *len, int size)
{
    if (!fgets(buffer, size, stdin))
    {
        puts("READ INPUT ERROR");    
        return READ_ERR;
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

void print_float(big_float *num)
{
    if (num->is_negative)
        printf("-");

    for (size_t i = 0; i < num->len_mantissa; i++)
    {
        if ((int) i == num->point_index)
        {
            printf(".");
        }

        printf("%d", num->mantissa[i]);
    }
    printf(" E%d\n", num->exp);
}

int get_mantissa(char *buffer, big_float *num)
{
    int i;
    int cur = 0;
    int point_index;
    bool no_zeros = false;
    bool has_point = false;
    bool has_sign = false;

    if (buffer[0] == '-')
    {
        has_sign = true;
        num->is_negative = true;
    }
    else
    {
        if (buffer[0] == '+')
            has_sign = true;
        num->is_negative = false;
    }


    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '.')
        {
            if (has_point)
            {
                puts("INVALID FLOAT INPUT: TWO DOTS");
                return INVALID_INPUT;
            }

            point_index = cur;
            has_point = true;
            no_zeros = true;

            continue;
        }

        if (!isdigit(buffer[i]))
        {
            if (i == 0 && has_sign)
                continue;

            puts("INVALID MANTISSA INPUT");
            return INVALID_INPUT;
        }

        int digit = buffer[i] - '0';
        
        if (digit)
            no_zeros = true;

        if (digit == 0 && !no_zeros)
            continue;
        
        
        if (cur + 1 > MAX_LEN_MANTISSA_IN)
        {
            puts("MANTISSA OVERFLOW");
            return INVALID_INPUT;
        }

        num->mantissa[cur++] = digit;
    }
    
    if (!no_zeros)
    {
        num->mantissa[0] = 0;
        num->len_mantissa = 1;
        num->is_negative = false;
        num->point_index = 0;
        return OK;
    }

    num->len_mantissa = cur;

    if (!has_point)
    {
        num->point_index = 0;
    }
    else
    {
        num->point_index = num->len_mantissa - point_index;
    }

    return OK;
}

int get_exponent(char *buffer, size_t len, big_float *num, bool is_two_parts)
{
    int cur = 0;
    int exponent_int;
    bool has_sign = false;
    bool is_negative = false;
    char exponent[MAX_EXP];

    if (buffer[is_two_parts] == '-')
    {
        has_sign = true;
        is_negative = true;
    }
    else if (buffer[is_two_parts] == '+')
    {
        has_sign = true;
    }

    for (size_t i = is_two_parts; i < len; i++)
    {
        if (!isdigit(buffer[i]))
        {
            if (i == (int) is_two_parts && has_sign)
                continue;

            printf("ERR: EXP NOT A DIGIT\n");
            return INVALID_INPUT;
        }
        
        if (cur + 1 > MAX_EXP)
        {
            puts("ERR: OVERFLOW EXP");
            return INVALID_INPUT;
        }

        exponent[cur++] = buffer[i];
    }
    exponent_int = atoi(exponent);

    num->exp = ((int) pow(-1, is_negative)) * exponent_int;
    return OK;
}

int split_buffer_by_parts(char *buffer, char parts[MAX_PARTS][MAX_FLOAT_LEN_IN], int *parts_count)
{
    char *elem = strtok(buffer, " ");

    while (elem != NULL)
    {
        if (*parts_count > MAX_PARTS)
        {
            puts("INVALID FLOAT INPUT");
            return INVALID_INPUT;
        }

        strcpy(parts[(*parts_count)++], elem);
        elem = strtok(NULL, " ");
    }

    return OK;
}

int get_float(char *buffer, big_float *num)
{
    int err;
    int parts_count = 0;
    char parts[MAX_PARTS][MAX_FLOAT_LEN_IN];

    err = split_buffer_by_parts(buffer, parts, &parts_count);

    if (err)
        return err;

    if (parts_count == 1)
    {
        num->exp = 0;
        err = get_mantissa(parts[0], num);    
    
        if (err)
            return err;
    }
    else if (parts_count == 2)
    {
        if (parts[1][0] != 'e' && parts[1][0] != 'E')
        {
            puts("INVALID FLOAT INPUT");
            return INVALID_INPUT;
        }

        err = get_mantissa(parts[0], num);

        if (err)
            return err;

        err = get_exponent(parts[1], strlen(parts[1]), num, true);
        
        if (err)
            return err;
    }
    else
    {
        if (parts[1][0] != 'e' && parts[1][0] != 'E')
        {
            puts("INVALID FLOAT INPUT");
            return INVALID_INPUT;
        }

        err = get_mantissa(parts[0], num);

        if (err)
            return err;

        err = get_exponent(parts[2], strlen(parts[2]), num, false);
        
        if (err)
            return err;
    }

    return OK;
}

int read_float(big_float *num)
{
    int err;
    char buffer[MAX_FLOAT_LEN_IN + 2];
    size_t len_buffer;

    err = read_str_in_buffer(buffer, &len_buffer, MAX_FLOAT_LEN_IN + 2);
    
    if (err)
        return err;

    if (len_buffer == MAX_FLOAT_LEN_IN && (buffer[0] != '-' || buffer[0] != '+'))
    {
        puts("BUFFER LEN > MAX_FLOAT_LEN_IN");
        return OVERFLOW_ERR;
    }

    if (strlen(buffer) == 1 && (buffer[0] == '-' || buffer[0] == '+'))
    {
        puts("INVALID INPUT");
        return INVALID_INPUT;
    }

    err = get_float(buffer, num);

    if (err)
        return err;

    err = normalize(num);

    if (err)
        return err;

    return OK;
}
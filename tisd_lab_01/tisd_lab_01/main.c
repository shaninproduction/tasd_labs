#include "libs.h"
#include "constants.h"
#include "io.h"
#include "multiply.h"

void print_result(big_float_result *num)
{
    if (num->is_negative)
        printf("-");

    printf("0.");
    for (int i = num->len_mantissa - 1; i >= (int) num->start; i--)
    {
        printf("%d", num->mantissa[i]);
    }
    printf(" E%d\n", num->exp);
}

// void print_result_debug(big_float_result *num)
// {
//     for (size_t i = 0; i < MAX_RESULT; i++)
//     {
//         printf("%d ", num->mantissa[i]);
//     }
//     puts("");
// }

int main(void)
{
    int err;
    big_int integer;
    big_float floating;
    big_float_result result = {
        {0},
        0,
        0,
        0,
        false
    };

    puts("            Умножение целого числа на вещественное         ");
    puts("Описание программы: пользователь вводит два числа: целое и вещественное,");
    puts("    далее над ними производится умножение и результат выводится в нормализованном виде");
    puts("1. Первым вводится целое число в формате [+-]N,");
    puts("    где N - длина числа не более 40 символов");
    puts("2. Вторым вводится вещественнео число в формате [+-]m.n [+-Ee]K1,");
    puts("    где m + n не более 30 символов, значение экспоненты [-99999 ; 99999]\n");

    printf("             >+---------1---------2---------3---------4---------5\n");
    printf("Введите целое: ");
    err = read_integer(&integer);

    if (err)
        return err;
    printf("                    >+---------1---------2---------3---------4---------5\n");
    printf("Введите вещественное: ");
    err = read_float(&floating);

    if (err)
        return err;

    err = mult(&integer, &floating, &result);

    if (err)
        return err;

    printf("Результат: ");
    print_result(&result);
    return OK;
}

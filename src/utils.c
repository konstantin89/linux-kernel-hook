#include "utils.h"


uintptr_t hex_addr_to_pointer(const char *str)
{
    uintptr_t sum;

    /* Go through str char by char and accumulate into sum */
    for (sum = 0; *str != '\0'; str++) {
        sum *= 16;
        if (*str >= '0' && *str <= '9')
            sum += (*str - '0');
        else if (*str >= 'a' && *str <= 'f')
            sum += (*str - 'a') + 10;
        else if (*str >= 'A' && *str <= 'F')
            sum += (*str - 'A') + 10;
        else
            return 0;
    }

    return sum;
}

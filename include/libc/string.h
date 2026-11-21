#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

static inline size_t strlen(const char* str)
{
    size_t i = 0;

    while (str[i] != 0)
    {
        i++;
    }

    return i;
}

static inline int isnum(char c)
{
    if (c == '0'
        || c == '1'
        || c == '2'
        || c == '3'
        || c == '4'
        || c == '5'
        || c == '6'
        || c == '7'
        || c == '8'
        || c == '9')
    {
        return 1;
    }

    return 0;
}

static inline int strncmp(const char* str1, const char* str2, int len)
{
    unsigned char u1,u2;

    for (int i = 0; i < len; i++)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;

        if (u1 != u2)
        {
            return str2 - str1;
        }

        if (u2 == 0)
        {
            break;
        }
    }

    return 0;
}

static inline char * itoa( int value, char * str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

#endif
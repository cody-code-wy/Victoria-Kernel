/*
 * stdlib.h
 */

#include <stdint.h>

// Typedefs

typedef uint32_t size_t;

typedef uint16_t wchar_t;

// Functions

/**
 * @brief convert integers to string representataion in specific base
 *
 * itoa will take one @c int64_t or compatable types @< int32_t int16_t int8_t uint32_t uint16_t uint8_t >@ and @c uint64_t (though it will be treated as a signed type so values larger than 9,223,372,036,854,775,807 will appear as negitive using Two's complement) 
 **/
char* itoa( int64_t value, char* strout, int8_t base );

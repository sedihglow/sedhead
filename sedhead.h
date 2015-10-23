/*
    stuff i use for stuff.
*/

#ifdef __SED_ERR__
    #include "err_handle/err_handle.h"  /* error handling functions */
#endif
#ifdef __SED_NUM__
    #include "get_num/get_num.h"        /* convert strings to int types */
#endif

#ifdef __SED_LINUX__
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/time.h>
#endif

#ifndef _SED_HEAD_
#define _SED_HEAD_
#include <sys/types.h>
#include <stdio.h>                  
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>


#ifndef __FL_CONSTS__
#define __FL_CONSTS__
/* Use memcpy to set a float value, causing the proper value to appear instead
   of the min/max. (example: Nan, -Nan, etc.), (memset gives improper results) */
#define set_float(num, set)    memcpy(&num, &set, sizeof(num))
#define set_double(num, set)   set_float(num,set)
#define set_nan(num, set)      set_float(num, set)
#define set_inf(num, set)      set_float(num,set)

/* Use these definitions placed in memory for the above macros in set.
   example: int32_t fnan = PF_NAN;
            int64_t dnegInf = ND_INF;

            set_float(num, fnan);
            set_double(num, dneginf); */

/* 32 bit float */
#define PF_NAN  0x7fc00000    /* positive NAN */
#define NF_NAN  0xffc00000    /* negetive NAN */

#define PF_INF  0x7f800000    /* positive INF */
#define NF_INF  0xff800000    /* negetive INF */

/* 64 bit double */
#define PD_NAN  0x7ff8000000000000    /* positive NAN */
#define ND_NAN  0xfff8000000000000    /* negetive NAN */

#define PD_INF  0x7ff0000000000000    /* positive INF */
#define ND_INF  0xfff0000000000000    /* negetive INF */
#endif 

                    /* __restrict */
#ifndef Restrict
#define Restrict __restrict
#endif

                    /* bool */
#ifdef true 
#undef true
#endif
#ifdef false 
#undef false 
#endif
typedef enum {false, true} Bool;

                    /* min/max */
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

                    /* input */
/* clears the input buffer using variable char ch; and getchar (). */
#define clear_buff()                                    \
{                                                       \
    char _TR_SH_ = '\0';                                \
    while(((ch) = getchar()) != '\n' && (ch) != EOF);   \
} /* end clear_buff */

/* get 1 character from stdin using getchar, clear buffer afterwards if
   needed */
#define getChar(input)                \
{                                     \
    if(((input) = getchar()) != '\n'){\
        clear_buff();}                \
} /* end getChar */

/* get a single character from stdin and loop untill input is correct 
   note: sets the single character to a capital letter */
#define yesNo(input, string, ...)                               \
{                                                               \
    do                                                          \
    {                                                           \
        printf((string), __VA_ARGS__);                          \
        getChar((input));                                       \
        (input) = toupper((input));                             \
    }while(input != 'Y' && input != 'N');                       \
} /* end getChar_check #}}} */

/* get a line of input from a buffer, clears the buffer if required */
#define getLineInput(input, max, fpntr, len)\
{                                           \
    fgets((input),(max),(fpntr));           \
    (len) = strlen((input)) - 1;            \
    if(input[(len)] == '\n'){               \
        input[(len)] = '\0';}               \
    else{                                   \
        clear_buff(); }                     \
} /* end getLineInput */

                    /* other */
/* create a bit mask for a given range of bits. start, end. (lsb,msb) */
#define create_mask(start, end, resMask)                                    \
{                                                                           \
    int32_t ___S_;                                                          \
    if((start) > (end)){                                                    \
        errmsg("create_mask: start > end, no mask was generated.");}        \
                                                                            \
    resMask = 0;                                                            \
    for((___S_) = (start); i <= (end); ++(___S_)){                          \
        (resMask) |= 1 << (___S_);}                                         \
} /* end create_mask */

/* adds all the ascii values in a character array together */
#define sumArr(array, size, res)                              \
{                                                             \
    int32_t ___NC_;                                           \
    (res) = 0;                                                \
    for((___NC_) = 0; (___NC_) < (size); ++(___NC_)){         \
        (res) += (array[(___NC_)]);}                          \
} /* end sumChars */

/* generated a random string, excluding 0x1 - 0x1f and 0x7f, places it in 
   (string). mod value implicitly ignores 0x7f. */
#define gen_string(string, size)                                        \
{                                                                       \
    int32_t __K_U_ = 0;                                                 \
    int32_t _SUM__ = 0;                                                 \
    char _N_CH_ = NULL; /* pointer to use with string */                \
                                                                        \
    if((string) == NULL)                                                \
    {                                                                   \
        (string) = (char*) malloc(sizeof(char)*(size));                 \
        memset((string), '\0', (size));                                 \
    }                                                                   \
                                                                        \
    /* seed random using sumArr */                                      \
    sumArr((string), (size), _SUM__);                                   \
    srandom(_SUM__);                                                    \
                                                                        \
    (string)[size-1] = '\0'; /* make sure there is a null at the end */ \
    for((__K_U_) = 0; (__K_U_) < (size)-1; ++__K_U_)                    \
    {                                                                   \
        _N_CH_ = (string)[(__K_U_)];                                    \
        do                                                              \
        {                                                               \
            _N_CH_ = random() % 0x7f;                                   \
        }while(_N_CH_ < 0x20 && _N_CH_ != 0);                           \
        (string)[(__K_U_)] = _N_CH_;                                    \
    }                                                                   \
} /* end gen_string */

/* vectorizes a function funct, its C99 as fuck tho.
   -Type is the type of pointer used. (VA_ARGS could be void for example.). 
   -... is a variable argument list.
   -will execute every argument into the function.
   -funct only takes in one argument. */
#define apply_funct(type, funct, ...)                      \
{                                                          \
    void *stopper = (int32_t[]){0};                        \
    type **apply_list = (type*[]){__VA_ARGS__, stopper};   \
    int32_t __GH_;                                         \
                                                           \
    for(__i_ = 0; apply_list[__i_] != stopper; ++__i_){    \
        (funct)(apply_list[__i_]);}                        \
} /* end apply_funct */
    
/* apply free to every pointer given in the argument list using the
   apply_funct macro */
#define free_all(...)   apply_funct(void, free, __VA_ARGS__)
#endif

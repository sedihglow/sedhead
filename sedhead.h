/*
    stuff i use for stuff.
*/

#ifndef _SED_HEAD_
#define _SED_HEAD_
#include <sys/types.h>
#include <string.h>   /* memcpy */

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
typedef enum {false, true} bool;

                    /* min/max */
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

                    /* input */
/* clears the input buffer using variable char ch; and getchar (). */
#ifndef CLEAR_BUFF
#define CLEAR_BUFF
#define clear_buff(ch) while(((ch) = getchar()) != '\n' && (ch) != EOF)
#endif

/* get a line of input from a buffer, clears the buffer if required */
#define getLineInput(input, max, fpntr, len)\
{                                           \
    char __ch__ = '\0'                      \
    fgets((input),(max),(fpntr));           \
    (len) = strlen((input)) - 1;            \
    if(input[(len)] == '\n'){               \
        input[(len)] = '\0';}               \
    else{                                   \
        clear_buff(__ch__); }               \
} /* end getLineInput */

                    /* other */
/* adds all the ascii values in a character array together */
#define sumChars(increment, array, size, res)                 \
{                                                             \
    for((increment) = 0; (increment) < (size), ++(increment)){\
        (res) += (array[(increment)]);}                       \
} /* end sumChars */

/* vectorizes a function funct, its C99 as fuck tho.
   -Type is the type of pointer used. (VA_ARGS would be void for example.). 
   -... is a variable argument list.
   -will execute every argument into the function.
   -funct only takes in one argument. */
#define apply_funct(type, funct, ...)                      \
{                                                          \
    void *stopper = (int[]){0};                            \
    type **apply_list = (type*[]){__VA_ARGS__, stopper};   \
    int __i_;                                              \
    for(__i_ = 0; apply_list[__i_] != stopper; ++__i_){    \
        (funct)(apply_list[__i_]);}                        \
} /* end apply_funct */
    
/* apply free to every pointer given in the argument list using the
   apply_funct macro */
#define free_all(...)   apply_funct(void, free, __VA_ARGS__);
#endif

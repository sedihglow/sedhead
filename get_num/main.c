#include "get_num.h"

#include <stdio.h>
#include <limits.h>

int main()
{

    
    printf("INT LIMITS low: %d, high %d\n", INT_MAX, INT_MIN);
    getInt("398475d4358", GN_BASE_10 | GN_NOEXIT_, "name"); 
    printf("\n overflow \n");
    getInt("93457438957893475893475893475843975893475894375893475894375893475893475893475893475893475893759839847587593487589435894389435789437589437589437589437589437598437589434358", GN_BASE_10 | GN_NOEXIT_, "name"); 
    getInt("-1", GN_BASE_10 | GN_NOEXIT_ | GN_GT_O, "name"); 
    getInt("33424538458", GN_BASE_10 | GN_NOEXIT_, "name"); 
    getInt(NULL, GN_BASE_10 | GN_NOEXIT_, "name"); 
    getInt("-398458", GN_BASE_10 | GN_NONEG | GN_NOEXIT_, "name"); 
    return 0;
} 

/* 
    used for testing the err_handle.h header,

    may randomly change to check shit. Might not be implemented to test
    everything completely. Will decide on that when the time comes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "err_handle.h"



int main(int argc, char *argv[])
{

    errno = E2BIG;
    
    errMsg("errmsg");

    noerr_msg(NULL);

    noerrExit("noerrExit");

    errnumExit(15, "string");

    exit(EXIT_SUCCESS);
} 

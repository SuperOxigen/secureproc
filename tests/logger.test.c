
#include "secureproc/logger.h"



int main(void)
{
    SECDEBUG("%s\n", "I am debug!");

    SECINFO("%s\n", "I am info!");

    SECWARN("%s\n", "I am warning!");

    SECERR("%s\n", "I am error!");

    return 0;
}


#include <string.h>

#include "secureproc/safestring.h"
#include "secureproc/logger.h"

typedef enum _TestStatus
{
    TEST_SKIP,
    TEST_PASS,
    TEST_FAIL
}
TestStatus;

TestStatus strlcpy_test1(void)
{
    char    buf[10];

    if (strlcpy(buf, "Hello World", sizeof(buf)) >= sizeof(buf))
    {
        SECINFO("Test 1 (a) [PASS]: copy feedback\n");
    }
    else
    {
        SECWARN("Test 1 (a) [FAIL]: copy feedback\n");
        return TEST_FAIL;
    }

    if (!buf[sizeof(buf) - 1])
    {
        SECINFO("Test 1 (b) [PASS]: null terminated\n");
    }
    else
    {
        SECWARN("Test 1 (b) [FAIL]: null terminated\n");
        return TEST_FAIL;
    }

    if (!strcmp(buf, "Hello Wor"))
    {
        SECINFO("Teat 1 (c) [PASS]: truncated string\n");
    }
    else
    {
        SECWARN("Teat 1 (c) [FAIL]: truncated string\n");
        return TEST_FAIL;
    }

    return TEST_PASS;
}

TestStatus strlcpy_test2(void)
{
    char    buf[25];

    if (strlcpy(buf, "Hello World", sizeof(buf)) == 11)
    {
        SECINFO("Test 2 (a) [PASS]: string length correct.\n");
    }
    else
    {
        SECWARN("Test 2 (a) [FAIL]: string length correct.\n");
    }

    if (!buf[11])
    {
        SECINFO("Test 2 (b) [PASS]: null terminated\n");
    }
    else
    {
        SECWARN("Test 2 (b) [FAIL]: null terminated\n");
        return TEST_FAIL;
    }

    if (!strcmp(buf, "Hello World"))
    {
        SECINFO("Teat 2 (c) [PASS]: truncated string\n");
    }
    else
    {
        SECWARN("Teat 2 (c) [FAIL]: truncated string\n");
        return TEST_FAIL;
    }

    return TEST_PASS;
}

TestStatus strlcpy_test3(void)
{
    char    buf[25];

    memset(buf, 0, sizeof(buf));

    if (strlcpy(buf, "Hello World", 0) == 11)
    {
        SECINFO("Test 3 (a) [PASS]: string length correct.\n");
    }
    else
    {
        SECWARN("Test 3 (a) [FAIL]: string length correct.\n");
        return TEST_FAIL;
    }

    if (buf[0])
    {
        SECWARN("Test 3 (b) [FAIL]: wrote to empty buffer.\n");
        return TEST_FAIL;
    }
    else
    {
        SECINFO("Test 3 (b) [PASS]: did not write to empty buffer.\n");
    }


    return TEST_PASS;
}

int strlcpy_test(void)
{
    int         failures = 0,
                passes = 0;
    TestStatus  res;

    res = strlcpy_test1();
    if (TEST_FAIL == res)
        failures++;
    else
        passes++;

    res = strlcpy_test2();
    if (TEST_FAIL == res)
        failures++;
    else
        passes++;

    res = strlcpy_test3();
    if (TEST_FAIL == res)
        failures++;
    else
        passes++;

    return failures;
}

int main(void)
{
    strlcpy_test();
    return 0;
}

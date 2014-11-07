#include <string.h>
#include <jni.h>
#include  <stdio.h>
#include  <stdlib.h>

/**
 * This is code for our adb client that can utilize the ptrace commands as well.
 */

int main(int argc, char **argv)
{
        int i = 1;
        i+=2;

        printf("Hello, world (i=%d)!\n", i);

        return 0;
        exit(0);
}


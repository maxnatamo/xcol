#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *xcol_util_dectohex(unsigned char i) {
    char *buffer = calloc(2, sizeof(char));
    sprintf(buffer, "%X", i);

    // Add hexidecimal padding.
    if(strlen(buffer) <= 1) {
        buffer[1] = buffer[0];
        buffer[0] = '0';
    }
    return buffer;
}

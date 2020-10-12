#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "base64.h"
#include <assert.h>

int main() {
    const char *input = "hello world";
    char *encoded;
    char *decoded;

    /* encode the data */
    encoded = base64_encode(input);
    printf("encoded: %s", encoded); /* encoded data has a trailing newline */

    /* decode the data */
    decoded = base64_decode(encoded);
    printf("decoded: %s\n", decoded);

    /* compare the original and decoded data */
    assert(strcmp(input, decoded) == 0);

    free(encoded);
    free(decoded);
    return 0;
}
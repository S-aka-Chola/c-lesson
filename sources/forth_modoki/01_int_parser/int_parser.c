#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static const char* const input = "123 456  1203";


int main() {
    int answer1 = 0;
    int answer2 = 0;
    int answer3 = 0;

    // write something here.

    const char* const input4 = input + 4;

    printf("input = %s\n", input);
    printf("input + 4 = %s\n", input4);
    printf("input[0] = %c\n", input[0]);

    answer1 = atoi(input);
    answer2 = atoi(input+4);
    answer3 = atoi(input+8);

    printf("answer1 = %d\n", answer1);
    printf("answer2 = %d\n", answer2);
    printf("answer3 = %d\n", answer3);

    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);
    assert(answer3 == 1203);

    return 0;
}

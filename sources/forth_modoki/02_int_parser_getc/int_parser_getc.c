#include "clesson.h"
#include <assert.h>

/*
cc cl_getc.c int_parser_getc.c
*/

// add original code here.


typedef enum{
    NUMBER,
    SPACE,
} Token;

int is_numeric(int c){
    return ( '0' <= c ) && ( c <= '9');
}

int is_space(int c){
    return ( c == ' ');
}

int parse_one(int *out_val, Token *out_type){
    //
    // c is used to store the cl_getc().
    // as initial value, c is set to be 0.
    // this means, c is not number nor space.
    //
    static int c = 0;

    //
    // cl_getc() for the first step.
    // from second attempt, c = NUMBER or SPACE,
    // so this process will be skipped.
    //
    if (c == 0) {
        c = cl_getc();
    }

    //
    // getc and compose Token
    //
    if (is_numeric(c)) {
        //
        // convert char to int
        //  e.g.)
        //    '0' : 0x30, '1' : 0x31 .. '9' : 0x39
        //
        *out_val = c - 0x30; 
        *out_type = NUMBER;

        //
        // read remaining number
        //  e.g.)
        //    '1' -> out_val = 1
        //    '5' -> out_val = 15
        //    '3' -> out_val = 153
        //
        while (c = cl_getc(), is_numeric(c)) {
            *out_val = *out_val * 10 + (c - 0x30);
        }
    }
    else if (is_space(c)) {
        *out_val = 0;
        *out_type = SPACE;

        //
        // skip remaining space ' '
        //
        while (c = cl_getc(), is_space(c)) {}
    }
    else {
    }

    /*
    if (*out_type == NUMBER) {
        printf("out_val = %d\n", *out_val);
        printf("out_type = NUMBER\n");
    }
    else if (*out_type == SPACE) {
        printf("out_val = %d\n", *out_val);
        printf("out_type = SPACE\n");
    }
    else {
    }
    */

    return c;
}



int main() {
    int answer1 = 0;
    int answer2 = 0;

    // write something here.
    Token answer1_type;
    Token answer2_type;
    parse_one(&answer1, &answer1_type);
    parse_one(&answer2, &answer2_type);
    parse_one(&answer2, &answer2_type);

    // sample for cl_getc() usage.
    /*
    int c;

    while((c = cl_getc()) != EOF) {
        printf("%c\n",c );
    }
    */


    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);

    return 0;


}




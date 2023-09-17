#include "clesson.h"
#include <assert.h>

/*
cc cl_getc.c int_parser_getc.c
*/

// add original code here.

//
// c is buffer used to store the cl_getc().
// when cl_getc_set_src() is called,
// c is needed to set to be 0.
// It (c is set to be 0) means that
// it is first time to read the target string.
//
static int c = 0;

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

void test_parse_one_123() {
    int answer;
    Token token;

    //
    // prerequisite for test:
    //  set input as "123"
    //  c is also set to be 0 to indicate the cursor refresh.
    //
    cl_getc_set_src("123"); c = 0;

    //
    // parse_one test
    //
    parse_one(&answer, &token);

    assert(answer == 123);
    assert(token == NUMBER);

    return;
}

void test_parse_one_123_456() {
    int answer;
    Token token;

    //
    // prerequisite for test:
    //  set input as "123 456"
    //  c is also set to be 0 to indicate the cursor refresh.
    //
    cl_getc_set_src("123 456"); c = 0;

    //
    // parse_one test
    //
    // 1.
    parse_one(&answer, &token);

    assert(answer == 123);
    assert(token == NUMBER);

    // 2.
    parse_one(&answer, &token);

    assert(answer == 0);
    assert(token == SPACE);

    // 3.
    parse_one(&answer, &token);

    assert(answer == 456);
    assert(token == NUMBER);

    return;
}


int main() {
    int answer1 = 0;
    int answer2 = 0;

    // write something here.

    //
    // test
    //
    test_parse_one_123();
    test_parse_one_123_456();

    //
    // set input as "123 456"
    // c is also set to be 0 to indicate the cursor refresh.
    //
    cl_getc_set_src("123  456"); c = 0;

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




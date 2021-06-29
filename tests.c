//
// Created by Mohammad  Boustta on 4/20/21.
//
#include "../minishell.h"
#include "simple-test.h"

#if (1)

/*
 * Start writing tests for the parser.
 */

void run_test(char *input) {
    t_lexer *l = new_lexer(input, (int) strlen(input));
    parse_and_execute(l);
}

/* SIMPLE_TEST_PRINT_FUN may be redefined like so. default is `printf` */

/* colour output is on by default, but can be disabled */
/* #define SIMPLE_TEST_USE_COLOUR false */


/* global variables, functions, and includes must come before BEGIN_TEST */
char *global_s;

/* a teardown function must be of type `void function(void)` and can be called
 * by TESTs which include them using the TEARDOWN macro. the call occurs either
 * after an ASSERT fails or after the TEST is finished.
 *
 * the macro may be called multiple times, but only the most recently set
 * teardown function will be called.
 *
 * here i'm using it to free memory that's alloced inside tests below */
void teardown_fun(void) {
    free(global_s);
}

/*
 * Defining the input tests and the expected output.
 */

char *inputs[256] = {
        "echo \"Hello World Moooo ii $x $SHELL $ $9 jdjhdhdhjdh $HOME\"",
        "echo \"Hello $SHELL\"",
        "echo \"I would like to say \\\" Go for it \\\"\"",
        "echo 'Hello 'World' >> Again | again'",
        "echo \"AB\"CD\"EF\"",
        "echo \"AB\" CD \"EF\"",
        "echo \"AB\"'CD'\"EF\"",
        "echo \"AB\" 'CD' \"EF\"",
        "echo \"AB\" 'CD  ' \"EF\"",
        "echo \"\\\\\"",
        "echo \"\\$\\\"\"",
        "echo $USER",
        "echo Hello\\\\ world",
        "echo Hello\\ world",
        "echo \"\\$\\\"\"",
        "echo \\\\",
        "echo '\\$\'",
        "echo \"e\"\"c\"\"h\"\"o\" 'e''c'\"h\"\"o\" 'e'\"c\"'h'\"o\"",
        "echo '\"\"\"\"\"\"\"\"\"\",         wtf     :\"\"'",
        "echo \"~\"",
        "echo '~~'",
        "echo helloworld\"'''$USER'''\"1234556789",
        "echo $USER$USER$USER",
        "echo '$USER'",
        "echo $USER",
        "echo ''\\''\"a|\"\\'q'a'\\a'w'",
        "echo \"\\$PWD\" \"\\PWD\"",
        "echo \\'\\\"\\\\ \"\\hello\\$PWD\"",
        "echo \"\\hello \\$PWD\"",
        // // ENV EXPANSIONS + ESCAPE
        "echo \\hello \\$PWD",
        "echo test     \\    test",
        "echo $TEST",
        "echo \"$TEST\"",
        "echo '$TEST'",
        "echo \"$TEST$TEST$TEST\"",
        "echo \"$TEST$TEST=lol$TEST\"",
        "echo \"   $TEST lol $TEST\"",
        "echo $TEST$TEST$TEST",
        "echo \"\\$TEST\"",
        "echo \"$=TEST\"",
        "echo \"$\"",
        "echo \"$1TEST\"",
        "echo \"$T1TEST\"",
        "echo         \\'\\\"\\\\",
        "echo \\'",
        "echo \"'\\''\"",
        "echo hello '\\' ';' \"   '\\' \\\" \" \\\" \"$SHELL\\\\\\\"\\~\\;\"",
        "echo \"$111TEST\"",
        "echo \"$USER111\"",
};


char *expected[256] = {
        "echo Hello World Moooo ii  /bin/zsh $  jdjhdhdhjdh /Users/moboustt",
        "echo Hello /bin/zsh",
        "echo I would like to say \" Go for it \"",
        "echo Hello World >> Again | again",
        "echo ABCDEF",
        "echo AB CD EF",
        "echo ABCDEF",
        "echo AB CD EF",
        "echo AB CD   EF",
        "echo \\",
        "echo $\"",
        "echo moboustt",
        "echo Hello\\ world",
        "echo Hello world",
        "echo $\"",
        "echo \\",
        "echo \\$",
        "echo echo echo echo",
        "echo \"\"\"\"\"\"\"\"\"\",         wtf     :\"\"",
        "echo ~",
        "echo ~~",
        "echo helloworld'''moboustt'''1234556789",
        "echo mobousttmobousttmoboustt",
        "echo $USER",
        "echo moboustt",
        "echo '\"a|\"\\qaaw",
        "echo $PWD \\PWD",
        "echo '\"\\ \\hello$PWD",
        "echo \\hello $PWD",
        // // ENV EXPANSIONS + ESCAPE
        "echo hello $PWD",
        "echo test   test",
        "echo ",
        "echo ",
        "echo $TEST",
        "echo ",
        "echo =lol",
        "echo     lol ",
        "echo ",
        "echo $TEST",
        "echo $=TEST",
        "echo $",
        "echo TEST",
        "echo ",
        "echo '\"\\",
        "echo '",
        "echo '\\''",
        "echo hello \\ ;    '\\' \"  \" /bin/zsh\\\"\\~\\;",
        "echo 11TEST",
        "echo "
};

const size_t n_of_tests = 49;

char *SYNTAX_ERROR_INPUT[256] = { // SYNTAX ERROR
        ";; test",
        "| test",
        "echo > <",
        "echo | |",
            "<",
        ";;",
        ";",
        "|",
        "||",
        ";@@;",
        "| |",
        "ls;;",
        "ls; ;",
        "ls||",
        "ls | |",
        "echo <",
        "echo >>",
        "echo >",
        "echo > ;",
        "echo > |"
};

/* must appear before an (optional) REGISTER_TEARDOWN and all TESTs */
BEGIN_TEST

        TEST("string comparison")
            {
#if (1)
                for (size_t i = 0; i < n_of_tests; ++i) {
                    char *s = inputs[i];
                    char *expec = expected[i];
                    run_test(s);
#endif
#if (0)
                    run_test("echo $USER$USER$USER");
                    char *expec = "echo mobousttmobousttmoboustt";
#endif
                    /* strings are compared by content, so this assertion succeeds */
                    printf("i == %zu\n", i);
                    ASSERT_EQ(expec, stream);
                }
            }
/* must come after all TESTs */
END_TEST

#endif
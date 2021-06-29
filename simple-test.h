#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>


/**************************
 *  CONFIGURATION MACROS  *
 **************************/

#ifndef SIMPLE_TEST_USE_COLOUR
#define SIMPLE_TEST_USE_COLOUR true
#endif

#ifndef SIMPLE_TEST_PRINT_FUN
#define SIMPLE_TEST_PRINT_FUN printf
#endif


/**************************************************
 *  INTERNAL FUNCTIONALITY. DO NOT CALL DIRECTLY  *
 **************************************************/

enum simple_test_type {
    SIMPLE_TEST_BOOL,
    SIMPLE_TEST_INT,
    SIMPLE_TEST_UNSIGNED,
    SIMPLE_TEST_CHAR,
    SIMPLE_TEST_STRING,
    SIMPLE_TEST_POINTER,
    SIMPLE_TEST_UNKNOWN,
    SIMPLE_TEST_MISMATCH,
};

enum simple_test_cond {
    SIMPLE_TEST_TRUE,
    SIMPLE_TEST_FALSE,
    SIMPLE_TEST_EQ,
    SIMPLE_TEST_NEQ,
    SIMPLE_TEST_GT,
    SIMPLE_TEST_LT,
    SIMPLE_TEST_GEQ,
    SIMPLE_TEST_LEQ
};

static intmax_t simple_test_il, simple_test_ir;
static uintmax_t simple_test_ul, simple_test_ur;
static char *simple_test_sl, *simple_test_sr;
static void *simple_test_pl, *simple_test_pr;

static int simple_test_assert(enum simple_test_type t,
                              enum simple_test_cond c, ...)
{
    va_list ap;
    bool two = !(c == SIMPLE_TEST_TRUE || c == SIMPLE_TEST_FALSE);

    int r;

    va_start(ap, c);

    switch (t) {
        case SIMPLE_TEST_MISMATCH:
            return -2;
        case SIMPLE_TEST_BOOL:
        case SIMPLE_TEST_INT:
        case SIMPLE_TEST_CHAR:
            simple_test_il = va_arg(ap, intmax_t);
            if (two) simple_test_ir = va_arg(ap, intmax_t);
            switch (c) {
                case SIMPLE_TEST_TRUE:
                    r = simple_test_il;
                    goto end;
                case SIMPLE_TEST_FALSE:
                    r = !simple_test_il;
                    goto end;
                case SIMPLE_TEST_EQ:
                    r = simple_test_il == simple_test_ir;
                    goto end;
                case SIMPLE_TEST_NEQ:
                    r = simple_test_il != simple_test_ir;
                    goto end;
                case SIMPLE_TEST_GT:
                    r = simple_test_il > simple_test_ir;
                    goto end;
                case SIMPLE_TEST_LT:
                    r = simple_test_il < simple_test_ir;
                    goto end;
                case SIMPLE_TEST_GEQ:
                    r = simple_test_il >= simple_test_ir;
                    goto end;
                case SIMPLE_TEST_LEQ:
                    r = simple_test_il <= simple_test_ir;
                    goto end;
            }

        case SIMPLE_TEST_UNSIGNED:
            simple_test_ul = va_arg(ap, uintmax_t);
            if (two) simple_test_ur = va_arg(ap, uintmax_t);
            switch (c) {
                case SIMPLE_TEST_TRUE:
                    r = simple_test_ul;
                    goto end;
                case SIMPLE_TEST_FALSE:
                    r = !simple_test_ul;
                    goto end;
                case SIMPLE_TEST_EQ:
                    r = simple_test_ul == simple_test_ur;
                    goto end;
                case SIMPLE_TEST_NEQ:
                    r = simple_test_ul != simple_test_ur;
                    goto end;
                case SIMPLE_TEST_GT:
                    r = simple_test_ul > simple_test_ur;
                    goto end;
                case SIMPLE_TEST_LT:
                    r = simple_test_ul < simple_test_ur;
                    goto end;
                case SIMPLE_TEST_GEQ:
                    r = simple_test_ul >= simple_test_ur;
                    goto end;
                case SIMPLE_TEST_LEQ:
                    r = simple_test_ul <= simple_test_ur;
                    goto end;
            }

        case SIMPLE_TEST_STRING:
            simple_test_sl = va_arg(ap, char *);
            if (two) simple_test_sr = va_arg(ap, char *);
            switch (c) {
                case SIMPLE_TEST_TRUE:
                    r = simple_test_sl != NULL;
                    goto end;
                case SIMPLE_TEST_FALSE:
                    r = simple_test_sl == NULL;
                    goto end;
                case SIMPLE_TEST_EQ:
                    if (simple_test_sl == NULL || simple_test_sr == NULL)
                        r = simple_test_sl == simple_test_sr;
                    else
                        r = strcmp(simple_test_sl, simple_test_sr) ? 0 : 1;
                    goto end;
                case SIMPLE_TEST_NEQ:
                    if (simple_test_sl == NULL || simple_test_sr == NULL)
                        r = simple_test_sl != simple_test_sr;
                    else
                        r = strcmp(simple_test_sl, simple_test_sr) ? 1 : 0;
                    goto end;
                case SIMPLE_TEST_GT:
                    if (simple_test_sl == NULL || simple_test_sr == NULL)
                        r = false;
                    else
                        r = strcmp(simple_test_sl, simple_test_sr) > 0 ? 1 : 0;
                    goto end;
                case SIMPLE_TEST_LT:
                    if (simple_test_sl == NULL || simple_test_sr == NULL)
                        r = false;
                    else
                        r = strcmp(simple_test_sl, simple_test_sr) < 0 ? 1 : 0;
                    goto end;
                case SIMPLE_TEST_GEQ:
                    if (simple_test_sl == NULL || simple_test_sr == NULL)
                        r = false;
                    else
                        r = strcmp(simple_test_sl, simple_test_sr) >= 0 ? 1 : 0;
                    goto end;
                case SIMPLE_TEST_LEQ:
                    if (simple_test_sl == NULL || simple_test_sr == NULL)
                        r = false;
                    else
                        r = strcmp(simple_test_sl, simple_test_sr) <= 0 ? 1 : 0;
                    goto end;
            }

        case SIMPLE_TEST_POINTER:
            simple_test_pl = va_arg(ap, void *);
            if (two) simple_test_pr = va_arg(ap, void *);
            switch (c) {
                case SIMPLE_TEST_TRUE:
                    r = simple_test_pl != NULL;
                    goto end;
                case SIMPLE_TEST_FALSE:
                    r = simple_test_pl == NULL;
                    goto end;
                case SIMPLE_TEST_EQ:
                    r = simple_test_pl == simple_test_pr;
                    goto end;
                case SIMPLE_TEST_NEQ:
                    r = simple_test_pl != simple_test_pr;
                    goto end;
                case SIMPLE_TEST_GT:
                    r = simple_test_pl > simple_test_pr;
                    goto end;
                case SIMPLE_TEST_LT:
                    r = simple_test_pl < simple_test_pr;
                    goto end;
                case SIMPLE_TEST_GEQ:
                    r = simple_test_pl >= simple_test_pr;
                    goto end;
                case SIMPLE_TEST_LEQ:
                    r = simple_test_pl <= simple_test_pr;
                    goto end;
            }

        default:
            r = -1;
    }

    end:
    va_end(ap);
    return r;
}

static enum simple_test_type simple_test_type_resolve(enum simple_test_type t1,
                                                      enum simple_test_type t2)
{
    if (t1 != t2) {
        if ((t1 == SIMPLE_TEST_INT && t2 == SIMPLE_TEST_UNSIGNED)
            || (t1 == SIMPLE_TEST_UNSIGNED && t2 == SIMPLE_TEST_INT)
            || (t1 == SIMPLE_TEST_BOOL && t2 == SIMPLE_TEST_UNSIGNED)
            || (t1 == SIMPLE_TEST_UNSIGNED && t2 == SIMPLE_TEST_BOOL)) {
            return SIMPLE_TEST_UNSIGNED;
        } else if ((t1 == SIMPLE_TEST_BOOL && t2 == SIMPLE_TEST_INT)
                   || (t1 == SIMPLE_TEST_INT && t2 == SIMPLE_TEST_BOOL)) {
            return SIMPLE_TEST_INT;
        } else if ((t1 == SIMPLE_TEST_INT && t2 == SIMPLE_TEST_CHAR)
                   || (t1 == SIMPLE_TEST_CHAR && t2 == SIMPLE_TEST_INT)) {
            return SIMPLE_TEST_CHAR;
        } else if ((t1 == SIMPLE_TEST_CHAR && t2 == SIMPLE_TEST_UNSIGNED)
                   || (t1 == SIMPLE_TEST_UNSIGNED && t2 == SIMPLE_TEST_CHAR)) {
            return SIMPLE_TEST_UNSIGNED;
        } else if ((t1 == SIMPLE_TEST_POINTER && t2 == SIMPLE_TEST_STRING)
                   || (t1 == SIMPLE_TEST_STRING && t2 == SIMPLE_TEST_POINTER)) {
            return SIMPLE_TEST_POINTER;
        } else {
            return SIMPLE_TEST_MISMATCH;
        }
    }

    return t1;
}

#define SIMPLE_TEST_TYPE(a) \
	_Generic((a), \
			    bool: SIMPLE_TEST_BOOL, \
			    char: SIMPLE_TEST_CHAR, \
			  int8_t: SIMPLE_TEST_INT, \
			 int16_t: SIMPLE_TEST_INT, \
			 int32_t: SIMPLE_TEST_INT, \
			 int64_t: SIMPLE_TEST_INT, \
			 uint8_t: SIMPLE_TEST_UNSIGNED, \
			uint16_t: SIMPLE_TEST_UNSIGNED, \
			uint32_t: SIMPLE_TEST_UNSIGNED, \
			uint64_t: SIMPLE_TEST_UNSIGNED, \
			  char *: SIMPLE_TEST_STRING, \
			  void *: SIMPLE_TEST_POINTER, \
			 default: SIMPLE_TEST_UNKNOWN)

#define SIMPLE_TEST_FAIL1(...) \
	do { \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN( \
					"\x1B[1m%*c :: at line %d, \x1B[m\x1B[1;31mfail: \x1B[m", \
					simple_test_pad_width, ' ', __LINE__); \
		} else { \
			SIMPLE_TEST_PRINT_FUN( \
					"%*c :: at line %d, fail: ", \
					simple_test_pad_width, ' ', __LINE__); \
		} \
			SIMPLE_TEST_PRINT_FUN( \
					__VA_ARGS__); \
			SIMPLE_TEST_PRINT_FUN( \
					"\n"); \
	} while (0)

#define SIMPLE_TEST_PRINT_VAL(w, s, t) \
	do { \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN( \
					"\x1B[1m%*c :: ", simple_test_pad_width, ' '); \
			SIMPLE_TEST_PRINT_FUN( \
					"`%s` \x1B[m== \x1B[1m", s); \
		} else { \
			SIMPLE_TEST_PRINT_FUN( \
					"%*c :: ", simple_test_pad_width, ' '); \
			SIMPLE_TEST_PRINT_FUN( \
					"`%s` == ", s); \
		} \
		switch (t) { \
		case SIMPLE_TEST_BOOL: \
			SIMPLE_TEST_PRINT_FUN( \
					"%s", (w ? simple_test_il : simple_test_ir) \
					? "true" : "false"); \
			break; \
		case SIMPLE_TEST_CHAR: \
			SIMPLE_TEST_PRINT_FUN( \
					"%c", w ? (char)simple_test_il : (char)simple_test_ir); \
			break; \
		case SIMPLE_TEST_INT: \
			SIMPLE_TEST_PRINT_FUN( \
					"%" PRIdMAX, w ? simple_test_il : simple_test_ir); \
			break; \
		case SIMPLE_TEST_UNSIGNED: \
			SIMPLE_TEST_PRINT_FUN( \
					"%" PRIuMAX, w ? simple_test_ul : simple_test_ur); \
			break; \
		case SIMPLE_TEST_STRING: \
			SIMPLE_TEST_PRINT_FUN( \
					((w ? simple_test_sl : simple_test_sr) \
						? "\"%s\"" : "%s"), w \
						? simple_test_sl : simple_test_sr); \
			break; \
		case SIMPLE_TEST_POINTER: \
			SIMPLE_TEST_PRINT_FUN( \
					"%p", w ? simple_test_pl : simple_test_pr); \
			break; \
		default: \
			break; \
		} \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN("\x1B[m\n"); \
		} else { \
			SIMPLE_TEST_PRINT_FUN("\n"); \
		} \
	} while (0)

#define SIMPLE_TEST_FAIL2 \
	do { \
		simple_test_fail_count++; \
		goto simple_test_loop_end; \
	} while (0)

#define SIMPLE_TEST_ERR(...) \
	do { \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN( \
					"\x1B[1m%*c :: at line %d, \x1B[m\x1B[1;31merr: \x1B[m", \
					simple_test_pad_width, ' ', __LINE__); \
		} else { \
			SIMPLE_TEST_PRINT_FUN( \
					"%*c :: at line %d, err: ", \
					simple_test_pad_width, ' ', __LINE__); \
		} \
		SIMPLE_TEST_PRINT_FUN(__VA_ARGS__); \
		SIMPLE_TEST_PRINT_FUN("\n"); \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN("\x1B[1;31mtesting aborted\x1B[m\n"); \
		} else { \
			SIMPLE_TEST_PRINT_FUN("testing aborted\n"); \
		} \
		exit(1); \
	} while (0)

#define SIMPLE_TEST_PRINT_BUF_WIDTH 512

#define SIMPLE_TEST_ASSERT1(t, c, s, a) \
	do { \
		switch ( simple_test_assert(t, c, (a)) ) { \
		case 1: break; \
		case 0: \
			SIMPLE_TEST_FAIL1(s " failed"); \
			SIMPLE_TEST_PRINT_VAL(0, #a, t); \
			SIMPLE_TEST_FAIL2; \
		break; \
		default: \
			 SIMPLE_TEST_ERR("unrecognised type in assertion"); \
		} \
	} while (0)

#define SIMPLE_TEST_ASSERT2(t1, t2, c, s, a, b) \
	do { \
		switch ( simple_test_assert(simple_test_type_resolve(t1, t2), \
					c, (a), (b)) ) { \
		case 1: break; \
		case 0: \
			SIMPLE_TEST_FAIL1(s " failed"); \
			SIMPLE_TEST_PRINT_VAL(0, #a, simple_test_type_resolve(t1, t2)); \
			SIMPLE_TEST_PRINT_VAL(1, #b, simple_test_type_resolve(t1, t2)); \
			SIMPLE_TEST_FAIL2; \
		break; \
		case -2: \
			 SIMPLE_TEST_ERR("type mismatch in assertion"); \
		default: \
			 SIMPLE_TEST_ERR("unrecognised type in assertion"); \
		} \
	} while (0)


/******************
 *  BASIC MACROS  *
 ******************/

#define TEARDOWN(f) \
	do { \
		simple_test_teardown = _Generic((f), \
				void(*)(void): (f), default: NULL); \
		if (simple_test_teardown == NULL) { \
			SIMPLE_TEST_ERR( \
					"wrongly-typed function passed to REGISTER_TEARDOWN"); \
		} \
	} while (0)

/* must appear before all tests */
#define BEGIN_TEST \
	int main(int argc, char **argv) \
	{ \
		int simple_test_iterator; \
		int simple_test_pad_width = 0; \
		int simple_test_fail_count = 0; \
		char simple_test_print_buf[SIMPLE_TEST_PRINT_BUF_WIDTH]; \
		int simple_test_test_count = 0; \
		int simple_test_test_current = 1; \
		int simple_test_test_current_at; \
		int simple_test_pass_number = 0; \
		void (*simple_test_teardown)(void) = NULL; \
		do { \
			simple_test_test_current_at = 0; \
			if (simple_test_pass_number == 0) { \
				if (SIMPLE_TEST_USE_COLOUR) { \
					SIMPLE_TEST_PRINT_FUN( \
							"\x1B[1mstarting tests in " __FILE__ "...\n"); \
				} else { \
					SIMPLE_TEST_PRINT_FUN( \
							"starting tests in " __FILE__ "...\n"); \
				} \
			} else { \
				simple_test_pad_width = sprintf(simple_test_print_buf, \
							"%d", simple_test_test_count) + 1; \
			} \
			for (simple_test_iterator = 0; simple_test_pass_number == 0 && \
					simple_test_iterator < 1; simple_test_iterator++) { \
				(void)0; \

#define TEST(description) \
	} \
	if (simple_test_teardown != NULL) { \
		simple_test_teardown(); \
		simple_test_teardown = NULL; \
	} \
	simple_test_test_current_at++; \
	if (simple_test_pass_number == 0) { \
		simple_test_test_count++; \
	} else if (simple_test_pass_number \
			== simple_test_test_current_at) { \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN( \
					"\x1B[m%*d \x1B[1m:: \x1B[m\x1B[33m%s\x1B[m\n", \
					simple_test_pad_width, \
					simple_test_test_current++, description); \
		} else { \
			SIMPLE_TEST_PRINT_FUN( \
					"%*d :: %s\n", \
					simple_test_pad_width, \
					simple_test_test_current++, description); \
		} \

/* must appear after all tests */
#define END_TEST \
			} \
			if (simple_test_teardown != NULL) { \
				simple_test_teardown(); \
				simple_test_teardown = NULL; \
			} \
			if (simple_test_test_count == 0) { \
				SIMPLE_TEST_ERR("no tests defined"); \
			} \
simple_test_loop_end: \
			(void)0; \
		} while (simple_test_pass_number++ < simple_test_test_count); \
		if (simple_test_fail_count) { \
			if (SIMPLE_TEST_USE_COLOUR) { \
				SIMPLE_TEST_PRINT_FUN( \
						"\x1B[1;31m%d of %d tests failed\x1B[m\n", \
						simple_test_fail_count, simple_test_test_count); \
			} else { \
				SIMPLE_TEST_PRINT_FUN( \
						"%d of %d tests failed\n", \
						simple_test_fail_count, simple_test_test_count); \
			} \
			return 1; \
		} else { \
			if (SIMPLE_TEST_USE_COLOUR) { \
				SIMPLE_TEST_PRINT_FUN("\x1B[1;32mall tests passed!\x1B[m\n"); \
			} else { \
				SIMPLE_TEST_PRINT_FUN("all tests passed!\n"); \
			} \
			return 0; \
		} \
	}

#define ECHO(...) \
	do { \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN( \
					"\x1B[1m%*c :: \x1B[m\x1B[34m", \
					simple_test_pad_width, ' '); \
		} else { \
			SIMPLE_TEST_PRINT_FUN( \
					"%*c :: ", \
					simple_test_pad_width, ' '); \
		} \
		SIMPLE_TEST_PRINT_FUN(__VA_ARGS__); \
		if (SIMPLE_TEST_USE_COLOUR) { \
			SIMPLE_TEST_PRINT_FUN("...\x1B[m\n"); \
		} else { \
			SIMPLE_TEST_PRINT_FUN("...\n"); \
		} \
	} while (0)


/**********************
 *  ASSERTION MACROS  *
 **********************/

#define ASSERT(a) \
	SIMPLE_TEST_ASSERT1(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_TRUE, "ASSERT", a)

#define ASSERT_NOT(a) \
	SIMPLE_TEST_ASSERT1(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_FALSE, \
			"ASSERT_NOT", a)

#define ASSERT_EQ(a, b) \
	SIMPLE_TEST_ASSERT2(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_TYPE((b)), \
			SIMPLE_TEST_EQ, "ASSERT_EQ", a, b)

#define ASSERT_NEQ(a, b) \
	SIMPLE_TEST_ASSERT2(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_TYPE((b)), \
			SIMPLE_TEST_NEQ, "ASSERT_NEQ", a, b)

#define ASSERT_GT(a, b) \
	SIMPLE_TEST_ASSERT2(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_TYPE((b)), \
			SIMPLE_TEST_GT, "ASSERT_GT", a, b)

#define ASSERT_LT(a, b) \
	SIMPLE_TEST_ASSERT2(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_TYPE((b)), \
			SIMPLE_TEST_LT, "ASSERT_LT", a, b)

#define ASSERT_GEQ(a, b) \
	SIMPLE_TEST_ASSERT2(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_TYPE((b)), \
			SIMPLE_TEST_GEQ, "ASSERT_GEQ", a, b)

#define ASSERT_LEQ(a, b) \
	SIMPLE_TEST_ASSERT2(SIMPLE_TEST_TYPE((a)), SIMPLE_TEST_TYPE((b)), \
			SIMPLE_TEST_LEQ, "ASSERT_LEQ", a, b)

#endif
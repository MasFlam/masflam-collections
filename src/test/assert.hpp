#include <cstdio>
#include <cstdlib>

bool exit_on_assertion_fail = false;

void assert(bool expr, const char *expr_str, const char *fail_message, const char *location_info, bool expected)
{
	if(expr != expected)
	{
		fprintf(stderr, "Assertion `%s` failed. %s. %s\n", expr_str, fail_message, location_info);
		if(exit_on_assertion_fail) exit(1);
	}
}

void assert(bool expr, const char *expr_str, const char *location_info, bool expected)
{
	if(expr != expected)
	{
		fprintf(stderr, "Assertion `%s` failed. %s\n", expr_str, location_info);
		if(exit_on_assertion_fail) exit(1);
	}
}

#define _INT_TO_STR(_int_literal) #_int_literal
#define INT_TO_STR(_int_literal_or_macro) _INT_TO_STR(_int_literal_or_macro)

#define ASSERT(_expr) assert((_expr), (#_expr), "file: " __FILE__ ", line: " INT_TO_STR(__LINE__), true);
#define ASSERT_FALSE(_expr) assert((_expr), (#_expr), "file: " __FILE__ ", line: " INT_TO_STR(__LINE__), false);
#define SASSERT(_expr, _fail_message) assert((_expr), (#_expr), (_fail_message), "file: " __FILE__ ", line: " INT_TO_STR(__LINE__), true);
#define SASSERT_FALSE(_expr, _fail_message) assert((_expr), (#_expr), (_fail_message), "file: " __FILE__ ", line: " INT_TO_STR(__LINE__), false);

#define ASSERT_THROWS(_stmt, _exception) \
	try \
	{ \
		_stmt; \
		fprintf(stderr, "Assertion failed: `" #_stmt "` didnt throw " #_exception ". file: " __FILE__ ", line: " INT_TO_STR(__LINE__)); \
		if(exit_on_assertion_fail) exit(1); \
	} \
	catch(_exception) {}

#define ASSERT_NOTHROW(_stmt) \
	try \
	{ \
		_stmt; \
	} \
	catch(...) \
	{ \
		fprintf(stderr, "Assertion failed: `" #_stmt "` threw an exception. file: " __FILE__ ", line: " INT_TO_STR(__LINE__)); \
		if(exit_on_assertion_fail) exit(1); \
	}

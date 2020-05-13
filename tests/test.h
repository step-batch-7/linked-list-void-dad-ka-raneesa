#ifndef __TEST_LIST_
#define __TEST_LIST_

#define PRINT_STRING(string) printf("%s\n", string)

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define PASS GREEN "\u2714 " RESET
#define FAIL RED "\u2718 " RESET

int PASSING_TESTS = 0;
int FAILING_TESTS = 0;

Status assert(int actual, int expected);

void display_assertion(Status assertion_status, char *message);

void test_clear_list(List_ptr list);
void test_search_node(List_ptr list);
void test_add_to_list(List_ptr list);

#endif
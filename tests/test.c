#include <stdio.h>
#include <stdlib.h>
#include "../linkedlist.h"
#include "test.h"

Status assert(int actual, int expected)
{
  return actual == expected;
}

void display_assertion(Status assertion_status, char *message)
{
  if (assertion_status)
  {
    printf(PASS);
    PASSING_TESTS++;
  }
  else
  {
    printf(FAIL);
    FAILING_TESTS++;
  }
  PRINT_STRING(message);
}

void test_clear_list(List_ptr list)
{
  int *num = malloc(sizeof(int));
  *num = 1;
  add_to_list(list, &num);

  PRINT_STRING("clear_list:");

  int status = assert(clear_list(list), Success);
  status = status && assert(list->length, 0);
  display_assertion(status, "should clear the list and set to zero");

  status = assert(clear_list(list), Failure);
  status = status && assert(list->length, 0);
  display_assertion(status, "should not clear the list if it is an empty list\n");
}

void test_search_node(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  add_to_list(list, &num1);

  PRINT_STRING("search_node");
  int status = assert(search_position(list, &num1), 0);
  display_assertion(status, "should give the position if the item is present in the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(search_position(list, &num2), -1);
  display_assertion(status, "should give -1 if the item is not present in the list\n");
  
  clear_list(list);
}

void test_add_to_list(List_ptr list){
  PRINT_STRING("Add to list:");

  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int status = assert(add_to_list(list, &num1), Success);
  status = status && assert(search_position(list, &num1), 0);
  status = status && assert(list->length, 1);
  display_assertion(status, "should add the given number at the beginning if list is empty of the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(add_to_list(list, &num2), Success);
  status = status && assert(search_position(list, &num2), 1);
  status = status && assert(list->length, 2);
  display_assertion(status, "should add the given number at the end of the list\n");

  clear_list(list);
}

int main(void){
  List_ptr list = create_list();
  
  test_clear_list(list);
  test_search_node(list);
  test_add_to_list(list);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);

  destroy_list(list);
  return 0;
}
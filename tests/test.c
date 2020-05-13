#include <stdio.h>
#include <stdlib.h>
#include "../linkedlist.h"
#include "test.h"

Status are_elements_equal(Element element1, Element element2)
{
  Int_ptr num1 = (Int_ptr)element1;
  Int_ptr num2 = (Int_ptr)element2;
  return num1 == num2;
}

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
  int status = assert(search_position(list, &num1, &are_elements_equal), 0);
  display_assertion(status, "should give the position if the item is present in the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(search_position(list, &num2, &are_elements_equal), -1);
  display_assertion(status, "should give -1 if the item is not present in the list\n");
  
  clear_list(list);
}

void test_add_to_list(List_ptr list){
  PRINT_STRING("Add to list:");

  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int status = assert(add_to_list(list, &num1), Success);
  status = status && assert(search_position(list, &num1, &are_elements_equal), 0);
  status = status && assert(list->length, 1);
  display_assertion(status, "should add the given number at the beginning if list is empty of the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(add_to_list(list, &num2), Success);
  status = status && assert(search_position(list, &num2, &are_elements_equal), 1);
  status = status && assert(list->length, 2);
  display_assertion(status, "should add the given number at the end of the list\n");

  clear_list(list);
}

void test_add_to_start(List_ptr list){
  PRINT_STRING("Add to beggining of list:");

  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int status = assert(add_to_start(list, &num1), Success);
  status = status && assert(search_position(list, &num1, &are_elements_equal), 0);
  status = status && assert(list->length, 1);
  display_assertion(status, "should add the given number at the beginning if list is empty of the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(add_to_start(list, &num2), Success);
  status = status && assert(search_position(list, &num2, &are_elements_equal), 0);
  status = status && assert(list->length, 2);
  display_assertion(status, "should add the given number at the begginging of the list\n");

  clear_list(list);
}

void test_insert_at(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  add_to_list(list, &num1);
  add_to_list(list, &num2);

  PRINT_STRING("insert_at");

  int *num3 = malloc(sizeof(int));
  *num3 = 3;
  int status = assert(insert_at(list, &num3, 2), Success);
  status = status && assert(search_position(list, &num3, &are_elements_equal), 2);
  status = status && assert(list->length, 3);
  display_assertion(status, "should add the given number at the end of the list");

  int *num4 = malloc(sizeof(int));
  *num4 = 4;
  status = assert(insert_at(list, &num4, 0), Success);
  status = status && assert(search_position(list, &num4, &are_elements_equal), 0);
  status = status && assert(list->length, 4);
  display_assertion(status, "should add the given number at the beginning of the list");

  int *num5 = malloc(sizeof(int));
  *num5 = 5;
  status = assert(insert_at(list, &num5, 2), Success);
  status = status && assert(search_position(list, &num5, &are_elements_equal), 2);
  status = status && assert(list->length, 5);
  display_assertion(status, "should add the given number at the given position of the list");

  int *num6 = malloc(sizeof(int));
  *num6 = 6;
  status = assert(insert_at(list, &num6, 9), Failure);
  status = status && assert(search_position(list, &num6, &are_elements_equal), -1);
  status = status && assert(list->length, 5);
  display_assertion(status, "should not add the given number if the given position is below 0");

  status = assert(insert_at(list, &num6, -9), Failure);
  status = status && assert(search_position(list, &num6, &are_elements_equal), -1);
  status = status && assert(list->length, 5);
  display_assertion(status, "should not add the given number if the given position is above list count\n");

  clear_list(list);
}

void test_add_unique(List_ptr list)
{
  PRINT_STRING("add_unique");

  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int status = assert(add_unique(list, &num1, &are_elements_equal), Success);
  status = status && assert(search_position(list, &num1, &are_elements_equal), 0);
  status = status && assert(list->length, 1);
  display_assertion(status, "should add the given number in the list if list is empty");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(add_unique(list, &num2, &are_elements_equal), Success);
  status = status && assert(search_position(list, &num2, &are_elements_equal), 1);
  status = status && assert(list->length, 2);
  display_assertion(status, "should add the given number in the list if not exists");

  status = assert(add_unique(list, &num1, &are_elements_equal), Failure);
  status = status && assert(search_position(list, &num1, &are_elements_equal), 0);
  status = status && assert(list->length, 1);
  display_assertion(status, "should not add the given number in the list if exists");

  clear_list(list);
}

void test_remove_from_start(List_ptr list)
{
  int *num = malloc(sizeof(int));
  *num = 1;
  add_to_list(list, &num);

  PRINT_STRING("\nremove_from_start");

  int status = are_elements_equal(remove_from_start(list), &num);
  status = status && assert(list->length, 0);
  display_assertion(status, "should remove the first item from the list");

  status = are_elements_equal(remove_from_start(list), NULL);
  status = status && assert(list->length, 0);
  display_assertion(status, "should not remove the item from the list if the list is empty");

  clear_list(list);
}

void test_remove_from_end(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  add_to_list(list, &num1);
  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  add_to_list(list, &num2);

  PRINT_STRING("\nremove_from_end");

  int status = are_elements_equal(remove_from_end(list), &num2);
  status = status && assert(list->length, 1);
  display_assertion(status, "should remove the last item from the list");

  status = are_elements_equal(remove_from_end(list), &num1);
  status = status && assert(list->length, 0);
  display_assertion(status, "should remove the first item from the list if there is only one item");

  status = are_elements_equal(remove_from_end(list), NULL);
  status = status && assert(list->length, 0);
  display_assertion(status, "should not remove the item from the list if the list is empty");

  clear_list(list);
}

void test_remove_at(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  int *num3 = malloc(sizeof(int));
  int *num4 = malloc(sizeof(int));
  int *num5 = malloc(sizeof(int));
  *num1 = 1;
  *num2 = 2;
  *num3 = 3;
  *num4 = 4;
  *num5 = 5;
  add_to_list(list, &num1);
  add_to_list(list, &num2);
  add_to_list(list, &num3);
  add_to_list(list, &num4);
  add_to_list(list, &num5);

  PRINT_STRING("\nremove_at");

  int status = are_elements_equal(remove_at(list, 4), &num5);
  status = status && assert(list->length, 4);
  display_assertion(status, "should remove the given number at the end of the list");

  status = are_elements_equal(remove_at(list, 0), &num1);
  status = status && assert(list->length, 3);
  display_assertion(status, "should remove the given number at the beginning of the list");

  status = are_elements_equal(remove_at(list, 1), &num3);
  status = status && assert(list->length, 2);
  display_assertion(status, "should remove the given number at the given position of the list");

  status = are_elements_equal(remove_at(list, 9), NULL);
  status = status && assert(list->length, 2);
  display_assertion(status, "should not remove the given number if the given position is below 0");

  status = are_elements_equal(remove_at(list, -9), NULL);
  status = status && assert(list->length, 2);
  display_assertion(status, "should not remove the given number if the given position is above list count");

  clear_list(list);
}

void test_remove_first_occurrence(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  *num1 = 1;
  *num2 = 2;
  add_to_list(list, &num1);
  add_to_list(list, &num2);

  PRINT_STRING("\nremove_first_occurrence");

  int status = are_elements_equal(remove_first_occurrence(list, &num1, &are_elements_equal), &num1);
  status = status && assert(search_position(list, &num1, &are_elements_equal), -1);
  status = status && assert(list->length, 1);
  display_assertion(status, "should remove first occurrence of the given number in the list if exists");

  status = are_elements_equal(remove_first_occurrence(list, &num1, &are_elements_equal), NULL);
  status = status && assert(search_position(list, &num1, &are_elements_equal), -1);
  status = status && assert(list->length, 1);
  display_assertion(status, "should not remove first occurrence of the given number in the list if not exists");

  clear_list(list);
}

void test_remove_all_occurrences(List_ptr list)
{
  add_to_end(list, 1);
  add_to_end(list, 2);
  add_to_end(list, 3);
  add_to_end(list, 1);

  PRINT_STRING("\nremove_all_occurrences");

  int status = assert(remove_all_occurrences(list, 1), Success);
  status = status && assert(search_position(list, 1), -1);
  status = status && assert(list->count, 2);
  display_pass_or_fail(status);
  PRINT_STRING("should remove all occurrences of the given number in the list if exists");

  status = assert(remove_all_occurrences(list, 1), Failure);
  status = status && assert(search_position(list, 1), -1);
  status = status && assert(list->count, 2);
  display_pass_or_fail(status);
  PRINT_STRING("should not remove all occurrences of the given number in the list if not exists");

  clear_list(list);
}

int main(void){
  List_ptr list = create_list();

  test_clear_list(list);
  test_search_node(list);
  test_add_to_list(list);
  test_add_to_start(list);
  test_insert_at(list);
  test_remove_from_start(list);
  test_remove_from_end(list);
  test_remove_at(list);
  test_remove_first_occurrence(list);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);

  destroy_list(list);
  return 0;
}
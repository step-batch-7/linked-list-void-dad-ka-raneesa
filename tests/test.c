#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linkedlist.h"
#include "test.h"

Status assert_element(Element element1, Element element2)
{
  int *num1 = (int *)element1;
  int *num2 = (int *)element2;
  if(num1 == 0 && num2 == 0){
    return Success;
  }
  return *num1 == *num2;
}

Status assert(int actual, int expected)
{
  return actual == expected;
}

Status assert_list(List_ptr list1, List_ptr list2){
  if(!assert(list1->length, list2->length)){
    return Failure;
  }

  Status assertion_status = Success;
  Node_ptr p_walk1 = list1->first;
  Node_ptr p_walk2 = list2->first;
  while(p_walk1 != NULL){
    assertion_status &= assert_element(p_walk1->element, p_walk2->element);
    p_walk1 = p_walk1->next;
    p_walk2 = p_walk2->next;
  }
  return assertion_status;
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
  status &= assert(list->length, 0);
  display_assertion(status, "should clear the list and set to zero");

  status = assert(clear_list(list), Failure);
  status &= assert(list->length, 0);
  display_assertion(status, "should not clear the list if it is an empty list\n");
}

void test_search_node(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  add_to_list(list, num1);

  PRINT_STRING("search_node");
  int status = assert(search_position(list, num1, &assert_element), 0);
  display_assertion(status, "should give the position if the item is present in the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(search_position(list, num2, &assert_element), -1);
  display_assertion(status, "should give -1 if the item is not present in the list\n");
  
  clear_list(list);
}

void test_add_to_list(List_ptr list){
  PRINT_STRING("Add to list:");

  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int status = assert(add_to_list(list, num1), Success);
  status &= assert(search_position(list, num1, &assert_element), 0);
  status &= assert(list->length, 1);
  display_assertion(status, "should add the given number at the beginning if list is empty of the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(add_to_list(list, num2), Success);
  status &= assert(search_position(list, num2, &assert_element), 1);
  status &= assert(list->length, 2);
  display_assertion(status, "should add the given number at the end of the list\n");

  clear_list(list);
}

void test_add_to_start(List_ptr list){
  PRINT_STRING("Add to beggining of list:");

  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int status = assert(add_to_start(list, num1), Success);
  status &= assert(search_position(list, num1, &assert_element), 0);
  status &= assert(list->length, 1);
  display_assertion(status, "should add the given number at the beginning if list is empty of the list");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(add_to_start(list, num2), Success);
  status &= assert(search_position(list, num2, &assert_element), 0);
  status &= assert(list->length, 2);
  display_assertion(status, "should add the given number at the begginging of the list\n");

  clear_list(list);
}

void test_insert_at(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  add_to_list(list, num1);
  add_to_list(list, num2);

  PRINT_STRING("insert_at");

  int *num3 = malloc(sizeof(int));
  *num3 = 3;
  int status = assert(insert_at(list, num3, 2), Success);
  status &= assert(search_position(list, num3, &assert_element), 2);
  status &= assert(list->length, 3);
  display_assertion(status, "should add the given number at the end of the list");

  int *num4 = malloc(sizeof(int));
  *num4 = 4;
  status = assert(insert_at(list, num4, 0), Success);
  status &= assert(search_position(list, num4, &assert_element), 0);
  status &= assert(list->length, 4);
  display_assertion(status, "should add the given number at the beginning of the list");

  int *num5 = malloc(sizeof(int));
  *num5 = 5;
  status = assert(insert_at(list, num5, 2), Success);
  status &= assert(search_position(list, num5, &assert_element), 2);
  status &= assert(list->length, 5);
  display_assertion(status, "should add the given number at the given position of the list");

  int *num6 = malloc(sizeof(int));
  *num6 = 6;
  status = assert(insert_at(list, num6, 9), Failure);
  status &= assert(search_position(list, num6, &assert_element), -1);
  status &= assert(list->length, 5);
  display_assertion(status, "should not add the given number if the given position is below 0");

  status = assert(insert_at(list, num6, -9), Failure);
  status &= assert(search_position(list, num6, &assert_element), -1);
  status &= assert(list->length, 5);
  display_assertion(status, "should not add the given number if the given position is above list count\n");

  clear_list(list);
}

void test_add_unique(List_ptr list)
{
  PRINT_STRING("add_unique");

  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  int status = assert(add_unique(list, num1, &assert_element), Success);
  status &= assert(search_position(list, num1, &assert_element), 0);
  status &= assert(list->length, 1);
  display_assertion(status, "should add the given number in the list if list is empty");

  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  status = assert(add_unique(list, num2, &assert_element), Success);
  status &= assert(search_position(list, num2, &assert_element), 1);
  status &= assert(list->length, 2);
  display_assertion(status, "should add the given number in the list if not exists");

  status = assert(add_unique(list,&num1, &assert_element), Failure);
  status &= assert(search_position(list, num1, &assert_element), 0);
  status &= assert(list->length, 1);
  display_assertion(status, "should not add the given number in the list if exists\n");

  clear_list(list);
}

void test_remove_from_start(List_ptr list)
{
  int *num = malloc(sizeof(int));
  *num = 1;
  add_to_list(list, num);

  PRINT_STRING("remove_from_start");

  int status = assert_element(remove_from_start(list), num);
  status &= assert(list->length, 0);
  display_assertion(status, "should remove the first item from the list");

  Element result = NULL;
  status = assert_element(remove_from_start(list), result);
  status &= assert(list->length, 0);
  display_assertion(status, "should not remove the item from the list if the list is empty\n");

  clear_list(list);
}

void test_remove_from_end(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  *num1 = 1;
  add_to_list(list, num1);
  int *num2 = malloc(sizeof(int));
  *num2 = 2;
  add_to_list(list, num2);

  PRINT_STRING("remove_from_end");

  int status = assert_element(remove_from_end(list), num2);
  status &= assert(list->length, 1);
  display_assertion(status, "should remove the last item from the list");

  status = assert_element(remove_from_end(list), num1);
  status &= assert(list->length, 0);
  display_assertion(status, "should remove the first item from the list if there is only one item");

  status = assert_element(remove_from_end(list), NULL);
  status &= assert(list->length, 0);
  display_assertion(status, "should not remove the item from the list if the list is empty\n");

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
  add_to_list(list, num1);
  add_to_list(list, num2);
  add_to_list(list, num3);
  add_to_list(list, num4);
  add_to_list(list, num5);

  PRINT_STRING("remove_at");

  int status = assert_element(remove_at(list, 4), num5);
  status &= assert(list->length, 4);
  display_assertion(status, "should remove the given number at the end of the list");

  status = assert_element(remove_at(list, 0), num1);
  status &= assert(list->length, 3);
  display_assertion(status, "should remove the given number at the beginning of the list");

  status = assert_element(remove_at(list, 1), num3);
  status &= assert(list->length, 2);
  display_assertion(status, "should remove the given number at the given position of the list");

  status = assert_element(remove_at(list, 9), NULL);
  status &= assert(list->length, 2);
  display_assertion(status, "should not remove the given number if the given position is below 0");

  status = assert_element(remove_at(list, -9), NULL);
  status &= assert(list->length, 2);
  display_assertion(status, "should not remove the given number if the given position is above list count\n");

  clear_list(list);
}

void test_remove_first_occurrence(List_ptr list)
{
  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  *num1 = 1;
  *num2 = 2;
  add_to_list(list, num1);
  add_to_list(list, num2);

  PRINT_STRING("remove_first_occurrence");

  int status = assert_element(remove_first_occurrence(list, num1, &assert_element), num1);
  status &= assert(search_position(list, num1, &assert_element), -1);
  status &= assert(list->length, 1);
  display_assertion(status, "should remove first occurrence of the given number in the list if exists");

  status = assert_element(remove_first_occurrence(list, num1, &assert_element), NULL);
  status &= assert(search_position(list, num1, &assert_element), -1);
  status &= assert(list->length, 1);
  display_assertion(status, "should not remove first occurrence of the given number in the list if not exists\n");

  clear_list(list);
}

void test_reverse(List_ptr list){
  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  *num1 = 1;
  *num2 = 2;
  add_to_list(list, num1);
  add_to_list(list, num2);

  List_ptr result = create_list();

  PRINT_STRING("reverse");
  int status = assert_list(reverse(result), result);
  status &= assert(result->length, 0);
  display_assertion(status, "should give empty list when give empty array");

  add_to_list(result, num2);
  add_to_list(result, num1);

  status = assert_list(reverse(list), result);
  status &= assert(list->length, 2);
  display_assertion(status, "should reverse the elements in the list\n");

  clear_list(list);
}

void add_one(Element value){
  int incremented_value = (*(int *)value) + 1;
  memcpy(value, &incremented_value, sizeof(incremented_value));
}

void test_forEach(List_ptr list){
  PRINT_STRING("forEach");

  List_ptr result = create_list();
  forEach(list, &add_one);
  int status = assert_list(list, result);
  status &= assert(result->length, 0);
  display_assertion(status, "should give empty list when give empty list");

  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  *num1 = 1;
  *num2 = 2;
  add_to_list(list, num1);
  add_to_list(list, num2);

  int *num3 = malloc(sizeof(int));
  int *num4 = malloc(sizeof(int));
  *num3 = 2;
  *num4 = 3;
  add_to_list(result, num3);
  add_to_list(result, num4);
  
  forEach(list, &add_one);
  status = assert_list(list, result);
  status &= assert(result->length, 2);
  display_assertion(status, "should give list with elements of incremented value\n");
  
  clear_list(list);
}


Element increment_by_one(Element element){
  Element new_element = malloc(sizeof(Element));
  *(int *)new_element = (*(int *)element) + 1;
  return new_element;
}

void test_map(List_ptr list){
  PRINT_STRING("map");

  List_ptr result = create_list();
  int status = assert_list(map(list, &increment_by_one), result);
  status &= assert(result->length, 0);
  display_assertion(status, "should give empty list when give empty list");

  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  *num1 = 1;
  *num2 = 2;
  add_to_list(list, num1);
  add_to_list(list, num2);

  int *num3 = malloc(sizeof(int));
  int *num4 = malloc(sizeof(int));
  *num3 = 2;
  *num4 = 3;
  add_to_list(result, num3);
  add_to_list(result, num4);
  
  status = assert_list(map(list, &increment_by_one), result);
  status &= assert(result->length, 2);
  display_assertion(status, "should increment values by one");

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
  test_reverse(list);
  test_forEach(list);
  test_map(list);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);

  destroy_list(list);
  return 0;
}
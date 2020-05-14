#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void display_element(Element element);
void display_list(List_ptr list);
Status are_elements_equal(Element element1, Element element2);
Element add_one(Element element);

void display_element(Element element)
{
  Int_ptr number = (Int_ptr)element;
  printf("%d ", *number);
}

void display_list(List_ptr list){
  printf("list : ");
  Node_ptr p_walk = list->first;
  while(p_walk != NULL){
    display_element(p_walk->element);
    p_walk = p_walk->next;
  }
  printf("\n");
}


Status are_elements_equal(Element element1, Element element2)
{
  Int_ptr num1 = (Int_ptr)element1;
  Int_ptr num2 = (Int_ptr)element2;
  return num1 == num2;
}

Element add_one(Element element){
  Element new_element = malloc(sizeof(Element));
  *(int *)new_element = (*(int *)element) + 1;
  return new_element;
}

int main(){
  int numbers[] = {1,2,3,4};
  Int_ptr ptr_to_numbers = numbers;
  int length = 3;
  List_ptr list = create_list();
  printf("add to list:\n");
  for(int i = 0; i < length; i++){
    add_to_list(list, ptr_to_numbers + i);
    display_list(list);
  }
  clear_list(list);
  display_list(list);
  printf("\nadd to start:\n");
  for(int i = 0; i < length; i++){
    add_to_start(list, ptr_to_numbers + i);
    display_list(list);
  }
  printf("\ninsert at:\n");
  insert_at(list, ptr_to_numbers, 0);
  display_list(list);
  insert_at(list, ptr_to_numbers + 2, 2);
  display_list(list);
  insert_at(list, ptr_to_numbers + 1, 5);
  display_list(list);

  printf("\nadd unique:\n");
  add_unique(list, ptr_to_numbers + 1, &are_elements_equal);
  display_list(list);
  add_unique(list, ptr_to_numbers + 3, &are_elements_equal);
  display_list(list);

  printf("\nremove from start:\n");
  remove_from_start(list);
  display_list(list);

  printf("\nremove from end:\n");
  remove_from_end(list);
  display_list(list);

  printf("\nremove from end:\n");
  remove_at(list, 2);
  display_list(list);

  printf("\nremove first occurrance:\n");
  remove_first_occurrence(list, ptr_to_numbers + 2, &are_elements_equal);
  display_list(list);

  printf("\nremove first occurrance:\n");
  add_to_list(list, ptr_to_numbers + 2);
  List_ptr result = remove_all_occurrences(list, ptr_to_numbers + 2, &are_elements_equal);
  display_list(list);
  printf("removed elements:");
  display_list(result);

  printf("\nreverse the list:\n");
  result = reverse(list);
  display_list(result);

  printf("\nForeach\n");
  forEach(list, &display_element);

  printf("\nmap\n");
  result = map(list, &add_one);
  display_list(list);
  display_list(result);
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void display_node(Node_ptr node);
void display_list(List_ptr list);

void display_node(Node_ptr node)
{
  Int_ptr number = (Int_ptr)node->element;
  printf("%d ", *number);
}

void display_list(List_ptr list){
  printf("list : ");
  Node_ptr p_walk = list->first;
  while(p_walk != NULL){
    display_node(p_walk);
    p_walk = p_walk->next;
  }
  printf("\n");
}

int main(){
  int numbers[] = {1,2,3};
  Int_ptr ptr_to_numbers = numbers;
  int length = sizeof(numbers)/sizeof(int);
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
  return 0;
}
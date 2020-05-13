#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Node_ptr create_node(Element element){
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = element;
  new_node->next = NULL;
  return new_node;
}

Status add_in_empty_list(List_ptr list, Node_ptr new_node)
{
  if (list->first == NULL)
  {
    list->first = new_node;
    list->last = new_node;
    return Success;
  }
  return Failure;
}

Status add_to_list(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  if(!add_in_empty_list(list, new_node)){
    list->last->next = new_node;
    list->last = new_node;
  }
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  if (!add_in_empty_list(list, new_node))
  {
    Node_ptr start_node = list->first;
    list->first = new_node;
    list->first->next = start_node;
  }
  list->length++;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position){
  if (position != 0)
  {
    Prev_Current_Pair pair = {NULL, list->first};
    int count = 0;
    while (count < list->length)
    {
      if (count == position)
      {
        Node_ptr new_node = create_node(element);
        pair.prev->next = new_node;
        new_node->next = pair.current;
        list->length++;
        return Success;
      }
      pair.prev = pair.current;
      pair.current = pair.current->next;
      count++;
    }
    if(position == count){
      return add_to_list(list, element);
    }
    return Failure;
  }
  return add_to_start(list, element);
}

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    if (matcher(p_walk->element, element))
    {
      return Failure;
    }
    p_walk = p_walk->next;
  }
  return add_to_list(list, element);
}

int search_position(List_ptr list, Element element, Matcher matcher){
  Node_ptr p_walk = list->first;
  int position = 0;
  while (p_walk != NULL)
  {
    if (matcher(p_walk->element, element))
    {
      return position;
    }
    p_walk = p_walk->next;
    position++;
  }
  return -1;
}

Status clear_list(List_ptr list){
  if(list->first == NULL){
    return Failure;
  }
  
  Node_ptr p_walk = list->first;
  Node_ptr node_to_free = NULL;

  while(p_walk != NULL){
    node_to_free = p_walk;
    p_walk = p_walk->next;
    free(node_to_free);
  }

  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return Success;
}

void destroy_list(List_ptr list)
{
  Node_ptr p_walk = list->first;
  Node_ptr node_to_free = NULL;
  while (p_walk != NULL)
  {
    node_to_free = p_walk;
    p_walk = p_walk->next;
    free(node_to_free);
  }
  free(list);
}
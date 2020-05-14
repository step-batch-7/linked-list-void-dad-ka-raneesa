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

Status remove_from_empty_list(Node_ptr node)
{
  if (node == NULL)
  {
    return Failure;
  }
  return Success;
}

Element remove_from_start(List_ptr list)
{ 
  Element removed_element = NULL;
  if (remove_from_empty_list(list->first))
  {
    removed_element = list->first->element;
    Node_ptr next_node = list->first->next;
    if (list->length == 1)
    {
      list->last = next_node;
    }
    list->first = next_node;
    list->length--;
  }
  return removed_element;
}

Element remove_from_end(List_ptr list){
  if (list->length != 1 && list->length != 0)
  {
    Element removed_element;
    int count = 1;
    Node_ptr p_walk = list->first;
    while (p_walk != NULL)
    {
      if (count == list->length - 1)
      {
        removed_element = p_walk->next->element;
        p_walk->next = NULL;
        list->last = p_walk;
        list->length--;
      }
      p_walk = p_walk->next;
      count++;
    }
    return removed_element;
  }
  return remove_from_start(list);
}

Element remove_element_at(List_ptr list, int position)
{
  Element removed_element = NULL;
  Prev_Current_Pair pair = {NULL, list->first};
  int count = 0;
  while (count < list->length)
  {
    if (count == position)
    {
      removed_element = pair.current->element;
      pair.prev->next = pair.current->next;
      list->length--;
      return removed_element;
    }
    pair.prev = pair.current;
    pair.current = pair.current->next;
    count++;
  }
  return removed_element;
}

Element remove_at(List_ptr list, int position){
  if (position == 0)
  {
    return remove_from_start(list);
  }
  if (position == list->length - 1)
  {
    return remove_from_end(list);
  }
  return remove_element_at(list, position);
}

int search_position(List_ptr list, Element element, Matcher matcher)
{
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
Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  int position = search_position(list, element, matcher);
  if (position != -1)
  {
    return remove_at(list, position);
  }
  return NULL;
}
List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher)
{
  List_ptr removed_elements = create_list();
  Element removed_element;
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    removed_element = remove_first_occurrence(list, element, matcher);
    p_walk = p_walk->next;
    if (removed_element)
      add_to_list(removed_elements, removed_element);
  }
  return removed_elements;
}

List_ptr reverse(List_ptr list){
  List_ptr reversed_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    add_to_start(reversed_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return reversed_list;
}

void forEach(List_ptr list, ElementProcessor processor){
  Node_ptr p_walk = list->first;
  while(p_walk != NULL){
    processor(p_walk->element);
    p_walk = p_walk->next;
  }
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
#include <stdio.h>
#include <stdlib.h>

/*
The consumer of this Linked List library is expected to take care of allocating & freeing elements.
The Linked List maintains the element references in a sequence and provides convenient operations on them.
*/

#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_


typedef enum
{
  Failure,
  Success
} Status;

typedef void *Element;
typedef int *Int_ptr;

typedef struct node
{
  Element element;
  struct node *next;
} Node;

typedef Node *Node_ptr;

typedef struct linklist
{
  Node *first;
  Node *last;
  int length;
} LinkedList;

typedef LinkedList *List_ptr;

typedef struct
{
  Node_ptr prev;
  Node_ptr current;
} Prev_Current_Pair;

typedef Element (*Mapper)(Element);
typedef Status (*Predicate)(Element);
typedef Element (*Reducer)(Element, Element);
typedef void (*ElementProcessor)(Element);
typedef Status (*Matcher)(Element, Element);

List_ptr create_list(void);

Status add_to_list(List_ptr, Element);
Status add_to_start(List_ptr, Element);
Status insert_at(List_ptr, Element element, int position);

List_ptr reverse(List_ptr);

List_ptr map(List_ptr, Mapper);
List_ptr filter(List_ptr, Predicate);
Element reduce(List_ptr, Element, Reducer);
void forEach(List_ptr, ElementProcessor processor);

Element remove_from_start(List_ptr); // Returns Element which was removed
Element remove_from_end(List_ptr);
Element remove_at(List_ptr, int position);

Element remove_first_occurrence(List_ptr, Element element, Matcher matcher);
List_ptr remove_all_occurrences(List_ptr, Element element, Matcher matcher); // Returns List of removed elements

Status add_unique(List_ptr list, Element element, Matcher matcher);

Status clear_list(List_ptr);

void destroy_list(List_ptr list);

Node_ptr create_node(Element data);
Status add_in_empty_list(List_ptr list, Node_ptr new_node);
Status are_elements_equal(Element element1, Element element2);
int search_position(List_ptr list, Element element, Matcher matcher);
Status remove_from_empty_list(Node_ptr node);
Element remove_element_at(List_ptr list, int position);
#endif

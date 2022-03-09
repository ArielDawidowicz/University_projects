
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"

/* Generic Linked List ADT*/

typedef struct LinkedList_t *LinkedList;


/* Function return Status values  */
typedef enum {ListNotDestroyed,ListDestroyed,NoNodeAdded,NodeAdded,NoNodeDeleted,NodeDeleted,ListHasNotPrinted,ListHasPrinted} LinkedListStatus;


/*Create a Linked List and returns the pointer to the linked list unitilized with pointers to the functions requested -
 * CopyFunction, FreeFunction, KeyInElement, EqualFunction and PrintElement. if it fails, returns NULL  */
LinkedList createLinkedList(copyFunction copyfunction, freeFunction freefunction, GetkeyInElement GetkeyInElement, equalFunction equalfunction,printFunction printElement);

/* Receives a pointer to LinkedList ADT and delete its Elements and releases memory in the heap. returns Status if the -
 * function succeed or failed  */
LinkedListStatus destroyList(LinkedList linkedList);


/* Receives pointer to a Linked list and a Element (void *) and adds the Element to the end of the list -
 * returns Status if the function succeed or failed  */
LinkedListStatus appendNode(LinkedList linkedlist, element elem);


/* Receives pointer to a Linked list and a Element (void *) and delete the Element from the list -
 * if he is in the list. Returns Status if the function succeed or failed  */
LinkedListStatus deleteNode(LinkedList linkedlist, element elem);


/* Receives pointer to a Linked list loops over the list and prints its elements */
LinkedListStatus displayList(LinkedList linkedlist);


/* Receives pointer to a Linked list and a Element (void *) checks if the Element is part of information stored -
 * in a Node and returns the Node. if this Node not found returns NULL  */
element searchByKeyInlist(LinkedList linkedlist, element elem);

#endif /* LINKEDLIST_H_ */

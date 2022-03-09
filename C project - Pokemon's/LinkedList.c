#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Defs.h"


typedef struct LinkedListNode_t{
	element value;
	struct LinkedListNode_t *next;
}Node;

struct LinkedList_t{
	Node *head;
	Node *tail;
	int size;
	copyFunction copyElement;
	freeFunction destroyElement;
	GetkeyInElement GetkeyInElement;
	equalFunction equalFunction;
	printFunction printElement;
};


LinkedList createLinkedList(copyFunction copyfunction, freeFunction freefunction, GetkeyInElement GetkeyInElement, equalFunction equalfunction,printFunction printElement){
	if(copyfunction == NULL || freefunction == NULL || GetkeyInElement == NULL || equalfunction == NULL || printElement == NULL){
		printf("Memory problem");
		return NULL;
	}
	LinkedList newLinkedList = (LinkedList)malloc(sizeof(struct LinkedList_t));
	if (newLinkedList == NULL){
		printf("Memory problem");
		return NULL;
	}
	newLinkedList->head = NULL;
	newLinkedList->tail = NULL;
	newLinkedList->size = 0;
	newLinkedList->copyElement = copyfunction;
	newLinkedList->destroyElement = freefunction;
	newLinkedList->GetkeyInElement = GetkeyInElement;
	newLinkedList->equalFunction = equalfunction;
	newLinkedList->printElement = printElement;
	return newLinkedList;
};


LinkedListStatus destroyList(LinkedList linkedList){
	if(linkedList == NULL)
		return ListNotDestroyed;
	Node *temp = linkedList->head;
	while (temp != NULL){
		linkedList->head = linkedList->head->next;
		linkedList->destroyElement(temp->value);
		free(temp);
		temp = linkedList->head;
	}
	free(linkedList);
	return ListDestroyed;
};


LinkedListStatus appendNode(LinkedList linkedlist, element elem){
	if(linkedlist == NULL || elem == NULL)
		return NoNodeAdded;
	Node *newNode =(Node *)malloc(sizeof(Node));
	if (newNode == NULL)
		return NoNodeAdded;
	newNode->value = linkedlist->copyElement(elem);
	if (newNode->value == NULL){
		free(newNode);
		return NoNodeAdded;
	}
	if(linkedlist->size == 0){
		linkedlist->tail = newNode;
		linkedlist->head = newNode;
		linkedlist->size++;
		return NodeAdded;
	}
	linkedlist->tail->next = newNode;
	linkedlist->tail = newNode;
	linkedlist->size++;
	return NodeAdded;
};


LinkedListStatus deleteNode(LinkedList linkedlist, element elem){
	if (linkedlist == NULL || elem == NULL){
		return NoNodeDeleted;
	}
	int i;
	Node *temp = linkedlist->head;
	if (linkedlist->equalFunction(elem, temp->value) == 0){
		Node *temp2 = temp->next;
		linkedlist->destroyElement(temp->value);
		free(linkedlist->head);
		linkedlist->head = temp2;
		linkedlist->size--;

		return NodeDeleted;
	}
	for (i=0 ; i<linkedlist->size ; i++){
		if (!temp->next)
			return NoNodeDeleted;
		if (linkedlist->equalFunction(elem, temp->next->value) == 0){
			if(temp->next == linkedlist->tail){
				linkedlist->destroyElement(temp->next->value);
				linkedlist->tail = temp;
				linkedlist->size--;
				return NodeDeleted;
			}
			linkedlist->destroyElement(temp->next->value);
			Node *temp2 = temp->next->next;
			free(temp->next);
			temp->next = temp2;
			linkedlist->size--;
			return NodeDeleted;
		}temp = temp->next;
	}return NoNodeDeleted;
};


LinkedListStatus displayList(LinkedList linkedlist){
	if (linkedlist == NULL )
		return ListHasNotPrinted;

	if (linkedlist->size == 0)
		return ListHasNotPrinted;
	Node *temp = linkedlist->head;
	while (temp != NULL){
		linkedlist->printElement(temp->value);
		temp = temp->next;
	}
	return ListHasPrinted;
};

element searchByKeyInlist(LinkedList linkedlist, element elem){
	if(linkedlist == NULL || elem == NULL)
		return NULL;
	Node *temp = linkedlist->head;
	while (temp != NULL){
		if(linkedlist->GetkeyInElement(temp->value, elem) == true)
			return temp->value;
		temp = temp->next;
	}
	return NULL;
};



#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include "Defs.h"

typedef struct MaxHeap_t *MaxHeap;

/* Function return Status values  */
typedef enum {HeapHasNotDestroyed, HeapHasDestroyed, HeapHasNotPrinted, HeapHasPrinted,ElementNotInserted,ElementInserted} MaxHeapStatus;

/*Create a Max Heap ADT and returns the pointer to the Max Heap unitilized with pointers to the functions requested -
* CopyFunction, FreeFunction, KeyInElement, EqualFunction and PrintElement. if it fails, returns NULL  */
MaxHeap CreateHeap(copyFunction copyFunction, freeFunction freeFunction, equalFunction equalFunction, printFunction printElement, char *name, int maxSize);

/* gets a Maxheap pointer and free all the memory of the elements inside the haep, and the heap itself -
 * and return status if the deletion succeed */
MaxHeapStatus destroyHeap(MaxHeap maxHeap);

/* gets a pointer to maxheap and pointer to a element and insert the element */
MaxHeapStatus insertToHeap(MaxHeap maxHeap, element elem);

/* gets a maxheap pointer and print all the elements */
MaxHeapStatus printHeap(MaxHeap maxHeap);

/* gets a maxheap pointer and returns the element with the highest value, and remove him from the heap */
element PopMaxHeap(MaxHeap maxHeap);

/* gets a maxheap pointer and returns the element with the highest value */
element TopMaxHeap(MaxHeap maxHeap);

/*/* gets a maxheap pointer and returns the id of the heap */
char *getHeapId(MaxHeap maxHeap);

/* gets a maxheap pointer and returns the number of elements inside the heap */
int getHeapCurrentSize(MaxHeap maxHeap);

/* return true if the heap name equals to the name recieved as arguments */
bool heapNameCheck(MaxHeap maxHeap, element name);

/* returns a copy pionter of the heap */
MaxHeap copyHeap(MaxHeap maxHeap);


#endif

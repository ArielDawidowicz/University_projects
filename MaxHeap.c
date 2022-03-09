#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "MaxHeap.h"
#include "Pokemon.h"


struct MaxHeap_t{
	int size, maxSize;
	char *name;
	element *heap;
	copyFunction copyElement;
	freeFunction destroyElement;
	equalFunction equalFunction;
	printFunction printElement;
};


static int LeftChild(int i){
	if (i == 0){
		int x = 1;
		return x;
	}
	int y = (2*i)+1;
	return y;
};

static int RightChild(int i){
	if (i == 0){
		int x = 2;
		return x;
	}
	int y = (2*i)+2;
	return y;
};

static int Parent(int i){
	if (i == 1 || i == 2){
		int x = 0;
		return x;
	}

	int y = floor((i/2)-1);
	return y;
};


static void Heapify(MaxHeap maxHeap, int i){
	int left = LeftChild(i);
	int right = RightChild(i);
	int largest;
	if (left < maxHeap->size && (maxHeap->equalFunction(maxHeap->heap[left], maxHeap->heap[i]) == 1))
		largest = left;
	else{
		largest = i;
	}
	if (right < maxHeap->size && (maxHeap->equalFunction(maxHeap->heap[right], maxHeap->heap[largest]) == 1))
		largest = right;
	if (i != largest){
		element temp = maxHeap->heap[i];
		element temp2 = maxHeap->heap[largest];
		maxHeap->heap[largest] = temp;
		maxHeap->heap[i] = temp2;
		Heapify(maxHeap, largest);
	}
};

MaxHeap CreateHeap(copyFunction copyFunction, freeFunction freeFunction, equalFunction equalFunction, printFunction printElement, char *name, int maxSize){
	if(copyFunction == NULL || freeFunction == NULL || equalFunction == NULL || printElement == NULL || name == NULL){
		printf("Memory problem");
		return NULL;
	}
	MaxHeap newMaxHeap = (MaxHeap)malloc(sizeof(struct MaxHeap_t));
	if (newMaxHeap == NULL){
		printf("Memory problem");
		return NULL;
	}
	newMaxHeap->name = (char *)malloc(sizeof(strlen(name))+1);
	if (newMaxHeap->name == NULL){
		free(newMaxHeap);
		printf("Memory problem");
		return NULL;
	}
	strcpy(newMaxHeap->name, name);
	newMaxHeap->heap = (element *)malloc(sizeof(element)*maxSize);
	if (newMaxHeap->heap == NULL){
		free(newMaxHeap->name);
		free(newMaxHeap);
		printf("Memory problem");
		return NULL;
	}
	int i;
	for (i=0 ; i<maxSize ;i++){
		newMaxHeap->heap[i] = NULL;
	}
	newMaxHeap->copyElement = copyFunction;
	newMaxHeap->destroyElement = freeFunction;
	newMaxHeap->equalFunction = equalFunction;
	newMaxHeap->printElement = printElement;
	newMaxHeap->maxSize = maxSize;
	newMaxHeap->size = 0;
	return newMaxHeap;
}


MaxHeapStatus destroyHeap(MaxHeap maxHeap){
	if (maxHeap == NULL)
		return HeapHasNotDestroyed;
	int i;
	for (i=0; i<maxHeap->maxSize;i++){
		if(maxHeap->heap[i] != NULL)
			maxHeap->destroyElement(maxHeap->heap[i]);
	}
	free(maxHeap->name);
	free(maxHeap->heap);
	free(maxHeap);
	return HeapHasDestroyed;
};

static void diffusion(MaxHeap maxHeap, int i){
	while (i > 0){
		int parent = Parent(i);
		if(maxHeap->equalFunction(maxHeap->heap[i], maxHeap->heap[parent]) == 1){
			element temp = maxHeap->heap[parent];
			maxHeap->heap[parent] = maxHeap->heap[i];
			maxHeap->heap[i] = temp;
			i = parent;
		}break;
	}
	if(maxHeap->size > 1){
	if(maxHeap->equalFunction(maxHeap->heap[1], maxHeap->heap[0]) == 1){
		element temp = maxHeap->heap[0];
		maxHeap->heap[0] = maxHeap->heap[1];
		maxHeap->heap[1] = temp;
	}
	}
	if(maxHeap->size > 2){
	if(maxHeap->equalFunction(maxHeap->heap[2], maxHeap->heap[0]) == 1){
		element temp = maxHeap->heap[0];
		maxHeap->heap[0] = maxHeap->heap[2];
		maxHeap->heap[2] = temp;
	}
	}
};

MaxHeapStatus insertToHeap(MaxHeap maxHeap, element elem){
	if (maxHeap == NULL || elem == NULL)
		return ElementNotInserted;
	if (maxHeap->size == maxHeap->maxSize)
		return ElementNotInserted;
	maxHeap->heap[maxHeap->size] = maxHeap->copyElement(elem);
	maxHeap->size++;
	if(maxHeap->size >0)
		diffusion(maxHeap, maxHeap->size-1);
	return ElementInserted;
};


MaxHeapStatus printHeap(MaxHeap maxHeap){
	if (maxHeap == NULL)
			return HeapHasNotPrinted;
	MaxHeap tempHeap = CreateHeap(maxHeap->copyElement, maxHeap->destroyElement, maxHeap->equalFunction, maxHeap->printElement,
			maxHeap->name, maxHeap->maxSize);
	if (tempHeap == NULL){
		return HeapHasNotPrinted;
	}
	printf("%s:\n", tempHeap->name);
	int i;
	for(i=0 ; i<maxHeap->size; i++){
		insertToHeap(tempHeap,maxHeap->heap[i]);
	}
	for(i=0 ; i<maxHeap->size; i++){
		printf("%i. ", i+1);
		element temp = PopMaxHeap(tempHeap);
		maxHeap->printElement(temp);
		maxHeap->destroyElement(temp);

	}
	if(maxHeap->size == 0)
		printf("No elements.\n\n");
	tempHeap->size = maxHeap->size;
	destroyHeap(tempHeap);

	return HeapHasPrinted;

};


element PopMaxHeap(MaxHeap maxHeap){
	if (maxHeap == NULL)
		return NULL;
	if (maxHeap->size == 0){
		return NULL;
	}
	if (maxHeap->size == 1){
		maxHeap->size--;
		element temp = maxHeap->heap[0];
		maxHeap->heap[0] = NULL;
		return temp;
	}
	element temp = maxHeap->heap[0];
	maxHeap->heap[0] = maxHeap->heap[maxHeap->size-1];
	maxHeap->heap[maxHeap->size-1] = NULL;
	maxHeap->size--;
	Heapify(maxHeap, 0);
	return temp;
};


element TopMaxHeap(MaxHeap maxHeap){
	if (maxHeap == NULL)
		return NULL;
	if (maxHeap->size == 0)
		return NULL;
	return maxHeap->heap[0];
};


char *getHeapId(MaxHeap maxHeap){
	if (maxHeap == NULL)
		return NULL;
	return maxHeap->name;
};


int getHeapCurrentSize(MaxHeap maxHeap){
	if (maxHeap == NULL)
		return -1;
	return maxHeap->size;
};


bool heapNameCheck(MaxHeap maxHeap, element name){
	if (strcmp(maxHeap->name, (char*)name) == 0)
		return true;
	return false;
};


MaxHeap copyHeap(MaxHeap maxHeap){ ///// TODO:REPAIR
	return maxHeap;
};





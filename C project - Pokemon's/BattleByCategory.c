#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "MaxHeap.h"
#include "BattleByCategory.h"
#include "Defs.h"


struct battle_s {
	int numberOfCategories;
	int capacity;
	char *categoriesNames;
	LinkedList categoriesList;
	copyFunction copyElement;
	freeFunction destroyElement;
	equalFunction equalFunction;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
	printFunction printElement;
};

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,
		freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){

	if(categories == NULL || equalElement == NULL || copyElement == NULL || freeElement == NULL || getCategory == NULL || getAttack == NULL || printElement == NULL )
		return NULL;

	struct battle_s *newBattle = (struct battle_s *)malloc(sizeof(struct battle_s));
	if (newBattle == NULL){
		printf("Memory problem");
		return NULL;
	}
	newBattle->categoriesNames = malloc(strlen(categories)+1);
	if (newBattle->categoriesNames == NULL){
		free(newBattle);
		return NULL;
	}
	strcpy(newBattle->categoriesNames, categories);
	newBattle->numberOfCategories = numberOfCategories;
	newBattle->capacity = capacity;
	newBattle->copyElement = copyElement;
	newBattle->destroyElement = freeElement;
	newBattle->equalFunction = equalElement;
	newBattle->getCategory = getCategory;
	newBattle->getAttack = getAttack;
	newBattle->printElement = printElement;
	newBattle->categoriesList = createLinkedList((copyFunction)copyHeap, (freeFunction)destroyHeap, (GetkeyInElement)heapNameCheck, equalElement, (printFunction)printHeap);
	if (newBattle->categoriesList == NULL){
		printf("Memory problem");
		return NULL;
	}
	char temp[50];
	strcpy(temp, categories);
	char d[] = ",";
	char *type = strtok(temp, d);
	while (type != NULL){
		appendNode(newBattle->categoriesList, CreateHeap(copyElement, freeElement, equalElement, printElement, type, capacity));
		type = strtok(NULL, ",");
	}
	return newBattle;
};


status destroyBattleByCategory(Battle b){
	if (b == NULL)
		return failure;
	destroyList(b->categoriesList);
	free(b->categoriesNames);
	free(b);
	return success;
};


status insertObject(Battle b, element elem){
	if (b == NULL || elem == NULL)
		return failure;
	MaxHeap tempMaxHemp = searchByKeyInlist(b->categoriesList,b->getCategory(elem));
	if (tempMaxHemp != NULL){
		if (insertToHeap(tempMaxHemp, elem) == ElementInserted )
			return success;
		return failure;
	}
	return failure;
};


void displayObjectsByCategories(Battle b){
	if (b == NULL)
		return;
	displayList(b->categoriesList);
};


element removeMaxByCategory(Battle b,char* category){
	if (b == NULL || category == NULL)
		return NULL;
	MaxHeap tempMaxHemp = searchByKeyInlist(b->categoriesList, category);
	if (tempMaxHemp == NULL)
		return NULL;
	if(getHeapCurrentSize(tempMaxHemp) < 0)
		return NULL;
	return PopMaxHeap(tempMaxHemp);
};


int getNumberOfObjectsInCategory(Battle b,char* category){
	if (b == NULL || category == NULL)
		return 0;
	MaxHeap tempMaxHemp = searchByKeyInlist(b->categoriesList, category);
	if (tempMaxHemp == NULL)
		return 0;
	return getHeapCurrentSize(tempMaxHemp);
};


element fight(Battle b,element elem){
	if (b == NULL || elem == NULL)
		return NULL;

	element maxElement = NULL;
	element CurrmaxElement = NULL;
	int currMax = -11111;
	int elemFirstUpdated, firstAttackToReturn;
	int elemTwoUpdated, secondAttackToReturn;
	int i;
	int currGap;
	char temp[300];
	strcpy(temp, b->categoriesNames);
	char d[] = ",";
	char *type = strtok(temp, d);
	for (i=0 ; i<b->numberOfCategories ; i++){
		MaxHeap tempMaxHemp = searchByKeyInlist(b->categoriesList, type);
		if(getHeapCurrentSize(tempMaxHemp) == 0){
			type = strtok(NULL, ",");
			continue;
		}
		CurrmaxElement = TopMaxHeap(tempMaxHemp);
		currGap = b->getAttack(CurrmaxElement, elem, &elemFirstUpdated, &elemTwoUpdated);
		if (currGap > currMax){
			currMax = currGap;
			maxElement = CurrmaxElement;
			firstAttackToReturn = elemFirstUpdated;
			secondAttackToReturn = elemTwoUpdated;
		}
		type = strtok(NULL, ",");
	}
	if(maxElement == NULL){
		printf("There are no Pokemons to fight against you.\n");
		return NULL;
	}

	printf("The final battle between:\n");
	b->printElement(elem);

	printf("In this battle his attack is :%d\n\n", secondAttackToReturn);

	printf("against ");
	b->printElement(maxElement);

	printf("In this battle his attack is :%d\n\n", firstAttackToReturn);

	if (currMax > 0){
		printf("THE WINNER IS:\n");
		b->printElement(maxElement);
		return maxElement;
	}
	if (currMax < 0){
		printf("THE WINNER IS:\n");
		b->printElement(elem);
		return elem;
	}
	printf("IT IS A DRAW.\n");
	return NULL;

};



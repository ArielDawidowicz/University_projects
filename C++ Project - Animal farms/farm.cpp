#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "farm.h"
#include "Animal.h"
using namespace std;


int farm::ID = 0;

/* Default constructor */
farm::farm(){
	money = 10;
	numOfAnimals = 0;
	numOfMilk = 0;
	numOfWool = 0;
	numOfEggs = 0;
	animalVec = {};
	farmID = 0;
	haveProducts = false;
	potentialBuyers = {};
	numOfpotentialBuyers = 0;
	ID++;
}

/* Returns the amount of money the farm has */
int farm::getMoney()const{
	return money;
}

/* Returns the amount of Animals the farm has */
int farm::getNumOfAnimals()const{
	return numOfAnimals;
}

/* Returns the amount of Milk(Product) the farm has */
int farm::getNumOfMilk()const{
	return numOfMilk;
}

/* Returns the amount of Wool(Product) the farm has */
int farm::getNumOfWool()const{
	return numOfWool;
}

/* Returns the amount of Eggs(Product) the farm has */
int farm::getNumOfEggs()const{
	return numOfEggs;
}

int farm::getNumOfpotentialBuyers()const{
	return numOfpotentialBuyers;
}


/* Setting new amount of money to the farm */
void farm::setMoney(int amount){
	money = amount;
}

/* Setting new amount of animals the farm has */
void farm::setNumOfAnimals(int amount){
	numOfAnimals = amount;
}

/* Setting new amount Milk(product) the farm has */
void farm::setNumOfMilk( int amount){
	numOfMilk = amount;
}

/* Setting new amount Wool(product) the farm has */
void farm::setNumOfWool( int amount){
	numOfWool = amount;
}

/* Setting new amount Eggs(product) the farm has */
void farm::setNumOfEggs( int amount){
	numOfEggs = amount;
}

void farm::updateAnimalsYears(){
	int i;
	for (i=0 ;i< animalVec.size(); i++){
		animalVec[i]->increaseAge();
	}
    removeOldAnimals();
}

void farm::removeOldAnimals(){
    int i;
    for (i=0; i<animalVec.size(); i++){
        if (animalVec[i]->getAge() == animalVec[i]->getmaxAge()){
            delete animalVec[i];
            animalVec.erase(animalVec.begin()+i);
            i--;
            numOfAnimals--;
        }
    }
}

void farm::deleteAllAnimals() {
    int i;
    for (i=0 ; i<animalVec.size(); i++){
        delete animalVec[i];
    }
}


void farm::printFarm()const{
	cout << ", Products: Milk[" << numOfMilk << "], Wool[" << numOfWool << "], Eggs[" << numOfEggs << "]" << endl;
}


farm::~farm() {
}



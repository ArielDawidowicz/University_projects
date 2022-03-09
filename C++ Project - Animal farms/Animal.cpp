#include "Animal.h"


/* Returns the age of the animal */
int Animal::getAge()const{
	return age;
}

/* Returns the maxAge of the animal */
int Animal::getmaxAge()const{
	return maxAge;
}

/* Setting new age to the animal */
void Animal::increaseAge(){
	age++;
}

Animal::~Animal() {
	// TODO Auto-generated destructor stub
}



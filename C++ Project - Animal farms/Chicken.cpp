#include "Chicken.h"

int Chicken::price = 3;

Chicken::Chicken():Animal(){
	maxAge = 3;
    age = 0;
}


Chicken::~Chicken(){};

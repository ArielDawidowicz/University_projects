#ifndef SHEEP_H_
#define SHEEP_H_
#include "Animal.h"


class Sheep : public Animal{

    static int price;
public:
	Sheep();
    static int getPrice(){return price;}
	virtual ~Sheep();

};

#endif /* SHEEP_H_ */

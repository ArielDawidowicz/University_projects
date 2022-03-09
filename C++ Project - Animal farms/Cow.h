#ifndef COW_H_
#define COW_H_
#include "Animal.h"

class Cow : public Animal{
    static int price;
public:
	Cow();
    static int getPrice(){return price;}
	virtual ~Cow();
};

#endif /* COW_H_ */

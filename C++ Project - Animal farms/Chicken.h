#ifndef CHICKEN_H_
#define CHICKEN_H_
#include "Animal.h"

class Chicken : public Animal{

static int price;
public:
    Chicken();
    static int getPrice(){return price;}
    virtual ~Chicken();
};

#endif /* CHICKEN_H_ */

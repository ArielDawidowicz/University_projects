#ifndef FARM_H_
#define FARM_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Animal.h"
using namespace std;

class farm {

protected:
	static int ID;
	int farmID;
	int money;
	int numOfAnimals;
	int numOfMilk;
	int numOfWool;
	int numOfEggs;
	int numOfpotentialBuyers;
	vector<farm*> potentialBuyers;
	vector<Animal*> animalVec;

public:
    bool haveProducts;
	/* Default constructor */
	farm();

	virtual void updateBuyers()=0;

	/* Sheep farm implements this function and not the other AddFarm functions */
	virtual void AddCowFarm(const farm* f1)=0;

	/* Chicken farm implements this function and not the other AddFarm functions */
	virtual void AddSheepFarm(const farm* f1)=0;

	/* Cow farm implements this function and not the other AddFarm functions */
	virtual void AddChickenFarm(const farm* f1)=0;

	/* Chicken farm implements this function and not the other sells me functions */
	virtual void SheepFarmSellsMe(farm* f1)const=0;

	/* Cow farm implements this function and not the other sells me functions */
	virtual void ChickenFarmSellsMe(farm* f1)const=0;

	/* Sheep farm implements this function and not the other sells me functions */
	virtual void CowFarmSellsMe(farm* f1)const=0;

	/* Each animal in the farm produce his thing and add it to the products list */
	virtual void Produce()=0;

	/* Selling products to potential buyers */
	virtual void SellProducts()=0;

	/* buying from seller the appropriate product */
	virtual void BuyProduct(farm *f1)=0;

	/* Buying the max number of animals with the budget */
	virtual void BuyAnimals()=0;

	/* Returns the amount of money the farm has */
	int getMoney()const;

	/* Returns the amount of Animals the farm has */
	int getNumOfAnimals()const;

	/* Returns the amount of Milk(Product) the farm has */
	int getNumOfMilk()const;

	/* Returns the amount of Wool(Product) the farm has */
	int getNumOfWool()const;

	/* Returns the amount of Eggs(Product) the farm has */
	int getNumOfEggs()const;

	/* return farmID */
	int getFarmID(){return farmID;}

	/* returns the number of potential buyers */
	int getNumOfpotentialBuyers()const;

	/* Setting new amount of money to the farm */
	void setMoney(int amount);

	/* Setting new amount of animals the farm has */
	void setNumOfAnimals(int amount);

	/* Setting new amount Milk(product) the farm has */
	void setNumOfMilk(int amount);

	/* Setting new amount Wool(product) the farm has */
	void setNumOfWool(int amount);

	/* Setting new amount Eggs(product) the farm has */
	void setNumOfEggs(int amount);

    /*  increasing the year of the animals */
    void updateAnimalsYears();

	/* Print the farm data */
	virtual void printFarm()const;

	/*Return curr ID counter*/
	static int getiD(){return ID;}

   /* Removes the animals that reached to the maxAge */
    void removeOldAnimals();

    /* this function clears the memory of the animals in farm vector */
    void deleteAllAnimals();

	/* Destructor */
	virtual ~farm();
};

#endif /* FARM_H_ */
// those
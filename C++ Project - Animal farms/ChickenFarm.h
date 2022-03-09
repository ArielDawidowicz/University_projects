#ifndef CHICKENFARM_H_
#define CHICKENFARM_H_
#include "farm.h"



class ChickenFarm : public farm{

public:
	ChickenFarm();
	virtual ~ChickenFarm();

	virtual void updateBuyers();

	/* Adds cow farm to chicken potential buyers */
	virtual void AddCowFarm(const farm* f1);

	/* no implementation */
	virtual void AddSheepFarm(const farm* f1){};

	/* no implementation */
	virtual void AddChickenFarm(const farm* f1){};

	/* Adds this chicken farm to sheep farm potential buyers */
	virtual void SheepFarmSellsMe(farm* f1)const;

	/* no implementation */
	virtual void ChickenFarmSellsMe(farm* f1)const{};

	/* no implementation */
	virtual void CowFarmSellsMe(farm* f1)const{};

	/* Each animal in the farm produce his thing and add it to the products list */
	virtual void Produce();

	/* Selling eggs to potential buyers */
	virtual void SellProducts();

    virtual void BuyProduct(farm *f1);

	/* Buying the max number of animals with the budget */
	virtual void BuyAnimals();

	/* overrides the farm class print funtion */
	virtual void printFarm()const;


};

#endif /* CHICKENFARM_H_ */

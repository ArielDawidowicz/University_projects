#ifndef COWFARM_H_
#define COWFARM_H_
#include "farm.h"


class CowFarm : public farm{

public:
	CowFarm();
	virtual ~CowFarm();

	virtual void updateBuyers();

	/* no implementation */
	virtual void AddCowFarm(const farm* f1){};

	/* Adds sheep farm to cows potential buyers */
	virtual void AddSheepFarm(const farm* f1);

	/* no implementation */
	virtual void AddChickenFarm(const farm* f1){};

	/* no implementation */
	virtual void SheepFarmSellsMe(farm* f1)const{};

	/* Adds this cowfarm farm to sheeps farm potential buyers */
	virtual void ChickenFarmSellsMe(farm* f1)const;

	/* no implementation */
	virtual void CowFarmSellsMe(farm* f1)const{};

	/* Each animal in the farm produce his thing and add it to the products list */
	virtual void Produce();

	/* Buying the max number of products with the budget */
	virtual void SellProducts();

	/* used to buy eggs */
	virtual void BuyProduct(farm *f1);

	/* Buying the max number of animals with the budget */
	virtual void BuyAnimals();

	/* overrides the farm class print funtion */
	virtual void printFarm() const;
};

#endif /* COWFARM_H_ */

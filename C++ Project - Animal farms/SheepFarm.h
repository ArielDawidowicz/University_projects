#ifndef SHEEPFARM_H_
#define SHEEPFARM_H_
#include "farm.h"

class SheepFarm : public farm{

public:

	SheepFarm();
	virtual ~SheepFarm();

	virtual void updateBuyers();

	/* no implementation */
	virtual void AddCowFarm(const farm* f1){};

	/* no implementation */
	virtual void AddSheepFarm(const farm* f1){};

	/* Adds chicken farm to sheepsfarm potential buyers */
	virtual void AddChickenFarm(const farm* f1);

	/* no implementation */
	virtual void SheepFarmSellsMe(farm* f1)const{};

	/* no implementation */
	virtual void ChickenFarmSellsMe(farm* f1)const{};

	/* Adds this sheepfarm to cows farm potential buyers */
	virtual void CowFarmSellsMe(farm* f1)const;

	/* Each animal in the farm produce his thing and add it to the products list */
	virtual void Produce();

	/* Selling Wool to potential buyers */
	virtual void SellProducts();

    virtual void BuyProduct(farm *f1);

	/* Buying the max number of animals with the budget */
	virtual void BuyAnimals();

	/* overrides the farm class print funtion */
	virtual void printFarm() const;
};

#endif /* SHEEPFARM_H_ */

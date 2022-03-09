#include "CowFarm.h"
#include "Animal.h"
#include "farm.h"
#include "Cow.h"
#include "Products.h"

CowFarm::CowFarm() : farm(){

	farmID = farm::getiD();
	int i;
	for(i=0 ; i<3; i++){
		Animal*temp = new Cow();
		this->animalVec.push_back(temp);
		numOfAnimals++;
	}
}

void CowFarm::updateBuyers(){
	if ( numOfMilk > 0)
		haveProducts = true;
	else{
		haveProducts = false;
	}
};


void CowFarm::AddSheepFarm(const farm* f1){
	this->potentialBuyers.push_back(const_cast<farm *>(f1));
	numOfpotentialBuyers ++;
	cout << "Cow farm("<< this->getFarmID() << ") Added Sheep farm("<< const_cast<farm *>(f1)->getFarmID() << ") to his client list"<< endl;

};


void CowFarm::ChickenFarmSellsMe(farm* f1)const{
	f1->AddCowFarm(const_cast<CowFarm *>(this));
}


void CowFarm::Produce(){
	int i;
	for(i=0 ; i< (int)animalVec.size(); i++){
		numOfMilk += animalVec[i]->getAge();
	}
    updateBuyers();
}

void CowFarm::SellProducts() {
    int i;
    for (i = 0; i < numOfpotentialBuyers; i++) {
        if(numOfMilk>0) {
            farm *f1 = potentialBuyers[i];
            f1->BuyProduct(this);
        }
    }
    updateBuyers();
}

void CowFarm::BuyProduct(farm* f1){
    int numOfProducts = 0;
    while(f1->haveProducts == true && this->money >= eggPrice) {
        money--;
        numOfEggs++;
        numOfProducts++;
        f1->setMoney(f1->getMoney() + eggPrice);
        f1->setNumOfEggs(f1->getNumOfEggs() - 1);
        f1->updateBuyers();
    }
    if (numOfProducts > 0)
        cout << "Cow farm(" << farmID << ") bought " << numOfProducts << " eggs for " << numOfProducts*eggPrice << " dollars from Chicken farm(" << f1->getFarmID() << ")" << endl;
}

/* Buying the max number of animals with the budget */
void CowFarm::BuyAnimals(){
	int numOfPurchases = 0;
    while (money >= Cow::getPrice()){
		Animal *tmp = new Cow();
		animalVec.push_back(tmp);
		money -= Cow::getPrice();
        numOfAnimals++;
        numOfPurchases++;
    }
    if(numOfPurchases > 0)
     cout << "Cow farm(" << farmID << ") bought " << numOfPurchases << " cows for " << numOfPurchases*Cow::getPrice() << " dollars" << endl;
}

void CowFarm::printFarm()const{
	cout << "Farm Id: " << farmID << ", type: Cow farm, Money: " << money << ", Animals: " << numOfAnimals << " cows" ;
	farm::printFarm();
}

CowFarm::~CowFarm() {}



#include "SheepFarm.h"
#include "Sheep.h"
#include "Animal.h"
#include "ChickenFarm.h"
#include "Products.h"




SheepFarm::SheepFarm() : farm(){
	farmID = farm::getiD();
	int i;
	for(i=0 ; i<3; i++){
		Animal*temp = new Sheep();
		this->animalVec.push_back(temp);
		numOfAnimals++;
	}
}

void SheepFarm::updateBuyers(){
	if ( numOfWool > 0)
		haveProducts = true;
	else{
		haveProducts = false;
	}
}

void SheepFarm::AddChickenFarm(const farm* f1){
	potentialBuyers.push_back(const_cast<farm *>(f1));
	numOfpotentialBuyers ++;
	cout << "Sheep farm("<< this->getFarmID() << ") Added Chicken farm("<< const_cast<farm *>(f1)->getFarmID() << ") to his client list"<< endl;
}


void SheepFarm::CowFarmSellsMe(farm* f1)const{
	f1->AddSheepFarm(const_cast<SheepFarm *>(this));
}


void SheepFarm::Produce(){
	int i;
	for(i=0 ; i< (int)animalVec.size(); i++){
		numOfWool += animalVec[i]->getAge();
	}
    updateBuyers();
}


void SheepFarm::SellProducts(){
	int i;
    for (i=0 ; i< numOfpotentialBuyers ; i++) {
        if (numOfWool > 0) {
            farm *f1 = potentialBuyers[i];
            f1->BuyProduct(this);
        }
    }
    updateBuyers();
}

void SheepFarm::BuyProduct(farm *f1){
    int numOfProducts = 0;
    while(f1->haveProducts == true && money >= milkPrice) {
        money-=3;
        numOfMilk++;
        numOfProducts++;
        f1->setMoney(f1->getMoney() + milkPrice);
        f1->setNumOfMilk(f1->getNumOfMilk() - 1);
        f1->updateBuyers();
    }
    if (numOfProducts > 0)
        cout << "Sheep farm(" << farmID << ") bought " << numOfProducts << " milk for " << numOfProducts*milkPrice << " dollars from Cow farm(" << f1->getFarmID() << ")" << endl;
}

void SheepFarm::BuyAnimals(){
	int numOfPurchases = 0;
    while (money >= Sheep::getPrice()){
		Animal *tmp = new Sheep();
		animalVec.push_back(tmp);
		money -= Sheep::getPrice();
        numOfAnimals++;
        numOfPurchases++;
    }
    if(numOfPurchases > 0)
        cout << "Sheep farm(" << farmID << ") bought " << numOfPurchases << " sheeps for " << numOfPurchases*Sheep::getPrice() << " dollars" << endl;
}

void SheepFarm::printFarm() const{
	cout << "Farm Id: " << farmID << ", type: Sheep farm, Money: " << money << ", Animals: " << numOfAnimals << " sheep" ;
	farm::printFarm();
}

SheepFarm::~SheepFarm() {}



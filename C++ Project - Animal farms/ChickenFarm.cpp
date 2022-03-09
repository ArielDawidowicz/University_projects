#include "ChickenFarm.h"
#include "Chicken.h"
#include "Animal.h"
#include "Products.h"


ChickenFarm::ChickenFarm() : farm(){
    farmID = farm::getiD();
    int i;
	for(i=0 ; i<3; i++){
		Animal*temp = new Chicken();
		this->animalVec.push_back(temp);
		numOfAnimals++;
	}
}

void ChickenFarm::updateBuyers(){
	if ( numOfEggs > 0)
		haveProducts = true;
	else{
		haveProducts = false;
	}
}

void ChickenFarm::AddCowFarm(const farm* f1){
	potentialBuyers.push_back(const_cast<farm *>(f1));
	numOfpotentialBuyers ++ ;
	cout << "Chicken farm("<< this->getFarmID() << ") Added Cow farm("<< const_cast<farm *>(f1)->getFarmID() << ") to his client list"<< endl;
}


void ChickenFarm::SheepFarmSellsMe(farm* f1) const{
	f1->AddChickenFarm(const_cast<ChickenFarm *>(this));
}

void ChickenFarm::Produce(){
	int i, j=0;
	for(i=0 ; i< (int)animalVec.size(); i++){
        j += animalVec[i]->getAge();
	}
    numOfEggs += j;
    updateBuyers();
}

void ChickenFarm::SellProducts(){
	int i;
    for (i=0 ; i< numOfpotentialBuyers ; i++){
        if (numOfEggs > 0) {
            farm *f1 = potentialBuyers[i];
            f1->BuyProduct(this);
        }
    }
    updateBuyers();
}

void ChickenFarm::BuyProduct(farm *f1){
    int numOfProducts = 0;
    while(f1->haveProducts && money >= woolPrice) {
        money-=2;
        numOfWool++;
        numOfProducts++;
        f1->setMoney(f1->getMoney() + woolPrice);
        f1->setNumOfWool(f1->getNumOfWool() - 1);
        f1->updateBuyers();
    }
    if (numOfProducts > 0)
        cout << "Chicken farm(" << farmID << ") bought " << numOfProducts << " wool for " << numOfProducts*woolPrice << " dollars from Sheep farm(" << f1->getFarmID() << ")" << endl;
}


void ChickenFarm::BuyAnimals(){
	int numOfPurchases = 0;
    while (money >= Chicken::getPrice()){
		Animal *tmp = new Chicken();
		animalVec.push_back(tmp);
		money -= Chicken::getPrice();
        numOfAnimals++;
        numOfPurchases++;
	}
    if(numOfPurchases > 0)
        cout << "Chicken farm(" << farmID << ") bought " << numOfPurchases << " chickens for " << numOfPurchases*Chicken::getPrice() << " dollars" << endl;
}

void ChickenFarm::printFarm()const{
	cout << "Farm Id: " << farmID << ", type: Chicken Farm, Money: " << money << ", Animals: " << numOfAnimals << " chickens" ;
	farm::printFarm();
}

ChickenFarm::~ChickenFarm() {}


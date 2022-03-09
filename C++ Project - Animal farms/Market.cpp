#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "farm.h"
#include "CowFarm.h"
#include "SheepFarm.h"
#include "ChickenFarm.h"
#include "Market.h"
#include "Exceptions.h"
#include <exception>


Market::Market(){
	years = 0;
	farms = {};
}

/* Create Farms */
void Market::newFarms(){
	std::string tempCin;
	int numOfcowFarms, numOfsheepFarms, numOfchickenFarms;
	int i ,j;
    bool next = true;
	cout << "----Creating new farms----" << endl;

    while (next) {
        try {
            cout << "How many new cow farms will be added this year?" << endl;
            cin >> tempCin;
            numOfcowFarms = stoi(tempCin);
            if (numOfcowFarms < 0)
                throw CowException();

            cout << "How many new sheep farms will be added this year?" << endl;

            cin >> tempCin;
            numOfsheepFarms = stoi(tempCin);
            if (numOfsheepFarms < 0)
                throw SheepException();

            cout << "How many new chicken farms will be added this year?" << endl;
            cin >> tempCin;
            numOfchickenFarms = stoi(tempCin);
            if (numOfchickenFarms < 0)
                throw ChickenException();
            next = false;
            }

        catch (exception& e){
            cout << e.what() << endl;
        }
    }

	/* if any invalid input print again how many of each */

	/*if inserted valid input - start adding the new farms to the market and to the other farms */

	cout << "----Adding new farms to market----" << endl;

	/* inserting new cow farms */

	for (i=0 ; i<numOfcowFarms ; i++){
		farm* tmpCowFarm = new CowFarm();

		/* Adding the new cow farm as potential buyer to the appropriate farm, and potential buyers to the new cow farm */
		for (j=0 ; j<(int)farms.size() ;j++){
			farms[j]->CowFarmSellsMe(tmpCowFarm);
			farms[j]->AddCowFarm(tmpCowFarm);

		}
		farms.push_back(tmpCowFarm);
	}

	/* inserting new sheep farms */
	for (i=0 ; i<numOfsheepFarms ; i++){
		farm* tmpSheepFarm = new SheepFarm();

		/* Adding the new sheep farm as potential buyer to the appropriate farm, and potential buyers to the new sheep farm */
		for (j=0 ; j<(int)farms.size() ;j++){
			farms[j]->SheepFarmSellsMe(tmpSheepFarm);
			farms[j]->AddSheepFarm(tmpSheepFarm);

		}
		farms.push_back(tmpSheepFarm);
	}

	/* inserting new chicken farms */
	for (i=0 ; i<numOfchickenFarms ; i++){
		farm* tmpChickenFarm = new ChickenFarm();

		/* Adding the new chicken farm as potential buyer to the appropriate farm, and potential buyers to the new chicken farm */
		for (j=0 ; j<(int)farms.size() ;j++){
			farms[j]->ChickenFarmSellsMe(tmpChickenFarm);
			farms[j]->AddChickenFarm(tmpChickenFarm);

		}
		farms.push_back(tmpChickenFarm);
	}
}

/* Peasant trade and then buying animal */
void Market::tradeDay(){
    cout << "----Begin Market----" << endl;

	/* Each farm sells the products to potential buyers */
	int i;
	for(i=0 ;i<(int)farms.size(); i++){
		farms[i]->SellProducts();
	}
    cout << "----Buy Animals----" << endl;
    for(i=0 ;i<(int)farms.size(); i++){
        farms[i]->BuyAnimals();
    }
}

/* Moving to the next year trading day, Creating new farms, Farm productivity, Trade day -
 * Year ++ , if Animals should leave(because of the age) they been removed .and adding 10$ to budget of each Farm in the market */
void Market::nextYear(){
    int i,j;

    /* part 1 - creating new farms */
    newFarms();

    /* part 2 - each farm Produces its produce */
    for(i=0 ;i<(int)farms.size(); i++){
        farms[i]->Produce();
    }

    /* part 3 - Trade day*/
    tradeDay();

    /* part 4 - updating Animals year and adding 10$ to each farm */
    for(i=0 ;i<(int)farms.size(); i++){
        farms[i]->setMoney(farms[i]->getMoney()+10);
        farms[i]->updateAnimalsYears();
        farms[i]->removeOldAnimals();

    }
    years++;
}

/* Passing years by the user decision. each year: farm production, trade day , removing animals if needed-
 * and adding 10$ to each farm in the market */
void Market::fastForwardYears(){
    std::string tempCin;
    int timesToForward, i, j;
    cout << "How many years to fast forward?" << endl;
    cin >> tempCin;
    timesToForward = stoi(tempCin); // minus case debug
    for (i=0 ; i<timesToForward; i++){
        /* part 1 - each farm Produces its produce */
        for(j=0 ;j<(int)farms.size(); j++){
            farms[j]->Produce();
        }
        /* part 2 - Trade day */
        tradeDay();

        /* part 3 - updating Animals year and adding 10$ to each farm */
        for(j=0 ;j<(int)farms.size(); j++){
            farms[j]->setMoney(farms[j]->getMoney()+10);
            farms[j]->updateAnimalsYears();
            farms[j]->removeOldAnimals();
        }
        years++;
    }
}

/* Returns the years the market is running */
int Market::getYear(){
	return years;
}

/* set new year to the market */
void Market::setYear(int year){
	years = year;
}

/* Print the data of the farms in the market */
void Market::printMarketFarms(){
    cout << "----Market Farms----" << endl;
	int i;
	for(i=0 ; i<(int)farms.size(); i++){
		farms[i]->printFarm();
	}

}

Market::~Market() {
    int i;
    for(i=0 ; i<farms.size(); i++){
        farms[i]->deleteAllAnimals();
        delete farms[i];
    }
}


#ifndef MARKET_H_
#define MARKET_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "farm.h"
using namespace std;

class Market {

private:
	int years;
	vector<farm*> farms;
public:

	/* Default constractor */
	Market();

	/* Create Farms */
	void newFarms();

	/* Peasent trade and then buing animal */
	void tradeDay();

	/* Moving to the next year trading day, Creating new farms, Farm productivity, Trade day -
	 * Year ++ , if Animals should leave(because of the age) they been removed .and adding 10$ to budget of each Farm in the market */
	void nextYear();

	/* Passing years by the user decision. each year: farm production, trade day , removing animals if needed-
	 * and adding 10$ to each farm in the market */
	void fastForwardYears();


	/* Returns the years the market is running */
	int getYear();

	/* set new year to the market */
	void setYear(int year);

	/* Print the data of the farms in the market */
	void printMarketFarms();

	/* Destructor */
	virtual ~Market();
};

#endif /* MARKET_H_ */

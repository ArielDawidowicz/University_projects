all: CPP_FARM clean

CPP_FARM: farmMarket.o Market.o  farm.o SheepFarm.o  CowFarm.o ChickenFarm.o Animal.o Cow.o Chicken.o  Sheep.o
	 g++ farmMarket.o Market.o farm.o SheepFarm.o  CowFarm.o ChickenFarm.o Animal.o Cow.o Chicken.o Sheep.o -o CPP_FARM

farmMarket.o: farmMarket.cpp Market.h
	g++ -c farmMarket.cpp

Market.o: Market.cpp Market.h farm.h SheepFarm.h CowFarm.h ChickenFarm.h Exceptions.h
	g++ -c Market.cpp

farm.o: farm.cpp farm.h Animal.h
	g++ -c farm.cpp

SheepFarm.o: SheepFarm.cpp SheepFarm.h Sheep.h Animal.h ChickenFarm.h Products.h
	g++ -c SheepFarm.cpp

CowFarm.o: CowFarm.cpp CowFarm.h Animal.h farm.h Cow.h Products.h
	g++ -c CowFarm.cpp

ChickenFarm.o: ChickenFarm.cpp ChickenFarm.h Animal.h Chicken.h Products.h
	g++ -c ChickenFarm.cpp

Animal.o: Animal.cpp Animal.h
	g++ -c Animal.cpp
	
Cow.o: Cow.cpp Cow.h
	g++ -c Cow.cpp

Chicken.o: Chicken.cpp Chicken.h
	g++ -c Chicken.cpp

Sheep.o: Sheep.cpp Sheep.h
	g++ -c Sheep.cpp

	
clean:
	rm -f *.o 


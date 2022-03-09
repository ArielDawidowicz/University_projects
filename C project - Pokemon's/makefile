PokemonsBattles: MainSecond.o BattleByCategory.o Pokemon.o LinkedList.o  MaxHeap.o 
	gcc BattleByCategory.o MainSecond.o Pokemon.o LinkedList.o  MaxHeap.o  -o PokemonsBattles

MainSecond.o: MainSecond.c Defs.h BattleByCategory.h Pokemon.h LinkedList.h LinkedList.h
	gcc -c MainSecond.c

BattleByCategory.o: BattleByCategory.c BattleByCategory.h LinkedList.h LinkedList.h Defs.h
	gcc -c BattleByCategory.c

Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c
	
clean:
	rm -f *.o

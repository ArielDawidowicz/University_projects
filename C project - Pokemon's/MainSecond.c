#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "MaxHeap.h"
#include "Pokemon.h"
#include "LinkedList.h"
#include "BattleByCategory.h"



int main(int argc, char *argv[]){

	//this struct contains all Pokemon types
	typedef struct Pokemon_Type_Arr{
	int Size;
	PokemonType **typesArr;
	}PokemonTypeArr;

	//initalize pokemon type array
	void InitTypeArr(PokemonTypeArr *newPokemonTypeArrPtr){
		newPokemonTypeArrPtr->Size = 0;
		newPokemonTypeArrPtr->typesArr = NULL;
		return;
	};


	//Add to pokemon type array
	void AddToPokemonTypeArr(PokemonType *type, PokemonTypeArr *typeArr){
		if(typeArr->Size == 0){
			typeArr->typesArr = (struct Pokemon_t**)malloc(sizeof(PokemonType *));
			if(typeArr->typesArr == NULL){
				puts("Memory problem!");
				return;
			}
			typeArr->typesArr[0] = type;
			typeArr->Size++;
		}
		else{
			typeArr->typesArr = (struct Pokemon_t**)realloc(typeArr->typesArr,((typeArr->Size)+1)*sizeof(PokemonType *));
			if(typeArr->typesArr == NULL){
				puts("Memory problem!");
				return;
			}
			typeArr->Size++;
			typeArr->typesArr[(typeArr->Size)-1] = type;
		}return;
	};

	//Find type by name in type array(based on that that the type exist in the type array)
	PokemonType *FindType(PokemonTypeArr *typeArr, char *typeName){
		int i;
		for (i=0 ; i<typeArr->Size ;i++){
			if (strcmp(typeArr->typesArr[i]->Name, typeName) == 0 ){
				return typeArr->typesArr[i];
			}
		}
		return NULL;
	};

	/* Initialize the struct that contains all Pokemon Types */
	PokemonTypeArr mainPokemonTypeArr;
	InitTypeArr(&mainPokemonTypeArr);

	Battle battle1; // main battle

	/* reading and setting the configuration file */
	FILE *filePtr = fopen(argv[3], "r");
	char line[300];
	char tmpLine[300];
	char d[] = ",";
	char *slice;
	char *lineWithoutDelim;
	int i;
	char *name;
	char *species;
	double weight;
	double height;
	int attack;

	/* Checking if number of types is greater than 0 if true than -> save data of the configuration file. else -> main menu */
	if (atoi(argv[1])> 0) {
		fgets(line, sizeof(line), filePtr); // types
		fgets(line, sizeof(line), filePtr); // name of types
		lineWithoutDelim = strtok(line, "\r\n");
		battle1 = createBattleByCategory(atoi(argv[2]), atoi(argv[1]), line, (equalFunction) equal,(copyFunction) copyfunc,
				(freeFunction) freefunc, (getCategoryFunction)getcat, (getAttackFunction)getAttackFunc,(printFunction) PrintPokemon);
		slice = strtok(lineWithoutDelim, d);
		for (i=0 ; i<atoi(argv[1]); i++){
			AddToPokemonTypeArr(CreatePokemonType(slice), &mainPokemonTypeArr);
			slice = strtok(NULL, d);
		}
		/* getting effective aggainst me or other */
		fgets(line, sizeof(line), filePtr);
		while (strcmp(line, "Pokemons\r\n") != 0){
			lineWithoutDelim = strtok(line, "\r\n");
			lineWithoutDelim++;
			slice = strtok(lineWithoutDelim, " "); // A type;
			PokemonType *tempPokemonA = FindType(&mainPokemonTypeArr, slice);
			PokemonType *tempPokemonB;
			slice = strtok(NULL, " ");
			slice = strtok(slice, ":");  // effective agains me / others
			if (strcmp(slice, "effective-against-me") == 0){
				slice = strtok(NULL, d);
				while (slice != NULL){
					tempPokemonB = FindType(&mainPokemonTypeArr, slice);
					AddToEffectiveAgainstMe(tempPokemonA, tempPokemonB);
					slice = strtok(NULL, d);
				}
			}
			else{
				slice = strtok(NULL, d);
				while (slice != NULL){
					tempPokemonB = FindType(&mainPokemonTypeArr, slice);
					AddToEffectiveAgainstOthers(tempPokemonA, tempPokemonB);
					slice = strtok(NULL, d);
				}
			}
			fgets(line, sizeof(line), filePtr);
		}
		strcpy(tmpLine, line);
		fgets(line, sizeof(line), filePtr);
		while(strcmp(tmpLine, line) != 0){
			lineWithoutDelim = strtok(line, "\r\n");
			name = strtok(lineWithoutDelim, d);
			species = strtok(NULL, d);
			height = atof(strtok(NULL, d));
			weight = atof(strtok(NULL, d));
			attack = atoi(strtok(NULL, d));
			slice = strtok(NULL, d);
			PokemonType *tempPokemonNew = FindType(&mainPokemonTypeArr, slice);
			Pokemon *tempPokemon = CreatePokemon(name, species, tempPokemonNew, CreateBioInfo(height, weight, attack));
			insertObject(battle1, tempPokemon);
			freefunc(tempPokemon);
			strcpy(tmpLine, line);
			fgets(line, sizeof(line), filePtr);
		}
	} // if num of type > 0

	/*  Main menu */
	fclose(filePtr);
	char input = '1';
	while (input != '6'){
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");
		scanf("%s", &input);
		switch(input)
		{
			case '1':
						displayObjectsByCategories(battle1);
						break;

			case '2':
						for (i=0; i<atoi(argv[1]);i++)
							PrintPokemonType(mainPokemonTypeArr.typesArr[i]);
						break;

			case '3':
						printf("Please enter Pokemon type name:\n");
						scanf("%s", slice);
						PokemonType *tempPokemonType = FindType(&mainPokemonTypeArr, slice);
						if (tempPokemonType == NULL){
							printf("Type name doesn't exist.\n");
							break;
						}
						if (getNumberOfObjectsInCategory(battle1, slice) == atoi(argv[2])){
							printf("Type at full capacity.\n");
								break;
						}

						printf("Please enter Pokemon name:\n");
						scanf("%s", slice);
						char name0[300];
						strcpy(name0, slice);

						printf("Please enter Pokemon species:\n");
						scanf("%s", slice);
						char species0[300];
						strcpy(species0, slice);

						printf("Please enter Pokemon height:\n");
						scanf("%s", slice);
						height = atof(slice);

						printf("Please enter Pokemon weight:\n");
						scanf("%s", slice);
						weight = atof(slice);

						printf("Please enter Pokemon attack:\n");
						scanf("%s", slice);
						attack = atoi(slice);

						Pokemon *tempPokemon3 = CreatePokemon(name0, species0, tempPokemonType, CreateBioInfo(height, weight, attack));
						insertObject(battle1, tempPokemon3);
						printf("The Pokemon was successfully added.\n");
						PrintPokemon(tempPokemon3);
						freefunc(tempPokemon3);
						break;


			case '4':
						printf("Please enter type name:\n");
						scanf("%s", slice);
						PokemonType *tempPokemonType0 = FindType(&mainPokemonTypeArr, slice);
						if (tempPokemonType0 == NULL){
							printf("Type name doesn't exist.\n");
							break;
						}
						Pokemon *tempPokemon0 = removeMaxByCategory(battle1,  slice);
						if (tempPokemon0 == NULL){
							printf("There is no Pokemon to remove.\n");
							break;
						}
						printf("The strongest Pokemon was removed:\n");
						PrintPokemon(tempPokemon0);
						freefunc(tempPokemon0);
						tempPokemonType0->NumOfPokemos--;
						break;


			case '5':
						printf("Please enter Pokemon type name:\n");
						scanf("%s", slice);
						PokemonType *tempPokemonType1 = FindType(&mainPokemonTypeArr, slice);
						if (tempPokemonType1 == NULL){
							printf("Type name doesn't exist.\n");
							break;
						}
						printf("Please enter Pokemon name:\n");
						scanf("%s", slice);
						strcpy(name, slice);

						printf("Please enter Pokemon species:\n");
						scanf("%s", slice);
						strcpy(species, slice);

						printf("Please enter Pokemon height:\n");
						scanf("%s", slice);
						height = atof(slice);

						printf("Please enter Pokemon weight:\n");
						scanf("%s", slice);
						weight = atof(slice);

						printf("Please enter Pokemon attack:\n");
						scanf("%s", slice);
						attack = atoi(slice);

						Pokemon *tempPokemon1 = CreatePokemon(name, species, tempPokemonType1, CreateBioInfo(height, weight, attack));
						printf("You choose to fight with:\n");
						PrintPokemon(tempPokemon1);

						fight(battle1, tempPokemon1);
						freefunc(tempPokemon1);
						tempPokemonType1->NumOfPokemos--;

						break;


			case '6':

						for(i=0 ; i<mainPokemonTypeArr.Size; i++){
							FreeEffective(mainPokemonTypeArr.typesArr[i]);
						}
						for(i=0 ; i<mainPokemonTypeArr.Size; i++){
							FreeType(mainPokemonTypeArr.typesArr[i]);
						}
						free(mainPokemonTypeArr.typesArr);
						destroyBattleByCategory(battle1);
						printf("All the memory cleaned and the program is safely closed.\n");
						break;

			default:
						printf("Please choose a valid number.\n");

		}}

return EXIT_SUCCESS;
}

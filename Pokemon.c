#include "Pokemon.h"




PokemonType *CreatePokemonType(char *nameOfType){
	PokemonType *newPokTypePtr;
	newPokTypePtr = (PokemonType *)malloc(sizeof(PokemonType));
	if (newPokTypePtr == NULL){
		printf("Memory problem");
		return NULL;
	}
	newPokTypePtr->Name = malloc(strlen(nameOfType)+1);
	if(newPokTypePtr->Name == NULL){
		free(newPokTypePtr);
		printf("Memory problem");
		return NULL;
	}
	strcpy(newPokTypePtr->Name, nameOfType);
	newPokTypePtr->NumOfPokemos = 0;
	newPokTypePtr->NumofEffectiveAgainstMe = 0;
	newPokTypePtr->NumofEffectiveAgainstOthers = 0;
	newPokTypePtr->effective_against_me = NULL;
	newPokTypePtr->effective_against_others = NULL;
	return newPokTypePtr;

};

//create new biological information function
BioInfo * CreateBioInfo( double height, double weight, int attack){
	BioInfo *newBioInfoPtr = (BioInfo *)malloc(sizeof(BioInfo));
	if(newBioInfoPtr == NULL){
		printf("Memory problem");
		return NULL;
	}
	newBioInfoPtr->Attack = attack;
	newBioInfoPtr->Height = height;
	newBioInfoPtr->Weight = weight;
	return newBioInfoPtr;
};

//create a pokemon function
Pokemon * CreatePokemon(char *name, char *speciesInfo, PokemonType *type, BioInfo *bio){
	Pokemon *newPokemonPtr = (Pokemon *)malloc(sizeof(Pokemon));
	if(newPokemonPtr == NULL){
		printf("Memory problem");
		return NULL;
	}
	newPokemonPtr->Name = malloc(strlen(name)+1);
	if(newPokemonPtr->Name == NULL){
		free(newPokemonPtr);
		printf("Memory problem");
		return NULL;
	}
	strcpy(newPokemonPtr->Name, name);
	newPokemonPtr->Species = malloc(strlen(speciesInfo)+1);
	if(newPokemonPtr->Species == NULL){
		free(newPokemonPtr->Name);
		free(newPokemonPtr);
		printf("Memory problem");
		return NULL;
	}
	strcpy(newPokemonPtr->Species, speciesInfo);
	if (type == NULL || bio == NULL){
		puts("Pokemon not created");
		return NULL;
	}
	newPokemonPtr->Bio = bio;
	newPokemonPtr->Type = type;
	type->NumOfPokemos++;
	return newPokemonPtr;
};

//check if Type B in A's effective against me/others list (based on that that A and B exist)
Status CheckIfBInA(PokemonType *typeA, PokemonType *typeB, char *effective){
	int y;
	if (strcmp(effective, "me") == 0){
		if (typeA->NumofEffectiveAgainstMe == 0){
			return TypeBNotInA;
		}
		for (y=0 ;y< typeA->NumofEffectiveAgainstMe; y++){
			if(strcmp(typeA->effective_against_me[y]->Name, typeB->Name) == 0 ){
				return TypeBInA;
			}
		}
		return TypeBNotInA;
	}
	if (strcmp(effective, "others") == 0){
		for (y=0 ;y< typeA->NumofEffectiveAgainstOthers; y++){
			if(strcmp(typeA->effective_against_others[y]->Name, typeB->Name) == 0 ){
				return TypeBInA;
			}
		}
		return TypeBNotInA;
	}
	return TypeBNotInA;
};


Status AddToEffectiveAgainstMe(PokemonType *a, PokemonType *b){
	if(a == NULL || b == NULL)
		return TypeNotAdded;
	if (a->NumofEffectiveAgainstMe == 0){
		a->effective_against_me = (PokemonType **)malloc(sizeof(PokemonType *));
			if(a->effective_against_me == NULL)
				return TypeNotAdded;   // Allocation Problem
		a->effective_against_me[0] = b;
		a->NumofEffectiveAgainstMe++;
	}
	else{
		a->effective_against_me = (PokemonType **)realloc(a->effective_against_me, sizeof(PokemonType *)*(a->NumofEffectiveAgainstMe+1));
		if(a->effective_against_me == NULL)
			return TypeNotAdded;   // Allocation Problem
		a->NumofEffectiveAgainstMe++;
		a->effective_against_me[(a->NumofEffectiveAgainstMe)-1] = b;
	}
	return TypeAdded;
};


Status AddToEffectiveAgainstOthers(PokemonType *a, PokemonType *b){
	if(a == NULL || b == NULL)
		return TypeNotAdded;
	if (a->NumofEffectiveAgainstOthers == 0){
		a->effective_against_others = (PokemonType **)malloc(sizeof(PokemonType *));
			if(a->effective_against_others == NULL)
				return TypeNotAdded;   // Allocation Problem
		a->effective_against_others[0] = b;
		a->NumofEffectiveAgainstOthers++;
	}
	else{
		a->effective_against_others = (PokemonType **)realloc(a->effective_against_others, sizeof(PokemonType *)*(a->NumofEffectiveAgainstOthers+1));
		if(a->effective_against_others == NULL)
			return TypeNotAdded;   // Allocation Problem
		a->NumofEffectiveAgainstOthers++;
		a->effective_against_others[(a->NumofEffectiveAgainstOthers)-1] = b;
	}
	return TypeAdded;
};



PrintStatus PrintPokemon(Pokemon *pokemon){
	if (pokemon == NULL){
		return PrintNotSucceed;
	}
	printf( "%s :\n", pokemon->Name);
	printf( "%s, %s Type.\n", pokemon->Species, pokemon->Type->Name);
	printf( "Height: %.2f m    Weight: %.2f kg    Attack: %i\n\n", pokemon->Bio->Height, pokemon->Bio->Weight, pokemon->Bio->Attack);
	return PrintSucceed;
};


PrintStatus PrintPokemonType(PokemonType *type){
	if (type == NULL){
		return PrintNotSucceed;
	}
	printf( "Type %s -- %i pokemons\n", type->Name, type->NumOfPokemos);
	if(type->NumofEffectiveAgainstMe > 0)
		printf( "\tThese types are super-effective against %s:", type->Name);
	int i;
	int j = type->NumofEffectiveAgainstMe;
	if (j > 0){
		for (i=0; i <j-1 ;i++){
			printf("%s ,", type->effective_against_me[i]->Name);
		}printf("%s\n", type->effective_against_me[j-1]->Name);
	}
	if(type->NumofEffectiveAgainstOthers > 0)
		printf("\t%s moves are super-effective against:", type->Name);
	if(type->NumofEffectiveAgainstOthers == 0)
		printf("\n");
	j = type->NumofEffectiveAgainstOthers;
	if (j > 0){
		for (i=0 ; i<j-1 ;i++){
			printf("%s ,", type->effective_against_others[i]->Name);
		}printf("%s\n\n", type->effective_against_others[j-1]->Name);
	}
	return PrintSucceed;
}


void FreeEffective(PokemonType *type){
	free(type->effective_against_me);
	free(type->effective_against_others);
};

//free all types
void FreeType(PokemonType *type){
	free(type->Name);
	free(type);
};


Pokemon *copyfunc(Pokemon *pokemon){
	pokemon->Type->NumOfPokemos--;
	return CreatePokemon(pokemon->Name, pokemon->Species, pokemon->Type,CreateBioInfo(pokemon->Bio->Height, pokemon->Bio->Weight,pokemon->Bio->Attack));
}


void freefunc(Pokemon *pokemon){
	if (pokemon != NULL){
		free(pokemon->Name);
		free(pokemon->Species);
		free(pokemon->Bio);
		free(pokemon);
	}
};


int equal(Pokemon *pokemon, Pokemon *pokemon2){
	if (pokemon->Bio->Attack > pokemon2->Bio->Attack)
		return 1;
	if (pokemon->Bio->Attack < pokemon2->Bio->Attack)
		return -1;
	return 0;
};


char* getcat(Pokemon *pokemon){
	return getTypeName(pokemon->Type);
};


char* getTypeName(PokemonType *pokemonType){
	return pokemonType->Name;
};


int getAttackFunc (Pokemon *firstElem ,Pokemon *secondElem ,int* attackFirst,int* attackSecond){
	int firstElemWeakAgainstSecondElem = 0;
	int secondElemWeakAgainstFirstElem = 0;
	int firstAttack = firstElem->Bio->Attack;
	int secondAttack = secondElem->Bio->Attack;
	PokemonType *firtElemType = firstElem->Type;
	PokemonType *secondElemType = secondElem->Type;

	if (CheckIfBInA(firtElemType, secondElemType, "me") == TypeBInA)
		firstElemWeakAgainstSecondElem = 1;

	if (CheckIfBInA(firtElemType, secondElemType, "others") == TypeBInA)
		secondElemWeakAgainstFirstElem = 1;

	if (CheckIfBInA(secondElemType, firtElemType, "me") == TypeBInA)
		secondElemWeakAgainstFirstElem = 1;

	if (CheckIfBInA(secondElemType, firtElemType, "others") == TypeBInA)
		firstElemWeakAgainstSecondElem = 1;

	if (firstElemWeakAgainstSecondElem == 1 )
		firstAttack -= 10;

	if (secondElemWeakAgainstFirstElem == 1 )
		secondAttack -= 10;

	*attackFirst = firstAttack;
	*attackSecond = secondAttack;

	return firstAttack-secondAttack;

};



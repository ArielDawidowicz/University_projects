#ifndef POKEMON_H_
#define POKEMON_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

//Struct of pokemon types
typedef struct Pokemon_t{
	char *Name;
	int NumOfPokemos, NumofEffectiveAgainstMe, NumofEffectiveAgainstOthers;
	struct Pokemon_t **effective_against_me;
	struct Pokemon_t **effective_against_others;
}PokemonType;

//Struct of the pokemon biological information
typedef struct bio_info{
	double Height;
	double Weight;
	int Attack;
}BioInfo;

//Struct of pokemon
typedef struct pokemon_a{
	char *Name;
	char *Species;
	PokemonType *Type;
	BioInfo *Bio;
}Pokemon;


//create a pokemon function
Pokemon * CreatePokemon(char *name, char *speciesInfo, PokemonType *type, BioInfo *bio);

//create a new type of pokemon function
PokemonType * CreatePokemonType(char *nameOfType);

//create new biological information function
BioInfo * CreateBioInfo( double height, double weight, int attack);

// new enum to provide status information after function execution
typedef enum{TypeAdded, TypeNotAdded, TypeDeleted, TypeNotDeleted,TypeExist,TypeNotExist,TypeBInA,TypeBNotInA,PokemonExist,PokemonNotExist} Status;

//check if Type B in A's effective against me/others list (based on that that A and B exist)
Status CheckIfBInA(PokemonType *typeA, PokemonType *typeB, char *effective);

//add type B to A's effective_against_me list function
Status AddToEffectiveAgainstMe(PokemonType *a, PokemonType *b);

//add type B to A's effective_against_others list function
Status AddToEffectiveAgainstOthers(PokemonType *a, PokemonType *b);

// new enum to provide status information after prints function execution
typedef enum{PrintSucceed, PrintNotSucceed} PrintStatus;

//pokemon print function
PrintStatus PrintPokemon(Pokemon *pokemon);

//pokemon type print function
PrintStatus PrintPokemonType(PokemonType *type);


// free all effective arrays in types struct
void FreeEffective(PokemonType *type); //

//free types
void FreeType(PokemonType *type); // move

// this function returns a Deepcopy pointer of pokemon received
Pokemon *copyfunc(Pokemon *pokemon);

// this function deletes the pokemon and all of its data
void freefunc(Pokemon *pokemon);

// this function return 0 if both pokemos have the same attack
int equal(Pokemon *pokemon, Pokemon *pokemon2);

// this function returns the type of pokemon
char  *getcat(Pokemon *pokemon);

// this function returns the type name
char* getTypeName(PokemonType *pokemonType);

// return the first attack - second attack . also produce the attack of each element, The function transmits the information through the pointers received in the function.
int getAttackFunc (Pokemon *firstElem ,Pokemon *secondElem ,int* attackFirst,int* attackSecond);


#endif /* POKEMON_H_ */

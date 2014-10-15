// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "HunterView.h"
#include "Places.h"


#define TRUE 1
#define FALSE 0

#define DEBUG

void decideHunterMove(HunterView gameState)
{

    int roundNumber = giveMeTheRound(gameState);
    PlayerID player = whoAmI(gameState);

    // For random number generation
    srand(time(NULL));
    
#ifdef DEBUG
    printf("\tDEBUG: roundNumber %d\n"
           "\t       player %d\n",roundNumber, player);
#endif
    
    
    // If the first round - go to predetermined location
    // based on player
    if (roundNumber == 0) {

#ifdef DEBUG
        printf("\tDEBUG: Case 1\n");
#endif

        switch (player) {
            case PLAYER_DR_SEWARD:
                registerBestPlay("GE","I'm on holiday in Geneva");
                break;
            case PLAYER_MINA_HARKER:
                registerBestPlay("CA","I'm on holiday in Geneva");
                break;
            case PLAYER_VAN_HELSING:
                registerBestPlay("ZU","I'm on holiday in Geneva");
                break;
            case PLAYER_LORD_GODALMING:
                registerBestPlay("ED","I'm on holiday in Geneva");
                break;
            default:
                break;
        }
    } else if (roundNumber % 6 == 0) {

#ifdef DEBUG
        printf("\tDEBUG: Case 2\n");
#endif

        // If at a round which is a muliple of six,
        // rest to gain information
        LocationID currentLocation = whereIs(gameState, player);

#ifdef DEBUG
        printf("\tDEBUG: Current Location at %s\n", idToName(currentLocation));
#endif

        registerBestPlay(idToAbbrev(currentLocation),"Resting");
    } else {

#ifdef DEBUG
        printf("\tDEBUG: Case 3\n");
#endif
        
        // Move to a random allowed location
        // Bacically a STUB
        
        LocationID *possibleLocations;
        int numPossibleLocations;
        
        possibleLocations = whereCanIgo(gameState, &numPossibleLocations, TRUE, TRUE, TRUE);
        
        int randomPosition = rand()%numPossibleLocations;
        
        if (randomPosition == 0) {
            randomPosition++;
        } else if (randomPosition >= numPossibleLocations) {
            randomPosition--;
        }
        
        LocationID locationToGo = possibleLocations[randomPosition];
        
        registerBestPlay(idToAbbrev(locationToGo) ,"I'm on holiday in Geneva");
    }
    
    
    
}

// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "DracView.h"

void decideDraculaMove(DracView gameState)
{
    int roundNumber = giveMeTheRound(gameState);
    
    // For random number generation
    srand(time(NULL));
    
    if (roundNumber == 0) {
        
#ifdef DEBUG
        printf("\tDEBUG: Case 1\n");
#endif
        
        // Go to predermined location
        registerBestPlay("CD","Mwuhahahaha");
        
    } else {
        
#ifdef DEBUG
        printf("\tDEBUG: Case 2\n");
#endif
        LocationID *possibleLocations;
        int numPossibleLocations;
        
        possibleLocations = whereCanIgo(gameState, &numPossibleLocations, TRUE, TRUE);
        
        int randomPosition = rand()%numPossibleLocations;
        
        if (randomPosition == 0) {
            randomPosition++;
        } else if (randomPosition >= numPossibleLocations) {
            randomPosition--;
        }
        
        LocationID locationToGo = possibleLocations[randomPosition];
        
        registerBestPlay(idToAbbrev(locationToGo) ,"DRACULA GOES TO ...");
        
    }

}

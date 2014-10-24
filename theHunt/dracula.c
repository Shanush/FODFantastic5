// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "DracView.h"

#define TRUE 1
#define FALSE 0

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
        registerBestPlay("CD","");
        
    } else {
        
#ifdef DEBUG
        printf("\tDEBUG: Case 2\n");
#endif
        LocationID *possibleLocations;
        int numPossibleLocations;
        
        possibleLocations = whereCanIgo(gameState, &numPossibleLocations, TRUE, TRUE);
        
        int foundLocation = 0;
        int index = 0;
        
        while (!foundLocation) {
            if (inTrail(possibleLocations[index], gameState)) {
                index++;
            } else {
                foundLocation = TRUE;
            }
        }
        
        /*int randomPosition = rand()%numPossibleLocations;
        
        if (randomPosition == 0) {
            randomPosition++;
        } else if (randomPosition >= numPossibleLocations) {
            randomPosition--;
        }
        
        LocationID locationToGo = possibleLocations[randomPosition];*/
        
        registerBestPlay(idToAbbrev(locationToGo) ,"");
        
    }

}


int inTrail(LocationID location, DracView gameState) {
    LocationID *trail;
    giveMeTheTrail(gameState, PLAYER_DRACULA, trail);
    
    for (int i = 0; i < TRAIL_SIZE; i++) {
        if (trail[i] == location) {
            return FALSE;
        }
    }
    
    return TRUE;
}
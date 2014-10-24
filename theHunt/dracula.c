// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "DracView.h"
#include "Places.h"

#define TRUE 1
#define FALSE 0

int inTrail(LocationID location, DracView gameState);

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
        
        LocationID locationToGo;
        
        int index = 0;
        
        int foundLocation = FALSE:
        
        while (index < numPossibleLocations && !foundLocation) {
            if (!inTrail(possibleLocations[index], gameState)) {
                locationToGo = possibleLocations[index];
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
    LocationID trail[TRAIL_SIZE] = {0};
    giveMeTheTrail(gameState, PLAYER_DRACULA, trail);
    
    int i;
    
    for (i = 0; i < TRAIL_SIZE; i++) {
        if (trail[i] == location) {
            return TRUE;
        }
    }
    
    return FALSE;
}
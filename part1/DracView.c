// DracView.c ... DracView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
#include "Places.h"
#include <string.h>
// #include "Map.h" ... if you decide to use the Map ADT

#define TURN_SIZE 8

struct dracView {
    GameView gV;
    int traps[NUM_MAP_LOCATIONS];
    int vampire[NUM_MAP_LOCATIONS];
};
     

// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
    int i; //increment counters
    
    DracView dracView = malloc(sizeof(struct dracView));
    dracView->gV = newGameView(pastPlays, messages);
    
    //Initalising traps
    for (i = 0; i < NUM_MAP_LOCATIONS; i++) {
        dracView->traps[i] = 0;
    }
    //Initalising vampires
    for (i = 0; i < NUM_MAP_LOCATIONS; i++) {
        dracView->vampire[i] = 0;
    }
    
    int turn = 0;
    
    while (turn < strlen(pastPlays)) {
        ////while loop condition used to be:
        //// pastPlays[turn] != 0 || (turn == 0 && pastPlays[turn] != 0)
        
        ////printf("turn = %d\n", turn);
        ////printf("pastPlays[turn] = %c\n", pastPlays[turn]);
        
        ////printf("while loop - pastPlay[%d]\n", turn);
        
        
        //locate the first action of the turn in the string
        int action = turn+3;
        
        char abbrev[3] = {pastPlays[turn+1], pastPlays[turn+2], '\0'};
        
        LocationID currentLocation = abbrevToID(abbrev);
        
        
        //update health points, locations of traps extra based on action
        if (pastPlays[turn] == 'D') {
           if (pastPlays[action] == 'T') {
               dracView->traps[currentLocation]++;
            }
            
            if (pastPlays[action+1] == 'V') {
                dracView->vampire[currentLocation]++;
            }
            
            if (pastPlays[action+2] == 'M') {
                dracView->traps[currentLocation]--;
            }
            
            // If vampire matured (not placed)
            if (pastPlays[action+4]== 'V') {  //<- is action+4 correct?
                dracView->vampire[currentLocation]--;
                
            }
        } else {
            while (action % TURN_SIZE != 0) {
                switch (pastPlays[action]) {
                    case  'T':
                        dracView->traps[currentLocation]--;
                        break;
                    case 'V':
                        dracView->vampire[currentLocation]--;
                        break;
                    default:
                        break;
                }
                action++;
            }
        }
        turn += TURN_SIZE;
    }

    
    return dracView;
}
     
     
// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
{

    disposeGameView(toBeDeleted->gV);
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView)
{
    return getRound(currentView->gV);
}

// Get the current score
int giveMeTheScore(DracView currentView)
{
    return getScore(currentView->gV);
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
    return getHealth(currentView->gV, player);
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return getLocation(currentView->gV, player);
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
                 LocationID *start, LocationID *end)
{
    LocationID *trailOfPlayer = NULL;
    getHistory(currentView->gV, player, trailOfPlayer);
    *start = trailOfPlayer[0];
    *end = trailOfPlayer[1];
    return;
}

// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                         int *numTraps, int *numVamps)
{
    *numTraps = currentView->traps[where];
    *numVamps = currentView->vampire[where];
    return;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    getHistory(currentView->gV, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
    return connectedLocations(currentView->gV, numLocations,
                              getLocation(currentView->gV, PLAYER_DRACULA),
                              PLAYER_DRACULA, getRound(currentView->gV), road, FALSE, sea);
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{

    return connectedLocations(currentView->gV, numLocations,
                              getLocation(currentView->gV, player),
                              player, getRound(currentView->gV), road, rail, sea);
}

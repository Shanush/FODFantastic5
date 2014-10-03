// DracView.c ... DracView ADT implementation

// Made by the group:
//  ╔═╗╔═╗╔╦╗╔═╗┌─┐┌┐┌┌┬┐┌─┐┌─┐┌┬┐┬┌─┐5
//  ╠╣ ║ ║ ║║╠╣ ├─┤│││ │ ├─┤└─┐ │ ││
//  ╚  ╚═╝═╩╝╚  ┴ ┴┘└┘ ┴ ┴ ┴└─┘ ┴ ┴└─┘
// *** Starring ***
//   +-+-+-+-+-+ +-+-+-+-+-+
//   |R|u|c|h|i| |G|u|p|t|a|
//   +-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
//   |S|a|n|j|a|y| |N|a|r|a|y|a|n|a|
//   +-+-+-+-+-+-+-+ +-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+-+-+
//   |S|h|a|n|u|s|h| |P|r|e|m|a| |T|h|a|s|a|r|a|t|h|a|n|
//   +-+-+-+-+-+-+-+ +-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+-+-+
//   |S|i|m|o|n| |V|a|n| |W|i|n|d|e|n|
//   +-+-+-+-+-+ +-+-+-+ +-+-+-+-+-+-+
//   |J|e|s|s|e| |Y|u|e|
//   +-+-+-+-+-+ +-+-+-+
// 72 character limit...................................................

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
#include "Places.h"

#define TURN_SIZE 8
#define ROUND_SIZE 40

struct dracView {
    GameView gV;
    int traps[NUM_MAP_LOCATIONS];
    int vampire[NUM_MAP_LOCATIONS];
    LocationID trueLocation;
};

// Helper function
LocationID findTrueLocation (char *pastPlays, int indexOfLocation);

// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
    //Increment counter
    int i;
    
    // Initalising dracView --------------------------------------------
    DracView dracView = malloc(sizeof(struct dracView));
    
    // Sets the gameView within dracView
    dracView->gV = newGameView(pastPlays, messages);
    
    // While DracView is mainly a wrapper - it also needs to know
    // where the traps and vampires are
    
    //Initalising traps
    for (i = 0; i < NUM_MAP_LOCATIONS; i++) {
        dracView->traps[i] = 0;
    }
    //Initalising vampires
    for (i = 0; i < NUM_MAP_LOCATIONS; i++) {
        dracView->vampire[i] = 0;
    }
    
    // Initalising finished --------------------------------------------
    
    // Setting up based on history -------------------------------------
    
    int turn = 0;
    
    while (turn < strlen(pastPlays)) {
        //locate the first action of the turn in the string
        int action = turn+3;
        
        LocationID currentLocation =
                                findTrueLocation(pastPlays, turn+1);
        
        //update health points, locations of traps etc based on action
        if (pastPlays[turn] == 'D') {
           if (pastPlays[action] == 'T') {
               dracView->traps[currentLocation]++;
            }
            
            if (pastPlays[action+1] == 'V') {
                dracView->vampire[currentLocation]++;
            }
            
            if (pastPlays[action+2] == 'M') {
                dracView->traps[findTrueLocation(pastPlays, (turn+1)-(ROUND_SIZE*6))]--;
            }
            
            // If vampire matured (not placed)
            if (pastPlays[action+2]== 'V') {
                dracView->vampire[findTrueLocation(pastPlays, (turn+1)-(ROUND_SIZE*6))]--;
            }
            dracView->trueLocation = currentLocation;
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


// Thanks to the nature of pastPlays history
// this function uses recursion (Y)
LocationID findTrueLocation (char *pastPlays, int indexOfLocation) {
    
    // Make abbrev string from pastPlays
    char abbrev[3] = {pastPlays[indexOfLocation],
                      pastPlays[indexOfLocation+1],
                      '\0'};
    
    if (strcmp(abbrev, "HI") == 0 ||
        strcmp(abbrev, "D1") == 0) {
        
        // Find the true location based on the last round
        return findTrueLocation(pastPlays, indexOfLocation-ROUND_SIZE);
        
    } else if (strcmp(abbrev, "D2") == 0) {
        
        // Find the true location based on the previous 2 rounds
        return findTrueLocation(pastPlays,
                                indexOfLocation-ROUND_SIZE*2);
        
    } else if (strcmp(abbrev, "D3") == 0) {
        
        // Find the true location based on the previous 3 rounds
        return findTrueLocation(pastPlays,
                                indexOfLocation-ROUND_SIZE*3);
        
    } else if (strcmp(abbrev, "D4") == 0) {
        
        // Find the true location based on the previous 4 rounds
        return findTrueLocation(pastPlays,
                                indexOfLocation-ROUND_SIZE*4);
        
    } else if (strcmp(abbrev, "D5") == 0) {
        
        // Find the true location based on the previous 5 rounds
        return findTrueLocation(pastPlays,
                                indexOfLocation-ROUND_SIZE*5);
        
    } else {
        
        // Get the id from Abbrev
        // If it wasn't one of the cases above - its a normal abbrev
        return abbrevToID(abbrev);
        
    }
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
                              currentView->trueLocation,
                              PLAYER_DRACULA, getRound(currentView->gV),
                              road, FALSE, sea);
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{

    return connectedLocations(currentView->gV, numLocations,
                              getLocation(currentView->gV, player),
                              player, getRound(currentView->gV),
                              road, rail, sea);
}

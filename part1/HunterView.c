// HunterView.c ... HunterView ADT implementation

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

// Since hunterview is exactly like gameview
// HunterView is just a wrapper

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"
     
struct hunterView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView gV;
};
     

// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    HunterView hunterView = malloc(sizeof(struct hunterView));
    hunterView->gV = newGameView(pastPlays, messages);
    return hunterView;
}
     
     
// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
{
    disposeGameView(toBeDeleted->gV);
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(HunterView currentView)
{
    return getRound(currentView->gV);
}

// Get the id of current player
PlayerID whoAmI(HunterView currentView)
{
    return getCurrentPlayer(currentView->gV);
}

// Get the current score
int giveMeTheScore(HunterView currentView)
{
    return getScore(currentView->gV);
}

// Get the current health points for a given player
int howHealthyIs(HunterView currentView, PlayerID player)
{
    return getHealth(currentView->gV, player);
}

// Get the current location id of a given player
LocationID whereIs(HunterView currentView, PlayerID player)
{
    return getLocation(currentView->gV, player);
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    getHistory(currentView->gV, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations, int road, int rail, int sea)
{
    return connectedLocations(currentView->gV, numLocations,
                              getLocation(currentView->gV, getCurrentPlayer(currentView->gV)),
                              getCurrentPlayer(currentView->gV), getRound(currentView->gV), road, FALSE, sea);
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    return connectedLocations(currentView->gV, numLocations,
                              getLocation(currentView->gV, player),
                              player, getRound(currentView->gV), road, rail, sea);
}

LocationID closestCityHunter(HunterView currentView, LocationID targetLocation,
                       LocationID *cities, int citiesSize) {
    
    return closestCityGame(currentView->gV, targetLocation, cities, citiesSize);
    
}

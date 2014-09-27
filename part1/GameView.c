// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
// #include "Map.h" ... if you decide to use the Map ADT

#pragma mark - structs

typedef struct player {
    PlayerID id;
    int health;
    int happyState;
    LocationID location;
    LocationID *trail;   //of size 6 array
} Player;

struct gameView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    Round roundNumber;
    PlayerID currentPlayer;
    int score;
    Player *players;
};

#pragma mark - new & dispose

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    
    //Initalising gameView
    GameView gameView = malloc(sizeof(struct gameView));
    gameView->roundNumber = 0;  //STUB
    gameView->currentPlayer = PLAYER_LORD_GODALMING; //STUB
    gameView->score = GAME_START_SCORE; // STUB
    gameView->players = calloc(NUM_PLAYERS, sizeof(struct player));
    
    //Initalising players array   STUB
    for (int i = 0; i < NUM_PLAYERS; i++) {
        gameView->players[i].id = i;
        gameView->players[i].health = 0;
        gameView->players[i].location = NOWHERE;
        gameView->players[i].trail = calloc(TRAIL_SIZE, sizeof(LocationID));
    }
    
    return gameView;
}
     
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    free( toBeDeleted->players );
    free( toBeDeleted );
}

//// Functions to return simple information about the current state of the game
#pragma mark - Current State Information

// Get the current round
Round getRound(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->roundNumber;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->currentPlayer;
}

// Get the current score
int getScore(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    //Random comment
    //Random
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->players[player].health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->players[player].location;
}


//// Functions that return information about the history of the game
#pragma mark - History Of Game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    for (int i = 0; i < TRAIL_SIZE; i++) {
        trail[i] = currentView->players[player].trail[i];
    }
}

//// Functions that query the map to find information about connectivity
#pragma mark - Connectivity information

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}

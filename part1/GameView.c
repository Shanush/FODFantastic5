// GameView.c ... GameView ADT implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
// #include "Map.h" ... if you decide to use the Map ADT

#define TURN_SIZE 8
#define TRUE 1
#define FALSE 0

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
    printf("Ad. Sea is %d\n",abbrevToID("AS"));
    printf("Athens is %d\n",abbrevToID("AT"));
    printf("Zagreb is %d\n",abbrevToID("ZA"));
    printf("Zurich is %d\n",abbrevToID("ZU"));
    
    //Initalising gameView
    GameView gameView = malloc(sizeof(struct gameView));
    gameView->roundNumber = 0;  //STUB
    gameView->currentPlayer = -1; //STUB
    gameView->score = GAME_START_SCORE; // STUB
    gameView->players = calloc(NUM_PLAYERS, sizeof(struct player));
    
    //Initalising players array   STUB
    for (int i = 0; i < NUM_PLAYERS; i++) {
        gameView->players[i].id = i;
        gameView->players[i].health =  (i != 4) ? GAME_START_HUNTER_LIFE_POINTS : GAME_START_BLOOD_POINTS;
        gameView->players[i].location = NOWHERE;
        gameView->players[i].trail = calloc(TRAIL_SIZE, sizeof(LocationID));
    }
    
    int turn = 0;
    while (pastPlays[turn] != 0 || (turn == 0 && pastPlays[turn] != 0)) {
        //printf("turn = %d\n", turn);
        //printf("pastPlays[turn] = %c\n", pastPlays[turn]);
        
        printf("while loop - pastPlay[%d]\n", turn);
        switch (pastPlays[turn]) {
            case 'G':
                gameView->currentPlayer = PLAYER_LORD_GODALMING;
                break;
            case 'S':
                gameView->currentPlayer = PLAYER_DR_SEWARD;
                break;
            case 'H':
                gameView->currentPlayer = PLAYER_VAN_HELSING;
                break;
            case 'M':
                gameView->currentPlayer = PLAYER_MINA_HARKER;
                break;
            case 'D':
                gameView->currentPlayer = PLAYER_DRACULA;
                break;
            default:
                break;
            
        }
        
        char currentAbbrevLocation[3] = {pastPlays[turn+1], pastPlays[turn+2], '\0'};
        printf("currentAbbrevLocaiton is %s, %d\n", currentAbbrevLocation, abbrevToID(currentAbbrevLocation));
        gameView->players[gameView->currentPlayer].location = abbrevToID(currentAbbrevLocation);
        
        
        int action = turn+3;
        
        while (action % TURN_SIZE != 0) {
            
            if (gameView->currentPlayer != PLAYER_DRACULA) {
                
                switch (pastPlays[action]) {
                    case  'T':
                        gameView->players[gameView->currentPlayer].health -= LIFE_LOSS_TRAP_ENCOUNTER;
                        //Remove trap from city
                        break;
                    case 'V':
                        //Vampire removed from city
                        break;
                    case 'D':
                        gameView->players[gameView->currentPlayer].health -= LIFE_LOSS_DRACULA_ENCOUNTER;
                        gameView->players[PLAYER_DRACULA].health -= LIFE_LOSS_HUNTER_ENCOUNTER;
                        break;
                    default:
                        break;
                }
                
            } else {
                //Something for dracula's actions
            }
            action++;
        }
        
        
        
        //printf("turn is %d\n", turn);
        turn += TURN_SIZE;
        gameView->roundNumber++;
    }
    
    gameView->currentPlayer = (gameView->currentPlayer == 4) ? PLAYER_LORD_GODALMING : gameView->currentPlayer + 1;
    printf("round number is %d\n", gameView->roundNumber);
    gameView->roundNumber /= 5;
    
    printf("round number is %d\n", gameView->roundNumber);
    
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
    //printf("Location of %d is %d\n", player ,currentView->players[player].location);
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

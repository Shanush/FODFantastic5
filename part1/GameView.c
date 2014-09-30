// GameView.c ... GameView ADT implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h" //... if you decide to use the Map ADT

#define TURN_SIZE 8
#define TRUE 1
#define FALSE 0

//Structs

typedef struct player {
    PlayerID id;
    int health;
    int happyState;
    LocationID location;
    LocationID *trail;   //of size 6 array
} player;

struct gameView {
    Map europe;
    Round roundNumber;
    PlayerID currentPlayer;
    int score;
    player *players;
};

//Declaration of helper functions
LocationID abbrevToLocationID(char *abbrev);
void updateLocationOfPlayer(char *abbrev, player *currentPlayer);
//new & dispose

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    ////printf("Ad. Sea is %d\n",abbrevToID("AS"));
    ////printf("Athens is %d\n",abbrevToID("AT"));
    ////printf("Zagreb is %d\n",abbrevToID("ZA"));
    ////printf("Zurich is %d\n",abbrevToID("ZU"));
    
    int i,j; //Increment counters
    
    //Initalising gameView
    GameView gameView = malloc(sizeof(struct gameView));
    gameView->roundNumber = 0;  //STUB
    gameView->currentPlayer = -1; //STUB
    gameView->score = GAME_START_SCORE; // STUB
    gameView->players = calloc(NUM_PLAYERS, sizeof(struct player));
    
    //Initialising the map
    gameView->europe = newMap();

    //Initalising players array   STUB
    for (i = 0; i < NUM_PLAYERS; i++) {
        gameView->players[i].id = i;
        gameView->players[i].health =  (i != 4) ? GAME_START_HUNTER_LIFE_POINTS : GAME_START_BLOOD_POINTS;
        gameView->players[i].location = UNKNOWN_LOCATION;
        gameView->players[i].trail = malloc(TRAIL_SIZE * sizeof(LocationID));
        for (j = 0; j < TRAIL_SIZE; j++) {
            gameView->players[i].trail[j] = UNKNOWN_LOCATION;
        }
    }
    
    
    int turn = 0;
    while (turn < strlen(pastPlays)) {
        ////while loop condition used to be:
        //// pastPlays[turn] != 0 || (turn == 0 && pastPlays[turn] != 0)
        
        ////printf("turn = %d\n", turn);
        ////printf("pastPlays[turn] = %c\n", pastPlays[turn]);
        
        ////printf("while loop - pastPlay[%d]\n", turn);
        
        //Set currentPlayer of turn
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
                gameView->score--; //"score decreases by 1 every time dracula finishes a turn"
                break;
            default:
                break;
            
        }
        
        player *currentPlayer = &gameView->players[gameView->currentPlayer];
        
        //Set location for this currentPlayer.
        updateLocationOfPlayer(&pastPlays[turn+1], currentPlayer);
        
        //add new location
        currentPlayer->trail[0] = currentPlayer->location;
        
        
        //locate the first action of the turn in the string
        int action = turn+3;
        
        //update health points, locations of traps extra based on action
        if (getCurrentPlayer(gameView) != PLAYER_DRACULA) {
            while (action % TURN_SIZE != 0) {
                switch (pastPlays[action]) {
                    case  'T':
                        currentPlayer->health -= LIFE_LOSS_TRAP_ENCOUNTER;
                        //Remove trap from city
                        break;
                    /*case 'V':
                        //Vampire removed from city
                        break;*/
                    case 'D':
                        currentPlayer->health -= LIFE_LOSS_DRACULA_ENCOUNTER;
                        gameView->players[PLAYER_DRACULA].health -= LIFE_LOSS_HUNTER_ENCOUNTER;
                        break;
                    default:
                        break;
                }
            }
            action++;
        } else {
            // If vampire matured (not placed)
            if (pastPlays[action+4]== 'V') {
                gameView->score -= 13;
            }
        }
        
        
        //updating score based on location
        //Hunter in hospital - to full life points
        if (currentPlayer->id != PLAYER_DRACULA) {
            if (currentPlayer->health <= 0) {
                updateLocationOfPlayer("JM", currentPlayer);
                currentPlayer->health = GAME_START_HUNTER_LIFE_POINTS;
                gameView->score -= 6;
            }
        }
        
        
        //Dracula at sea - loses 2 life points
        if (currentPlayer->id == PLAYER_DRACULA &&
            currentPlayer->location == SEA_UNKNOWN) {
            currentPlayer->health -= LIFE_LOSS_SEA;
        }
        
        //Hunter if rest
        if (currentPlayer->id != PLAYER_DRACULA &&
            currentPlayer->trail[0] == currentPlayer->trail[1]) {
            currentPlayer->health += LIFE_GAIN_REST;
        }
        
        //update turn + roundNumber
        ////printf("turn is %d\n", turn);
        turn += TURN_SIZE;
        gameView->roundNumber++;
    }
    
    //Set the currentPlayer to the next person after last player.
    gameView->currentPlayer = (gameView->currentPlayer+1)%5; //increment currentPlayer to the next player.

    ////gameView->currentPlayer = (gameView->currentPlayer == 4) ? PLAYER_LORD_GODALMING : gameView->currentPlayer + 1;
    
    ////printf("round number is %d\n", gameView->roundNumber);
    
    //RoundNumber was actually counting turn number
    //so roundNumber is modified to have the actual round number
    gameView->roundNumber = (gameView->roundNumber + 1) / 5;
    
    ////printf("round number is %d\n", gameView->roundNumber);
    
    //GameView is now ready to be used!
    return gameView;
}
     
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    free( toBeDeleted->players );
    free( toBeDeleted );
}

//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    return currentView->roundNumber;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    return currentView->currentPlayer;
}

// Get the current score
int getScore(GameView currentView)
{
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    return currentView->players[player].health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    return currentView->players[player].location;
}


//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    int i = 0;
    for (i = 0; i < TRAIL_SIZE; i++) {
        trail[i] = currentView->players[player].trail[i];
    }
//    printf("\ttrail[0] = %d\n", trail[0]);
//    printf("\ttrail[1] = %d\n", trail[1]);
//    printf("\ttrail[2] = %d\n", trail[2]);
//    printf("\ttrail[3] = %d\n", trail[3]);
//    printf("\ttrail[4] = %d\n", trail[4]);
//    printf("\ttrail[5] = %d\n", trail[5]);
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    // use map in gameview
    
    // pass it onto Map.c
    return connLocs(currentView->europe, numLocations,
                               from, player, round,
                               road, rail, sea);
}


//Helper Functions
LocationID abbrevToLocationID(char *abbrev) {
    if (!strcmp(abbrev,"C?")) {
        return CITY_UNKNOWN;
    } else if (!strcmp(abbrev,"S?")) {
        return SEA_UNKNOWN;
    } else if (!strcmp(abbrev,"HI")) {
        return HIDE;
    } else if (!strcmp(abbrev,"D1")) {
        return DOUBLE_BACK_1;
    } else if (!strcmp(abbrev,"D2")) {
        return DOUBLE_BACK_2;
    } else if (!strcmp(abbrev,"D3")) {
        return DOUBLE_BACK_3;
    } else if (!strcmp(abbrev,"D4")) {
        return DOUBLE_BACK_4;
    } else if (!strcmp(abbrev,"D5")) {
        return DOUBLE_BACK_5;
    } else if (!strcmp(abbrev,"TP")) {
        return TELEPORT;
    } else {
        return abbrevToID(abbrev);
    }
}

void updateLocationOfPlayer(char *abbrev, player *currentPlayer) {
    char currentAbbrevLocation[3] = {abbrev[0], abbrev[1], '\0'};
    //printf("currentAbbrevLocaiton is %s, %d\n", currentAbbrevLocation, abbrevToLocationID(currentAbbrevLocation));
    currentPlayer->location = abbrevToLocationID(currentAbbrevLocation);
    
    //Update trail for currentPlayer
    //Shuffle current trail
    int i;
    for (i = TRAIL_SIZE-1; i >= 1; i--) {
        currentPlayer->trail[i] = currentPlayer->trail[i-1];
    }
}
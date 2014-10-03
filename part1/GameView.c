// GameView.c ... GameView ADT implementation
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
#include "Map.h" //... if you decide to use the Map ADT

#define TURN_SIZE 8
#define TRUE 1
#define FALSE 0
#define NUM_TURNS 5

////Structs

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

////Declaration of helper functions
LocationID abbrevToLocationID(char *abbrev);
void updateLocationOfPlayer(char *abbrev, player *currentPlayer);
void reduceHealthIfAtSea (player *currentPlayer);

////new & dispose

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    
    int i,j; // Increment counters
    
    // Initalising gameView --------------------------------------------
    GameView gameView = malloc(sizeof(struct gameView));
    gameView->roundNumber = -1;
    gameView->currentPlayer = -1;
    gameView->score = GAME_START_SCORE;
    gameView->players = calloc(NUM_PLAYERS, sizeof(struct player));
    
    // Initalising players array
    for (i = 0; i < NUM_PLAYERS; i++) {
        gameView->players[i].id = i;
        
        //initalise health based on hunter or dracula
        gameView->players[i].health =  (i != PLAYER_DRACULA)
                                        ? GAME_START_HUNTER_LIFE_POINTS
                                        : GAME_START_BLOOD_POINTS;
        
        gameView->players[i].location = UNKNOWN_LOCATION;
        
        //Initalise trail with unknown location
        gameView->players[i].trail = malloc(TRAIL_SIZE * sizeof(LocationID));
        for (j = 0; j < TRAIL_SIZE; j++) {
            gameView->players[i].trail[j] = UNKNOWN_LOCATION;
        }
    }
    
    // Initialising the map
    gameView->europe = newMap();

    // Finished initalising --------------------------------------------
    
    
    // Updating game based on history of each turn ---------------------
    
    // The while loop parses through each turn, but jumping to the
    // index of the pastPlays string of which the turn starts.
    // This is kept by the turnIndex integer variable.
    
    int turnIndex = 0;
    while (turnIndex < strlen(pastPlays)) {
        
        // Set currentPlayer of turn
        switch (pastPlays[turnIndex]) {
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
                
                // "score decreases by 1 every time dracula finishes
                // a turn"
                gameView->score--;
                break;
                
            default: break;
        }
        
        // Keep a local pointer to currentPlayer
        player *currentPlayer =
                            &gameView->players[gameView->currentPlayer];
        
        // if the player is on zero health - they would have already
        // been to hospital, and so we increase their life points
        // to full
        if(currentPlayer->id != PLAYER_DRACULA &&
           currentPlayer->health == 0) {
            currentPlayer->health = GAME_START_HUNTER_LIFE_POINTS;
        }
        
        
        // Set location for this currentPlayer.
        updateLocationOfPlayer(&pastPlays[turnIndex+1], currentPlayer);
        
        
        // locate the first action of the turn in the string
        int actionIndex = turnIndex+3;
        
        // update health points, score etc -----------------------------
        // based on action ---------------------------------------------
        
        if (getCurrentPlayer(gameView) != PLAYER_DRACULA) {
            // if currentPlayer is hunter then:
            
            // for each action of the turn
            while (actionIndex % TURN_SIZE != 0) {
                switch (pastPlays[actionIndex]) {
                    case  'T':
                        // A trap was encountered - reduce health
                        currentPlayer->health -=
                                            LIFE_LOSS_TRAP_ENCOUNTER;
                        break;
                        
                    case 'D':
                        // Dracula was encountered - reduce health
                        currentPlayer->health -=
                                            LIFE_LOSS_DRACULA_ENCOUNTER;
                        
                        // Dracula also loses health
                        gameView->players[PLAYER_DRACULA].health -=
                                            LIFE_LOSS_HUNTER_ENCOUNTER;
                        break;
                        
                    default: break;
                }
                
                actionIndex++;
            }
            
            
            // ---- updating score based on location ------
            
            // Hunter goes in hospital - will gain full life points
            // in next round
            if (currentPlayer->health <= 0) {
                
                updateLocationOfPlayer("JM", currentPlayer);
                currentPlayer->health = 0;
                
                gameView->score -= SCORE_LOSS_HUNTER_HOSPITAL;
                
            }
            
            //Hunter if rest
            if (currentPlayer->trail[0] == currentPlayer->trail[1] &&
                currentPlayer->health != 0) {
                
                currentPlayer->health += LIFE_GAIN_REST;
            
            }
            
            // ---- finished updating score based on location ----
            
            // If the health is more than limit, due to over achievement
            // reduce the score to limit
            if (currentPlayer->health > GAME_START_HUNTER_LIFE_POINTS) {
                currentPlayer->health = GAME_START_HUNTER_LIFE_POINTS;
            }

           
        } else {
            
            // If vampire matured (not placed)
            if (pastPlays[actionIndex+2] == 'V') {
                gameView->score -= SCORE_LOSS_VAMPIRE_MATURES;
            }
            
            //Dracula at sea... drop health
            reduceHealthIfAtSea(currentPlayer);
            
            // If at Castle Dracula at end of turn
            if (currentPlayer->location == CASTLE_DRACULA) {
                currentPlayer->health += LIFE_GAIN_CASTLE_DRACULA;
            }
        }
        

        // Updating score & health end ---------------------------------
        

        //update turn + roundNumber
        turnIndex += TURN_SIZE;
        gameView->roundNumber++;
    }
    
    //Set the currentPlayer to the next person after last player.
    gameView->currentPlayer = (gameView->currentPlayer+1)%NUM_PLAYERS;
    
    
    //RoundNumber was actually counting turn number
    //so roundNumber is modified to have the actual round number
    gameView->roundNumber = (gameView->roundNumber + 1) / NUM_TURNS;
    
    
    //GameView is now ready to be used!
    return gameView;
}
     
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    disposeMap( toBeDeleted->europe );
    free( toBeDeleted->players->trail );
    free( toBeDeleted->players );
    free( toBeDeleted );
}

//// Functions to return simple information about the current state of
//// the game


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


//// Helper Functions

// In house abbrev to Id convertor
// Takes care of city and sea unknown
// As well as hide and double backs
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

// Updated the location and trail based on abbrevated location
void updateLocationOfPlayer(char *abbrev, player *currentPlayer) {
    char currentAbbrevLocation[3] = {abbrev[0], abbrev[1], '\0'};
    currentPlayer->location = abbrevToLocationID(currentAbbrevLocation);
    
    //Update trail for currentPlayer
    //Shuffle current trail
    int i;
    for (i = TRAIL_SIZE-1; i >= 1; i--) {
        currentPlayer->trail[i] = currentPlayer->trail[i-1];
    }
    
    // add new location
    currentPlayer->trail[0] = currentPlayer->location;
}

// reduces heath for dracula if discoved to be at sea
void reduceHealthIfAtSea (player *currentPlayer) {
    //boolean to determine if we should deduct HP
    int dropHealth = FALSE;
    
    //doubleBack, number used if a doubleback is present
    int dB = 0;
    
    //if he is in an unknown sea (hunter view)
    if (currentPlayer->trail[0] == SEA_UNKNOWN) {
        dropHealth = TRUE;
    } else {
        switch (currentPlayer->trail[0]) {
            //Set dB to correponding doubleBack number
            case DOUBLE_BACK_1: dB = 1; break;
            case DOUBLE_BACK_2: dB = 2; break;
            case DOUBLE_BACK_3: dB = 3; break;
            case DOUBLE_BACK_4: dB = 4; break;
            case DOUBLE_BACK_5: dB = 5; break;
            default: break;
        }
        if (currentPlayer->trail[dB] == HIDE) {
            //if the item at that trail was a hide, then
            //the correct location was the location before
            dB++;
        }
        if (dB > 0) {
            //If the location was at sea - then drop the health
            if (currentPlayer->trail[dB] == SEA_UNKNOWN) {
                dropHealth = TRUE;
            } else if (idToType (currentPlayer->trail[dB]) == SEA) {
                dropHealth = TRUE;
            }
        } else if (currentPlayer->trail[0] >= MIN_MAP_LOCATION &&
                   currentPlayer->trail[0] <= MAX_MAP_LOCATION &&
                   idToType (currentPlayer->trail[0]) == SEA) {
            //the most recently visited location is a sea...
            dropHealth = TRUE;
        }
    }
    
    if (dropHealth) {
        currentPlayer->health -= LIFE_LOSS_SEA;
    }
}
/**
 * Runs a player's game turn ...
 *
 * Can produce either a Hunter player or a Dracula player
 * depending on the setting of the I_AM_DRACULA #define
 *
 * This is a dummy version of the real player.c used when
 * you submit your AIs. It is provided so that you can
 * test whether your code is likely to compile ...
 *
 * Note that it used to drive both Hunter and Dracula AIs.
 * It first creates an appropriate view, and then invokes the
 * relevant decide-my-move function, which should use the 
 * registerBestPlay() function to send the move back.
 *
 * The real player.c applies a timeout, so that it will halt
 * decide-my-move after a fixed amount of time, if it doesn't
 * finish first. The last move registered will be the one
 * used by the game engine. This version of player.c won't stop
 * your decide-my-move function if it goes into an infinite
 * loop. Sort that out before you submit.
 *
 * Based on the program by David Collien, written in 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"

#define I_AM_DRACULA 1

#ifdef I_AM_DRACULA
#include "DracView.h"
#include "dracula.h"
#else
#include "HunterView.h"
#include "hunter.h"
#endif

// moves given by registerBestPlay are this long (including terminator)
#define MOVE_SIZE 3

// The minimum static globals I can get away with
static char latestPlay[MOVE_SIZE] = "";
static char latestMessage[MESSAGE_SIZE] = "";

int main(int argc, char *argv[])
{
#ifdef I_AM_DRACULA
   DracView gameState;
   char *plays = "GZA.... SED.... HZU.... MZU....";
   PlayerMessage msgs[3] = { "", "", "" };
   gameState = newDracView(plays,msgs);
   decideDraculaMove(gameState);
   disposeDracView(gameState);
    
    plays = "GZA.... SED.... HZU.... MZU.... DCA.... "
            "GZA.... SED.... HZU.... MZU.... DCA.... "
            "GZA.... SED.... HZU.... MZU.... DCA.... "
            "GZA.... SED.... HZU.... MZU.... DCA.... "
            "GZA.... SED.... HZU.... MZU....";
    gameState = newDracView(plays,msgs);
    decideDraculaMove(gameState);
    disposeDracView(gameState);
    
    
    plays = "GLO.... STO.... HMU.... MSO....";
    gameState = newDracView(plays,msgs);
    decideDraculaMove(gameState);
    disposeDracView(gameState);
    
    plays = "GLO.... STO.... HMU.... MSO.... DCD.V.. GLO.... STO.... HMU.... MSO....";
    gameState = newDracView(plays,msgs);
    decideDraculaMove(gameState);
    disposeDracView(gameState);
    
    
#else
    
    // Testing new game
    printf("Testing new game\n");
    
    printf("First Lord Godalming: \n");
    HunterView gameState;
    char *plays = "";
    PlayerMessage msgs[3] = { "", "", "" };
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    printf("Dr. Seward: \n");
    plays = "GZA....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    printf("Van Helsing: \n");
    plays = "GZA.... SED....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    printf("Mina Harker: \n");
    plays = "GZA.... SED.... HZU....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    
    // Testing a round divisible by six
    printf("\nTesting out a round divisible by six\n");
    printf("First Lord Godalming: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... ";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    printf("Dr. Seward: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    
    printf("Van Helsing: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    printf("Mina Harker: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU.... MCA.... DC?.... "
            "GZA.... SED.... HZU....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    // Testing a round otherwise
    
    printf("\nTesting a round otherwise\n");
    
    printf("First Lord Godalming: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    printf("Dr. Seward: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    
    printf("Van Helsing: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    printf("Mina Harker: \n");
    plays = "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU.... MCA.... DC?.... "
    "GZA.... SED.... HZU....";
    gameState = newHunterView(plays,msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    
    
    
    printf("Testing problem with segfault ------\n------\n------\n------\n");
    plays = "GED.... SGE.... HZU.... MCA.... DCD.V.. GNS.... SMR.... HMR.... MMA.... DC?T... GAO.... SMR.... HMR.... MLS.... DC?T... GAO.... SMR.... HMR.... MSN.... DC?T... GAO.... SMR.... HMR.... MSR.... DD1T... GAO....";
    gameState = newHunterView(plays, msgs);
    decideHunterMove(gameState);
    disposeHunterView(gameState);
    
    
    
    
#endif
   printf("Move: %s, Message: %s\n", latestPlay, latestMessage);
   return EXIT_SUCCESS;
}

// Saves characters from play (and appends a terminator)
// and saves characters from message (and appends a terminator)
void registerBestPlay (char *play, PlayerMessage message) {
   strncpy(latestPlay, play, MOVE_SIZE-1);
   latestPlay[MOVE_SIZE-1] = '\0';
    
    printf("\tLocation: %s\n",idToName(abbrevToID(latestPlay)));
    
   strncpy(latestMessage, message, MESSAGE_SIZE);
   latestMessage[MESSAGE_SIZE-1] = '\0';
}

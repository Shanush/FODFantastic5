// testDracView.c ... test the DracView ADT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "DracView.h"

int main()
{
    int i;
    DracView dv;


    printf("Test for basic functions, just before Dracula's first move\n");
    PlayerMessage messages1[] = {"Hello","Rubbish","Stuff",""};
    dv = newDracView("GST.... SAO.... HZU.... MBB....", messages1);
    assert(giveMeTheRound(dv) == 0);
    assert(whereIs(dv,PLAYER_LORD_GODALMING) == STRASBOURG);
    assert(whereIs(dv,PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
    assert(whereIs(dv,PLAYER_VAN_HELSING) == ZURICH);
    assert(whereIs(dv,PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
    assert(whereIs(dv,PLAYER_DRACULA) == UNKNOWN_LOCATION);
    assert(howHealthyIs(dv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    printf("passed\n");
    disposeDracView(dv);

    printf("Test for encountering Dracula and hunter history\n");
    PlayerMessage messages2[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!","","",""};
    dv = newDracView("GST.... SAO.... HCD.... MAO.... DGE.... "
                     "GGED... SAO.... HCD.... MAO....", messages2);
    assert(giveMeTheRound(dv) == 1);
    assert(whereIs(dv,PLAYER_DRACULA) == GENEVA);
    assert(howHealthyIs(dv,PLAYER_LORD_GODALMING) == 5);
    assert(howHealthyIs(dv,PLAYER_DRACULA) == 30);
    assert(whereIs(dv,PLAYER_LORD_GODALMING) == GENEVA);
    LocationID history[TRAIL_SIZE];
    giveMeTheTrail(dv,PLAYER_DRACULA,history);
    assert(history[0] == GENEVA);
    assert(history[2] == UNKNOWN_LOCATION);
    giveMeTheTrail(dv,PLAYER_LORD_GODALMING,history);
    assert(history[0] == GENEVA);
    assert(history[1] == STRASBOURG);
    assert(history[2] == UNKNOWN_LOCATION);
    giveMeTheTrail(dv,PLAYER_DR_SEWARD,history);
    assert(history[0] == ATLANTIC_OCEAN);
    assert(history[1] == ATLANTIC_OCEAN);
    assert(history[2] == UNKNOWN_LOCATION);
    printf("passed\n");        
    disposeDracView(dv);

    printf("Test for Dracula leaving minions\n");
    PlayerMessage messages3[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!","","","","Drop a V","Party in Strasbourg","Party","Party","Party"};
    dv = newDracView("GGE.... SGE.... HGE.... MGE.... DED.V.. "
                     "GST.... SST.... HST.... MST.... DMNT... "
                     "GST.... SST.... HST.... MST....", messages3);
    int nT, nV;
    whatsThere(dv,EDINBURGH,&nT,&nV);
    assert(nT == 0 && nV == 1);
    whatsThere(dv,MANCHESTER,&nT,&nV);
    assert(nT == 1 && nV == 0);
    assert(whereIs(dv,PLAYER_DRACULA) == MANCHESTER);
    giveMeTheTrail(dv,PLAYER_DRACULA,history);
    assert(history[0] == MANCHESTER);
    assert(history[1] == EDINBURGH);
    assert(history[2] == UNKNOWN_LOCATION);
    giveMeTheTrail(dv,PLAYER_MINA_HARKER,history);
    assert(history[0] == STRASBOURG);
    assert(history[1] == STRASBOURG);
    assert(history[2] == GENEVA);
    assert(history[3] == UNKNOWN_LOCATION);
    printf("passed\n");
    disposeDracView(dv);
    // needs further work - double back 2 not working
    /*dv = newDracView("GGE.... SGE.... HGE.... MGE.... DED.V.. "
                     "GST.... SST.... HST.... MST.... DHIT... "
                     "GST.... SST.... HST.... MST.... DMNT... "
                     "GST.... SST.... HST.... MST.... DD2T...", messages3);*/
    dv = newDracView("GGE.... SGE.... HGE.... MGE.... DED.V.. "
                     "GST.... SST.... HST.... MST.... DHIT... "
                     "GST.... SST.... HST.... MST.... DMNT... "
                     "GST.... SST.... HST.... MST.... DD1T...", messages3);
    whatsThere(dv,EDINBURGH,&nT,&nV);
    assert(nV == 1);
    whatsThere(dv, MANCHESTER, &nT, &nV);
    assert(nT == 2 && nV == 0);
    whatsThere(dv,EDINBURGH,&nT,&nV);
    assert(nT == 1 && nV == 1);
    dv = newDracView("GGE.... SGE.... HGE.... MGE.... DED.V.. "
                     "GST.... SST.... HST.... MST.... DHIT... "
                     "GST.... SST.... HST.... MST.... DMNT... "
                     "GST.... SST.... HST.... MST.... DD3T...", messages3);
    whatsThere(dv,EDINBURGH,&nT,&nV);
    assert(nV == 1);
    whatsThere(dv, MANCHESTER, &nT, &nV);
    assert(nT == 1 && nV == 0);
    whatsThere(dv,EDINBURGH,&nT,&nV);
    assert(nT == 2 && nV == 1);
    printf("Our test right here\n");
    dv = newDracView("GGE.... SGE.... HGE.... MGE.... DED.V.. "
                     "GST.... SST.... HST.... MST.... DHIT... "
                     "GST.... SST.... HST.... MST.... DMNT... "
                     "GGE.... SGE.... HGE.... MGE.... DLVT... "
                     "GST.... SST.... HST.... MST.... DD3T...", messages3);
    printf("called the funciton\n");
    whatsThere(dv,EDINBURGH,&nT,&nV);
    assert(nV == 1);
    printf("up to first ed\n");
    whatsThere(dv, MANCHESTER, &nT, &nV);
    assert(nT == 1 && nV == 0);
    whatsThere(dv, LIVERPOOL, &nT, &nV);
    assert(nT == 1 && nV == 0);
    whatsThere(dv,EDINBURGH,&nT,&nV);
    assert(nT == 2 && nV == 1);
    printf("passed our tests\n");
    
    //-------------------------
    
    printf("Test for connections\n");
    int size, seen[NUM_MAP_LOCATIONS], *edges;

    printf("Checking Galatz road connections\n");
    PlayerMessage messages5[] = {"Gone to Galatz"};
    dv = newDracView("GGA....", messages5);
    edges = whereCanTheyGo(dv,&size,PLAYER_LORD_GODALMING,1,0,0);
    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
    for (i = 0; i< size ; i++) seen[edges[i]] = 1;
    assert(size == 5); assert(seen[GALATZ]); assert(seen[CONSTANTA]);
    assert(seen[BUCHAREST]); assert(seen[KLAUSENBURG]); assert(seen[CASTLE_DRACULA]);
    free(edges);
    disposeDracView(dv);

    printf("Checking Ionian Sea sea connections\n");
    PlayerMessage messages6[] = {"Sailing the Ionian"};
    dv = newDracView("GIO....", messages6);
    edges = whereCanTheyGo(dv,&size,PLAYER_LORD_GODALMING,0,0,1);
    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
    for (i = 0; i < size; i++) seen[edges[i]] = 1;
    assert(size == 7); assert(seen[IONIAN_SEA]); assert(seen[BLACK_SEA]);
    assert(seen[ADRIATIC_SEA]); assert(seen[TYRRHENIAN_SEA]);
    assert(seen[ATHENS]); assert(seen[VALONA]); assert(seen[SALONICA]);
    free(edges);
    disposeDracView(dv);

    printf("Checking Athens rail connections (none)\n");
    PlayerMessage messages7[] = {"Leaving Athens by train"};
    dv = newDracView("GAT....", messages7);
    edges = whereCanTheyGo(dv,&size,PLAYER_LORD_GODALMING,0,1,0);
    assert(size == 1);
    assert(edges[0] == ATHENS);
    free(edges);
    disposeDracView(dv);

    printf("passed\n");

    // Test whatsThere ()
    printf("Test whatsThere ()\n");
    PlayerMessage messages685[] = {"Hello","Rubbish","Stuff",""};
    dv = newDracView("GST.... SAO.... HZU.... MBB....", messages685);
    assert(giveMeTheRound(dv) == 0);
    assert(whereIs(dv,PLAYER_LORD_GODALMING) == STRASBOURG);
    assert(whereIs(dv,PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
    assert(whereIs(dv,PLAYER_VAN_HELSING) == ZURICH);
    assert(whereIs(dv,PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
    assert(whereIs(dv,PLAYER_DRACULA) == UNKNOWN_LOCATION);
    assert(howHealthyIs(dv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    printf("passed\n");
    disposeDracView(dv);

    // EXTRA TEST 1
    printf("extra test 1\n");
    PlayerMessage messages9[] = {"Hello","Rubbish","Stuff",""};
    dv = newDracView("GVI.... SZU.... HBB.... MSO...." messages9);
    assert(whereIs(dv, PLAYER_LORD_GODALMING) == VIENNA);
    assert(whereIs(dv, PLAYER_DR_SEWARD) == ZURICH);
    assert(whereIs(dv, PLAYER_VAN_HELSING) == BAY_OF_BISCAY);
    assert(whereIs(dv, PLAYER_MINA_HARKER) == SOFIA);
    assert(whereIs(dv, PLAYER_DRACULA) == UNKNOWN_LOCATION);
    assert(howHealthyIs(dv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    disposeDracView(dv);
    printf("passed extra1!\n");

    // EXTRA TEST 2 - test putting traps twice
    printf("extra test 2\n");
    PlayerMessage messages10[] = {"Drop","party","at","Varrock"};
    dv = newDracView("GHA.... SMA.... HVR.... MBI.... DSZ.V.. "
                     "GCO.... SSR.... HSO.... MNP.... DZAT... "
                     "GFR.... STO.... HBE.... MRO.... DVIT...", messages3);
    assert(GiveMeTheRound(dv) == 3);
    assert((giveMeTheScore(dv)) == (GAME_START_SCORE - (SCORE_LOSS_DRACULA_TURN*GiveMeTheRound(dv))));
    
    assert(whereIs(dv, PLAYER_LORD_GODALMING) == FRANKFURT);
    assert(whereIs(dv, PLAYER_DR_SEWARD) == TOULOUSE);
    assert(whereIs(dv, PLAYER_VAN_HELSING) == BELGRADE);
    assert(whereIs(dv, PLAYER_MINA_HARKER) == ROME);
    assert(whereIs(dv, PLAYER_DRACULA) == VIENNA);
    
    int numOfTraps, numOfVamps;
    whatsThere(dv,SZEGED,&numOfTraps,&numOfVamps);
    assert(numOfTraps == 0 && numOfVamps == 1);
    whatsThere(dv,ZAGREB,&numOfTraps,&numOfVamps);
    assert(nT == 1 && nV == 0);
    whatsThere(dv,VIENNA,&numOfTraps,&numOfVamps);
    assert(nT == 1 && nV == 0);

    assert(howHealthyIs(dv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    disposeDracView(dv);
    printf("passed extra2!\n");

    // EXTRA TEST 3 - deleting traps once trail has passed
    printf("extra test 3!\n");
    PlayerMessage messages10[] = {"Drop","party","at","Varrock"};
    dv = newDracView("GHA.... SMA.... HVR.... MBI.... DSZTV.. "
                     "GCO.... SSR.... HSO.... MNP.... DZAT... "
                     "GFR.... STO.... HBE.... MRO.... DVIT..."
                     "GCO.... SSR.... HSO.... MNP.... DPRT... "
                     "GHA.... SMA.... HVR.... MBI.... DNUT... "
                     "GFR.... STO.... HBE.... MRO.... DSTT..."
                     "GHA.... SMA.... HVR.... MBI.... DPAT... ", messages3);
    assert(GiveMeTheRound(dv) == 7);
    assert((giveMeTheScore(dv)) == (GAME_START_SCORE - (SCORE_LOSS_DRACULA_TURN*GiveMeTheRound(dv))));
    
    assert(whereIs(dv, PLAYER_LORD_GODALMING) == HAMBURG);
    assert(whereIs(dv, PLAYER_DR_SEWARD) == MADRID);
    assert(whereIs(dv, PLAYER_VAN_HELSING) == VARNA);
    assert(whereIs(dv, PLAYER_MINA_HARKER) == BARI);
    assert(whereIs(dv, PLAYER_DRACULA) == PARIS);
    
    int numOfTraps, numOfVamps;
    whatsThere(dv,SZEGED,&numOfTraps,&numOfVamps);
    assert(numOfTraps == 0 && numOfVamps == 1);
    whatsThere(dv,SZEGED,&numOfTraps,&numOfVamps);
    // since traps are destroyed after every 6 moves in the trail
    assert(nT == 0 && nV == 1);
    whatsThere(dv,VIENNA,&numOfTraps,&numOfVamps);
    assert(nT == 1 && nV == 0);
    whatsThere(dv,PRAGUE,&numOfTraps,&numOfVamps);
    assert(nT == 1 && nV == 0);
    whatsThere(dv,NUREMBURG,&numOfTraps,&numOfVamps);
    assert(nT == 1 && nV == 0);
    whatsThere(dv,STRASBOURG,&numOfTraps,&numOfVamps);
    assert(nT == 1 && nV == 0);
    whatsThere(dv,PARIS,&numOfTraps,&numOfVamps);
    assert(nT == 1 && nV == 0);
    
    disposeDracView(dv);
    printf("passed extra3!\n");


    return 0;
}


// Map.h ... interface to Map data type

// Edited by the group:
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


#ifndef MAP_H
#define MAP_H

#include "Places.h"
#include "GameView.h"

typedef struct edge{
    LocationID  start;
    LocationID  end;
    TransportID type;
} Edge;

// graph representation is hidden 
typedef struct MapRep *Map; 

// operations on graphs 
Map  newMap();  
void disposeMap(Map g); 
void showMap(Map g); 
int  numV(Map g);
int  numE(Map g, TransportID t);
LocationID* connLocs (Map g, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea);

LocationID closestCity(Map g, LocationID targetLocation, LocationID *cities, int citiesSize);

#endif

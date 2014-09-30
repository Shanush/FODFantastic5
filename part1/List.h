// List ADT - made by the FODFantastic5

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Map.h"
#include "Places.h"

typedef struct list *List;

List newlist();

void appendLocation (List l, LocationID location);

void joinTwoList (List front, List back);

int numElements (List l);

void deletelist(List l);

#endif
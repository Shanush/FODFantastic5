// LIST implementation

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


#include "List.h"

typedef struct node *NodePointer;

struct list {
    NodePointer first;
    NodePointer last;
    int numElements;
};

struct node {
    LocationID item;
    NodePointer next;
};

// Helper Functions
static NodePointer makeNewNode(LocationID location);

List newlist() {
    List newList = malloc(sizeof(struct list));
    
    // Set first and last to null
    // number of elements to zero
    newList->first = newList->last = NULL;
    newList->numElements = 0;
    
    return newList;
}

void appendLocation (List l, LocationID location) {
    assert(l != NULL); // Ensure list is valid
    
    // Make a new node with the location
    NodePointer newNode = makeNewNode(location);
    
    
    if (l->first == NULL) {
        // List is empty
        // make first and last the new node
        l->first = newNode;
        l->last = newNode;
        
    } else {
        // List is not empty
        // update last, after adding new node
        l->last->next = newNode;
        l->last = l->last->next;
        
    }
    
    // Increment number of elements in list
    l->numElements++;
}

void joinTwoList (List front, List back) {
    
    // Ensure front is valid
    // Back can be NULL - it will be ignored
    assert(front != NULL);
    
    // If back is not valid or is an empty list
    if (back != NULL && back->first != NULL) {
        
        if (front->first == NULL) {
            // If front is empty
            front->first = back->first;
            front->last = back->last;
            
            
        } else {
            // Insert to the back of list
            front->last->next = back->first;
            front->last = back->last;
        }
        
        //Add to the back number of elements to the front.
        front->numElements += back->numElements;
    }
    
    free(back);
}

int numElements (List l) {
    assert(l != NULL);
    
    return l->numElements;
}

LocationID *convertListToArray(List l, int *numLocation) {
    
    // Sets the number of elements to "numLocation"
    *numLocation = numElements(l);
    
    // Allocated memory for array
    LocationID *array = malloc(sizeof(LocationID)*numElements(l));
    
    //increment variables
    int i;
    NodePointer curr;
    
    // ensures that both i is less than numLocation
    //     i.e. not overflowing the array by some random accident
    // and curr is not null
    //     i.e not accessing a null pointer by some random accident
    // just to be safe (Y)
    for (i = 0, curr = l->first; i < *numLocation && curr != NULL;
         i++, curr = curr->next) {
        
        array[i] = curr->item;
    }
    
    return array;
}

void deletelist(List l) {
    assert(l != NULL);

    // Deletes the first node
    // Adds the next node to the front
    // Repeats until null
    while (l->first != NULL) {
        NodePointer toBeDeleted = l->first;
        l->first = toBeDeleted->next;
        free(toBeDeleted);
    }
    
    //Gotta free l the head as well
    free(l);
}

// makes a new node from location
// mallocs required space
// initalises the next to be null
static NodePointer makeNewNode(LocationID location) {
    NodePointer newNode = malloc(sizeof(struct node));
    newNode->item = location;
    newNode->next = NULL;
    
    return newNode;
}

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

//Helper Functions
static NodePointer makeNewNode(LocationID location);

List newlist() {
    List newList = malloc(sizeof(struct list));
    
    newList->first = newList->last = NULL;
    newList->numElements = 0;
    
    return newList;
}

void appendLocation (List l, LocationID location) {
    assert(l != NULL);
    
    NodePointer newNode = makeNewNode(location);
    
    if (l->first == NULL) {
        l->first = newNode;
        l->last = newNode;
    } else {
        l->last->next = newNode;
        l->last = l->last->next;
    }
    
    l->numElements++;
}

void joinTwoList (List front, List back) {
    assert(front != NULL && back != NULL);
    
    front->last = back->first;
    front->numElements += back->numElements;
    
    free(back);
}

int numElements (List l) {
    assert(l != NULL);
    
    return l->numElements;
}

void deletelist(List l) {
    assert(l != NULL);
    
    while (l->first != NULL) {
        NodePointer toBeDeleted = l->first;
        l->first = toBeDeleted->next;
        free(toBeDeleted);
    }
    
    free(l);
}

static NodePointer makeNewNode(LocationID location) {
    NodePointer newNode = malloc(sizeof(struct node));
    newNode->item = location;
    newNode->next = NULL;
    
    return newNode;
}

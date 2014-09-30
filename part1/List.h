
typedef struct list *List;

List newlist();
void appendLocation (List l, LocationID location);
int numElements (List l);
void deletelist(List l);
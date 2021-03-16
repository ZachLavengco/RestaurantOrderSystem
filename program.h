#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// struct definition for each order
typedef struct Node {
    char* name;   // name of order
    int burgers;   // number of burgers in order
    int salads;    // number of salads in order
    bool present;  // check if person is in restaurant
    struct Node* next;
} node;

extern int debugMode;

void clearToEoln();
int getNextNWSChar ();
int getPosInt ();
char *getName();
void clearToEoln();
void printCommands();

void doAdd (node** head);
void doCallAhead (node** head);
void doWaiting (node** head);
void doRetrieve (node** head);
void doList (node** head);
void doDisplay (node** head);
void doEstimateTime(node** head);
void clear(node** head);

void addToList(node** head, char* nm, int bgr, int sld, bool prst);
bool doesNameExist(node** head, char* nm);
void updateStatus(node** head, char* nm);
void retrieveAndRemove(node** head, int rdyBurgs, int rdySalads);
int countOrdersAhead(node** head, char* nm);
int displayWaitingTime(node** head, char* nm);
void displayOrdersAhead(node** head, char* nm);
void displayListInformation(node** head);
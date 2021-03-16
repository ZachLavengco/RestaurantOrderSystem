#include "program.h"

// checks if a name is already in the system (used for 'a', 'c', 'w', 't', 'l' commands)
bool doesNameExist(node** head, char* nm) {
    // checks if list is empty
    if (*head == NULL) {
        return false;
    }
    // sets a node pointer to iterate through list
    node* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->name, nm) == 0)  // checks if name is found
            return true;
        
        temp = temp->next;  // iterator
    }
    return false;  // occurs when no name is found
}

// adds a new order to the end of the list (used for 'a', 'c' commands)
void addToList(node** head, char* nm, int bgr, int sld, bool prst) {
    // creates new node and stores necessary data within
    node* newNode = (node*)malloc(sizeof(node));
    newNode->name = nm;
    newNode->burgers = bgr;
    newNode->salads = sld;
    newNode->present = prst;
    newNode->next = NULL;

    // if start of list then front is set to node
    if (*head == NULL) {
        *head = newNode;
    }  // if existing nodes are present
    else {
        node* temp = *head;
        while (true) {
            if (debugMode == true)
              printf( "Visiting node %s with values %d and %d\n", temp->name, temp->burgers, temp->salads);
            if (temp->next == NULL) {
                temp->next = newNode;
                break;
            }
            temp = temp->next;
        }
    }
}

// updates whether a name is in-restaurant or not (used for 'w' command)
// if returns false, customer is in-restaurant
void updateStatus(node** head, char* nm) {
  node* temp = *head;

  while (strcmp(temp->name, nm) != 0) {
    temp = temp->next;
  }
  temp->present = true;
}

// finds if a name's order is ready and is also in-restaurant (used for 'r' command)
void retrieveAndRemove(node** head, int rdyBurgs, int rdySalads) {
    // sets a node pointer to iterate through list
    node* temp = *head;

    if (temp != NULL && temp->burgers <= rdyBurgs && temp->salads <= rdySalads && temp->present == true) {
      *head = temp->next;
      free (temp->name);
      free (temp);
      return;
    }

    while (temp != NULL) {
        if (debugMode == true)
            printf( "Visiting node %s with values %d and %d\n", temp->name, temp->burgers, temp->salads);
        // makes sure there's enough burgers and salads ready
        if (temp->next != NULL && temp->next->burgers <= rdyBurgs && temp->next->salads <= rdySalads && temp->next->present == true) {
            if (debugMode == true)
                printf( "Visiting node %s with values %d and %d\n", temp->next->name, temp->next->burgers, temp->next->salads);
            if (temp->next->next != NULL){
                node* delete = temp->next;
                temp->next = temp->next->next;
                free (delete->name);
                free (delete);
                return;
            }
            else {
                free (temp->next->name);
                free (temp->next);
                temp->next = NULL;
                return;
            }
        }
        else {
          temp = temp->next;
        }
    }
    printf("No matching orders found.\n");
}

// returns number of orders waiting ahead of specified name (used for 'l' command)
int countOrdersAhead(node** head, char* nm) {
    int count = 0;
    // sets a node pointer to iterate through list
    node* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->name, nm) == 0)  // checks if name is found
            return count;
        
        temp = temp->next;  // iterator
        count++;  // adds up amount of orders passed by
    }
    printf ("No match found for the given name.Try again!\n");
    return 0;
}

// displays the waiting time of order for specified name (used for 't' command)
int displayWaitingTime(node** head, char* nm) {
    int time = 0;
    // sets a node pointer to iterate through list
    node* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->name, nm) == 0)  // checks if name is found
            return time;
        if (debugMode == true)
          printf( "Visiting node %s with values %d and %d\n", temp->name, temp->burgers, temp->salads);
        
        time += (temp->burgers) * 5;  // adds up amount of time it takes to make the burgers per order
        time += (temp->salads) * 2;  // adds up amount of time it takes to make the salads per order
        temp = temp->next;  // iterator
    }
    return 0;
}

// displays all orders until specific order name is reached (used for 'l' command)
void displayOrdersAhead(node** head, char* nm) {
    // sets a node pointer to iterate through list
    node* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->name, nm) == 0)  // checks if name is found
            return;
        
        // checks whether name is present or not
        printf(" %s: %d burgers and %d salads \n", temp->name, temp->burgers, temp->salads);

        temp = temp->next;  // iterator
    }
}

// displays each order's name, order details, and in-restaurant status (used for 'd' command)
void displayListInformation(node** head) { 
    // sets a node pointer to iterate through list
    node* temp = *head;
    while (temp != NULL) {
        
        // checks whether name is present or not
        if (temp->present == false)
            printf("%s: %d burgers and %d salads, currently not in the restaurant.\n", temp->name, temp->burgers, temp->salads);
        else
            printf("%s: %d burgers and %d salads, currently in the restaurant.\n", temp->name, temp->burgers, temp->salads);

        temp = temp->next;  // iterator
    }
}
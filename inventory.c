// COP3502C // Programming Assignment #5 // Mina Georgoudiou // 04/10/24

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CMDLEN 35
#define MAXLEN 19
#define TABLESIZE 300007

// global variables for safe-keeping
int money = 100000;
int complexity = 0;

typedef struct item {
    char name[MAXLEN+1];
    int quantity;
    int saleprice;
} item;

typedef struct node {
    item* iPtr;
    struct node* next;
} node;

typedef struct hashtable {
    node** lists;
    int size;
} hashtable;

// prototype for given hash function
int hashfunc(char* word, int size);
node* hashSearch(hashtable* h, char* item);

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("invalid input/output args");
        return -1;
    }
    // open input file
    FILE* inFile = fopen(argv[1],"r");
    // create or overwrite output file
    FILE* outFile = fopen(argv[2],"w");

    // make sure the files exist
    if (inFile == NULL || outFile == NULL) {
        printf("invalid input/output arg");
        return -1;
    }

    // dynamically allocate hash table
    hashtable* h = (hashtable*)malloc(sizeof(hashtable));
    h->size = TABLESIZE;
    h->lists = (node**)malloc(sizeof(node*)*TABLESIZE);
    for (int x = 0; x < TABLESIZE; x++) 
        h->lists[x] = NULL;

    // first line of input should be a count of how many commands are being inputted
    int cmdCount;
    fscanf(inFile, " %d", &cmdCount);

    // execute command loop this many times
    for(int x = 0; x <= cmdCount; x++) {
        
        // put the next line into a string
        char cmd[CMDLEN];
        fgets(cmd, CMDLEN, inFile);

        // first token will always be the type of command
        char* token;
        char* rest = cmd;
        token = strtok_r(rest, " ", &rest);

        // buy command
        if (strcmp(token, "buy") == 0) {
            // finish tokenizing cmd
            char* name = strtok_r(rest, " ", &rest);
            int num = atoi(strtok_r(rest, " ", &rest));
            int price = atoi(strtok_r(rest, " ", &rest));

            item* entry = hashSearch(h, name);

        }
        // sell command
        if (strcmp(token, "sell") == 0) {
            char* name = strtok_r(rest, " ", &rest);
            int num = atoi(strtok_r(rest, " ", &rest));
        }
        // change price command
        if (strcmp(token, "change_price") == 0) {
            char* name = strtok_r(rest, " ", &rest);
            int price = atoi(strtok_r(rest, " ", &rest));
        }
    }

    free(h);
}

int hashfunc(char* word, int size) {
    int len = strlen(word);
    int res = 0;
    for (int i=0; i<len; i++)
        res = (1151*res + (word[i]-'a'))%size;
    return res;
}

item* hashSearch(hashtable* h, char* name) {
    int row = hashfunc(name, TABLESIZE);
    // get linked list using row generated by hashfunction given the item string
    node* head = h->lists[row];
    // temp for parsing
    node* temp = head;
    while (temp != NULL) {
        // if we've found a pre-existing match for the record
        if (!strcmp(temp->iPtr->name, name))
            return temp->iPtr;

        // increment complexity
        complexity++;

        // and move onto the next one otherwise
        temp = temp->next;
    }

    // if the function hasnt returned yet, it must mean we have to add a new entry.
    node* newNode = (node*)malloc(sizeof(node));

    // since we're inserting any new node at the front of the linked list, simply set next to head pointer (which might be NULL if the linked list was previously empty)
    newNode->next = head;
    
    // allocate item pointer and set name and defaults
    newNode->iPtr = (item*)malloc(sizeof(item));
    strcpy(newNode->iPtr->name, name);
    newNode->iPtr->quantity = 0;
    newNode->iPtr->saleprice = NULL;

    // set row in hashtable to newnode pointer since its now the front
    h->lists[row] = newNode;

    // increment complexity one more time.
    complexity++;
    
    // and return
    return newNode->iPtr;

}
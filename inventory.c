// COP3502C // Programming Assignment #5 // Mina Georgoudiou // 04/10/24

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CMDLEN 35
#define MAXLEN 19
#define TABLESIZE 300007

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
        if (strcmp(token, "buy") == 0) {}
        // sell command
        if (strcmp(token, "sell") == 0) {}
        // change price command
        if (strcmp(token, "change_price") == 0) {}
    }

}

int hashfunc(char* word, int size) {
    int len = strlen(word);
    int res = 0;
    for (int i=0; i<len; i++)
    res = (1151*res + (word[i]-'a'))%size;
    return res;
}
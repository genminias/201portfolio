#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include "classes.h"

int main(int argc, char *argv[]) {
    printf("Loading in dataset, please wait a moment...\n");

    //gets # of lines in dataset
    /*FILE *dataset = fopen("title.basics.tsv", "r");
    if (!dataset) {
        printf("Error: dataset could not be opened for reading");
        return -2;
    }
    char buf[1000];
    int count = 0;
    while(fgets(buf, 1000, dataset) != NULL) {
        count++;
    }
    fclose(dataset);
    printf("%d\n", count);*/

    //READ DATASET HERE
    int movLength = 0;
    movie **movArr = loadDataset(&movLength);
    if (movArr == NULL) {
        return -1;
    }
    printf("%d\n", movLength); //take this out

    //start UI
    char catalogName[20];
    printf("Welcome to your movie catalog!\n");
    printf("What would you like to name your first catalog? (must be 15 characters or less): ");
    scanf("%s", catalogName);
    if (strlen(catalogName) > 15) { //maybe make this separate function so it doesn't exit the whole program?
        printf("Error: catalog name must be 15 characters or less, please try again\n");
        return -2;
    }
    strcat(catalogName, ".txt");

    //FILE *logFile = fopen(catalogName, "w");

    //MENU HERE (printMenu function?)

    return 0;
}
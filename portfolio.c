#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
//#include "classes.h" //MAKE THIS FILE
//#include "classes.c" //MAKE THIS FILE

//MAKE A MAKEFILE :)

int main(void) {
    char catalogName[20];

    printf("Welcome to your movie catalog!\n");
    printf("What would you like to name your first catalog? (must be less than 16 characters): ");
    scanf("%s", catalogName);
    while (strlen(catalogName) > 15) {
        printf("Error: catalog name must be less than 16 characters, please try again\n");
        return -1;
    }
    strcat(catalogName, ".txt");
    printf("%s\n", catalogName);

    //FILE *logFile = fopen(catalogName, "w");

    return 0;
}
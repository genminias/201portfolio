#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include "classes.h"

int main(int argc, char *argv[]) {
    printf("Loading in dataset, please wait a moment...\n\n");

    //read dataset
    int movLength = 0;
    movie **movArr = loadDataset(&movLength);
    if (movArr == NULL) {
        return -1;
    }

    //create first catalog
    catalogs *newCatalog = malloc(sizeof(catalogs));
    catalogList *list = malloc(sizeof(catalogList));

    char temp[500];
    printf("Welcome to your movie catalog!\n");
    printf("What would you like to name your first catalog?: ");
    scanf("%s", temp);
    strcat(temp, ".txt");
    int tempLen = strlen(temp);
    newCatalog->catalogName = malloc((tempLen + 1) * sizeof(char));
    strcpy(newCatalog->catalogName, temp);
    newCatalog->next = NULL;
    list->head = newCatalog;
    printf("\nCatalog created!\n");

    //FILE *logFile = fopen(newCatalog->catalogName, "w");

    //MAIN MENU HERE (make a print main menu function)
    int menuItem = 0;
    printf("What would you like to do next?\n\n");
    printf("1 - create new catalog\n");
    printf("2 - open an existing catalog\n");
    printf("3 - quit program\n\n");
    printf("Type the corresponding number: ");
    scanf(" %d", &menuItem);
    if ((menuItem <= 0) || (menuItem >= 4)) {
        printf("Error: Must choose menu options 1, 2, or 3. Please try again.\n");
        return -3; //make it jump back to menu ?
    }

    if (menuItem == 1) { //create new catalog
        printf("\n\nWhat would you like to name this catalog?: ");
        scanf("%s", temp);
        strcat(temp, ".txt");
        catalogs *ptr = list->head;
        while (ptr) {
            if (strcmp(ptr->catalogName, temp) == 0) {
                printf("Error: Catalog already exists. Would you like to overwrite it?\n");
                //if yes, overwright
                //if no, print main menu function
                return -4; //take this out
            }
            else {
                ptr = ptr->next;
            }
        }
        catalogs *anotherCatalog = malloc(sizeof(catalogs));
        tempLen = strlen(temp);
        anotherCatalog->catalogName = malloc((tempLen + 1) * sizeof(char));
        strcpy(anotherCatalog->catalogName, temp);
        anotherCatalog->next = list->head;
        list->head = anotherCatalog;
        //print menu for catalog functions
    }
    if (menuItem == 2) { //open existing catalog
        printf("\n\nWhich catalog would you like to edit?\n");
        catalogs *ptr = list->head;
        while (ptr) {
            printf("%s\n", ptr->catalogName);
            ptr = ptr->next;
        }
        printf("\nType one of the catalogs as it is shown above: ");
        scanf("%s", temp);
        //error if unknown catalog
        //openfile, or send filename to another fucntion
        //print menu for catalog functions
    }
    if (menuItem == 3) { //quit program
        printf("\nGoodbye! Your catalog(s) will be saved for future reference\n");
        return 0;
    }

    return 0;
}
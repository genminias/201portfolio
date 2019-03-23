#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include "classes.h"

int main(int argc, char *argv[]) {
    printf("Loading in dataset, please wait a moment...\n\n");

    //read dataset
    int movLength = 0;
    struct movie *root = loadDataset(&movLength);
    if (root == NULL) {
        return -1;
    }

    //create first catalog (FIX!!!!!!! should store filenames in another file, not in linked list ? also, possibly
    //take out creating a new catalog at startup)
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
        return -3; //make it jump back to menu, try using a while loop
    }

    if (menuItem == 1) { //create new catalog
        printf("\n\nWhat would you like to name this catalog?: ");
        scanf("%s", temp);
        strcat(temp, ".txt");
        catalogs *ptr = list->head;
        while (ptr) {
            if (strcmp(ptr->catalogName, temp) == 0) {
                printf("Error: Catalog already exists. Would you like to overwrite it? (1-yes, 2-no): ");
                //if yes, overwright (apparently can just open file to write using "w")
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
        printf("\n\nWhich catalog would you like to open?\n");
        catalogs *ptr = list->head;
        while (ptr) {
            printf("%s\n", ptr->catalogName);
            ptr = ptr->next;
        }
        printf("\nType one of the catalogs as it is shown above: ");
        scanf("%s", temp);
        //error if unknown catalog
        //open file, or send filename to another fucntion
        //print menu for catalog functions
    }
    if (menuItem == 3) { //quit program
        printf("\nGoodbye! Your catalog(s) will be saved for future reference\n");
        //free catalog memory ???
        return 0;
    }

    return 0;
}
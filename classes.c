#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "classes.h"

///////////////////////////////////////////////////////////////////////////////////////////

//function that loads data into a binary search tree (maybe change to AVL tree)
struct movie *loadDataset(int *movLength) {

    //open file
    FILE *basics = fopen("title.basics.tsv", "r");
    if (!basics) {
        printf("Error: dataset could not be opened for reading");
        return NULL;
    }

    //root node
    struct movie *root = NULL;

    //read whole lines into buffer arrays
    int i = 0;
    char *tconstBuf = malloc(15 * sizeof(char));
    char *titleTypeBuf = malloc(20 * sizeof(char));
    char *primaryTitleBuf = malloc(200 * sizeof(char));
    char *originalTitleBuf = malloc(200 * sizeof(char));
    char *isAdultBuf = malloc(15 * sizeof(char));
    char *startYearBuf = malloc(15 * sizeof(char));
    char *endYearBuf = malloc(15 * sizeof(char));
    char *runtimeMinutesBuf = malloc(15 * sizeof(char));
    char *genresBuf = malloc(200 * sizeof(char));

    while (fscanf(basics, "%s %s %[^\t] %[^\t] %s %s %s %s %[^\n]", tconstBuf,
    titleTypeBuf, primaryTitleBuf, originalTitleBuf, isAdultBuf, startYearBuf, endYearBuf, runtimeMinutesBuf, genresBuf) == 9) {

        //if movie, allocate new movie node
        char *moviesWord = "movie";
        int length = 0;
        if (strcmp(moviesWord, titleTypeBuf) == 0) {
            struct movie *newMovie = malloc(sizeof(movie));
            if (newMovie == NULL) {
                printf("Error: cannot make new movie node\n");
                return NULL;
            }

            length = strlen(tconstBuf); //tconst
            newMovie->tconst = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->tconst, tconstBuf);

            length = strlen(titleTypeBuf); //titleType
            newMovie->titleType = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->titleType, titleTypeBuf);

            length = strlen(primaryTitleBuf); //primaryTitle
            newMovie->primaryTitle = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->primaryTitle, primaryTitleBuf);

            length = strlen(originalTitleBuf); //originalTitle
            newMovie->originalTitle = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->originalTitle, originalTitleBuf);

            length = strlen(isAdultBuf); //isAdult
            newMovie->isAdult = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->isAdult, isAdultBuf);

            length = strlen(startYearBuf); //startYear
            newMovie->startYear = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->startYear, startYearBuf);

            length = strlen(runtimeMinutesBuf); //runtimeMinutes
            newMovie->runtimeMinutes = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->runtimeMinutes, runtimeMinutesBuf);

            length = strlen(genresBuf); //genres
            newMovie->genres = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->genres, genresBuf);

            newMovie->left = NULL; //tree pointers
            newMovie->right = NULL;
            newMovie->listNext = NULL;

            i++; //node counter

            //insert node into tree
            if (root == NULL) {
                root = newMovie;
            }
            else {
                insert(root, newMovie);
            }
        }
    }
    *movLength = i - 1;
    fclose(basics);
    free(tconstBuf);
    free(titleTypeBuf);
    free(primaryTitleBuf);
    free(originalTitleBuf);
    free(isAdultBuf);
    free(startYearBuf);
    free(runtimeMinutesBuf);
    free(genresBuf);
    return root;
}

///////////////////////////////////////////////////////////////////////////////////////////

//insert movie node into binary search tree, sorted by primaryTitle
void insert(movie *root, movie *newMovie) {
    if (strcmp(newMovie->primaryTitle, root->primaryTitle) < 0) {
        if (root->left != NULL) { //traverse left tree
            insert(root->left, newMovie);
        }
        else {
            root->left = newMovie;
        }
    }
    else if (strcmp(newMovie->primaryTitle, root->primaryTitle) > 0) {
        if (root->right != NULL) { //traverse right tree
            insert(root->right, newMovie);
        }
        else {
            root->right = newMovie;
        }
    }
    else { //duplicate values linked list
        struct movie *head = root;
        while (head->listNext != NULL) {
            head = head->listNext;
        }
        head->listNext = newMovie;
    }
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////
//should these be implemented in a class???????????

//user log
char *username() {
    char buf[200];
    printf("What is your username?: ");
    scanf("%s", buf);
    strcat(buf, ".txt");
    //should I account for case ?
    int len = strlen(buf);
    char *user = malloc((len + 1) * sizeof(char));
    strcpy(user, buf);
    FILE *userCatalog = fopen(user, "r");
    if (userCatalog == NULL) {
        printf("\nThis username does not exist. I'll create it for you!\n");
        userCatalog = fopen(user, "w");
        fclose(userCatalog);
        printf("\nEntering user catalog...\n");
    }
    else {
        printf("\nEntering user catalog...\n");
    }
    return user;
}

///////////////////////////////////////////////////////////////////////////////////////////

//main menu
//PUT A HELP COMMAND
int printMainMenu(int menuItem) {
    printf("------------------------------------------------------\n");
    printf("What would you like to do?\n\n");
    printf("1 - Edit/update catalog (add, delete, list)\n");
    printf("2 - Overwrite catalog (clean slate)\n");
    printf("3 - Delete catalog\n");
    printf("4 - Change catalogs\n");
    printf("5 - Quit program\n\n");
    printf("Type the corresponding number: ");
    scanf("%d", &menuItem); //test for int ?
    printf("------------------------------------------------------\n");
    return menuItem;
}

///////////////////////////////////////////////////////////////////////////////////////////

//main menu options
void mainMenuOptions(int menuItem, char *user) {
    if (menuItem == 1) { //edit catalog
        menuItem = printCatalogMenu(menuItem);
        catalogMenuOptions(menuItem, user);
        return;
    }
    if (menuItem == 2) { //overwrite catalog
        FILE *catalog = fopen(user, "w");
        fclose(catalog);
        printf("Catalog overwritten!\n");
        //print main menu or catalog menu ?
        return;
    }
    if (menuItem == 3) { //delete catalog
        int status = remove(user);
        if (status == 0) {
            printf("Catalog deleted!\n");
            printf("You will be prompted to enter a new or existing username\n");
            printf("------------------------------------------------------\n");
            user = username();
            menuItem = printMainMenu(menuItem);
            while ((menuItem < 1) || (menuItem > 5)) {
                printf("Error: Must choose menu options 1-5. Please try again.\n");
                menuItem = printMainMenu(menuItem);
            }
            mainMenuOptions(menuItem, user);
        }
        return;
    }
    if (menuItem == 4) { //change user catalog
        printf("Going back...\n");
        printf("------------------------------------------------------\n");
        user = username();
        menuItem = printMainMenu(menuItem);
        while ((menuItem < 1) || (menuItem > 5)) {
            printf("Error: Must choose menu options 1-5. Please try again.\n");
            menuItem = printMainMenu(menuItem);
        }
        mainMenuOptions(menuItem, user);
        return;
    }
    if (menuItem == 5) { //quit program
        printf("Goodbye! Your catalog(s) will be saved for future reference\n");
        printf("------------------------------------------------------\n");
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

//main menu
int printCatalogMenu(int menuItem) {
    printf("------------------------------------------------------\n");
    printf("What would you like to do now?\n\n");
    printf("1 - List all movies in the catalog\n");
    printf("2 - Add movie to the catalog\n");
    printf("3 - Delete movie from the catalog\n");
    printf("4 - Go back to main menu\n");
    printf("5 - Quit program\n\n");
    //search catalog and print specific movies ?
    printf("Type the corresponding number: ");
    scanf("%d", &menuItem); //test for int ?
    printf("------------------------------------------------------\n");
    return menuItem;
}

///////////////////////////////////////////////////////////////////////////////////////////

//catalog menu options
void catalogMenuOptions(int menuItem, char *user) {

}

///////////////////////////////////////////////////////////////////////////////////////////

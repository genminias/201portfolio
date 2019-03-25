#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "classes.h"

///////////////////////////////////////////////////////////////////////////////////////////

//function that loads data into a binary search tree
struct movie *loadDataset(int *movLength) {

    //open file
    FILE *basics = fopen("title.basics.tsv", "r");
    if (!basics) {
        printf("Error: dataset could not be opened for reading");
        return NULL;
    }

    struct movie *root = NULL; //root node

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

            //do I even need most of these ????
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

//insert movie node into binary search tree, sorted by caseTitle
void insert(movie *root, movie *newMovie) {
    struct movie *cursor = root;
    if (strcmp(newMovie->primaryTitle, cursor->primaryTitle) < 0) { //traverse left tree
        if (cursor->left != NULL) {
            insert(cursor->left, newMovie);
        }
        else {
            cursor->left = newMovie;
        }
    }
    else if (strcmp(newMovie->primaryTitle, cursor->primaryTitle) > 0) { //traverse right tree
        if (cursor->right != NULL) {
            insert(cursor->right, newMovie);
        }
        else {
            cursor->right = newMovie;
        }
    }
    else { //duplicate values linked list
        struct movie *head = cursor;
        while (head->listNext != NULL) {
            head = head->listNext;
        }
        head->listNext = newMovie;
    }
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////

//search tree for given movie
struct movie *searchTree(char *keyword, movie *root) {
    struct movie *cursor = root;
    char caseTitle[200]; //make traversal case insensitive
    int j = 0;
    strcpy(caseTitle, cursor->primaryTitle);
    while (caseTitle[j]) {
        caseTitle[j] = toupper(caseTitle[j]);
        j++;
    }
    if (strcmp(keyword, caseTitle) < 0) { //traverse left tree
        if (cursor->left != NULL) {
            return searchTree(keyword, cursor->left);
        }
        else {
            printf("Sorry! This movie does not exist. Try searching again.\n");
            return NULL;
        }
    }
    else if (strcmp(keyword, caseTitle) > 0) { //traverse right tree
        if (cursor->right != NULL) { 
            return searchTree(keyword, cursor->right);
        }
        else {
            printf("Sorry! This movie does not exist. Try searching again.\n");
            return NULL;
        }
    }
    else { //found match
        if (cursor->listNext != NULL) { //if duplicate titles, list all and choose
            int count = 1, choice = 0;
            char val[50];
            struct movie *head = cursor;
            printf("There are multiple movies with this title. Which one would you like to add?\n\n");
            printf("%d - %s (%s)\n", count, head->primaryTitle, head->startYear);
            while (head->listNext != NULL) {
                count++;
                head = head->listNext;
                printf("%d - %s (%s)\n", count, head->primaryTitle, head->startYear);
            }
            printf("\nType the corresponding number: ");
            fgets(val, 50, stdin);
            int size = strlen(val);
            val[size-1] = '\0';
            choice = atoi(val);
            printf("------------------------------------------------------\n");
            if ((choice < 1) || (choice > count)) {
                printf("Error: entered invalid number. No movie will be added.\n");
                return NULL;
            }
            for (int k = 1; k < choice; k++) {
                cursor = cursor->listNext;
            }
        }
        return cursor;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////

//add movie to catalog
void addMovieToLog(movie *match, char *user) {
    FILE *catalog = fopen(user, "a");
    fprintf(catalog, "%s (%s)\n", match->primaryTitle, match->startYear);
    fprintf(catalog, "%s minutes\n", match->runtimeMinutes);
    fprintf(catalog, "%s\n\n", match->genres);
    fclose(catalog);
    printf("%s has been added to your catalog!\n", match->primaryTitle);
    printf("------------------------------------------------------\n");
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////

char *matchingTitle() {
    char keyword[200];
    int j = 0;
    printf("What movie would you like to add to your catalog? (please type full title): ");
    fgets(keyword, 200, stdin);
    int size = strlen(keyword);
    keyword[size-1] = '\0';
    printf("------------------------------------------------------\n");
    while (keyword[j]) {
        keyword[j] = toupper(keyword[j]);
        j++;
    }
    int len = strlen(keyword);
    char *temp = malloc((len + 1) * sizeof(char));
    strcpy(temp, keyword);
    return temp;
}

///////////////////////////////////////////////////////////////////////////////////////////

//user log
char *username() {
    char buf[200];
    printf("What is your username?: ");
    fgets(buf, 200, stdin);
    int size = strlen(buf);
    buf[size-1] = '\0';
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
char *printMainMenu(char *menuItem) {
    printf("------------------------------------------------------\n");
    printf("What would you like to do?\n\n");
    printf("1 - Edit/update catalog (add, delete, list)\n");
    printf("2 - Overwrite catalog (clean slate)\n");
    printf("3 - Delete catalog\n");
    printf("4 - Change users\n");
    printf("5 - Quit program\n\n");
    printf("Type the corresponding number: ");
    fgets(menuItem, 50, stdin);
    int size = strlen(menuItem);
    menuItem[size-1] = '\0';
    printf("------------------------------------------------------\n");
    return menuItem;
}

///////////////////////////////////////////////////////////////////////////////////////////

//main menu options
int mainMenuOptions(char *menuItem, char *user) {
    if (strcmp(menuItem, "1") == 0) { //edit catalog
        printf("Opening catalog menu...\n");
        printf("------------------------------------------------------\n");
        return 3;
    }
    else if (strcmp(menuItem, "2") == 0) { //overwrite catalog
        FILE *catalog = fopen(user, "w");
        fclose(catalog);
        printf("Catalog overwritten!\n");
        printf("\nOpening catalog menu...\n");
        printf("------------------------------------------------------\n");
        return 3;
    }
    else if (strcmp(menuItem, "3") == 0) { //delete catalog
        int status = remove(user);
        if (status == 0) {
            printf("Catalog deleted!\n");
            printf("\nYou will be prompted to enter a new or existing username.\n");
            printf("------------------------------------------------------\n");
            return 1;
        }
        else {
            printf("Error: could not delete catalog.\n");
        }
        return 5;
    }
    else if (strcmp(menuItem, "4") == 0) { //change user catalog
        printf("Going back...\n");
        printf("------------------------------------------------------\n");
        return 1;
    }
    else if (strcmp(menuItem, "5") == 0) { //quit program
        printf("Goodbye! Your catalog(s) will be saved for future reference.\n");
        printf("------------------------------------------------------\n");
        return 5;
    }
    else {
        printf("Error: Must choose menu options 1-5. Please try again.\n");
        return 2;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

//catalog menu
char *printCatalogMenu(char *menuItem) {
    printf("What would you like to do now?\n\n");
    printf("1 - List all movies in the catalog\n");
    printf("2 - Add movie to the catalog\n");
    printf("3 - Delete movie from the catalog\n");
    printf("4 - Go back to main menu\n");
    printf("5 - Quit program\n\n");
    printf("Type the corresponding number: ");
    fgets(menuItem, 50, stdin);
    int size = strlen(menuItem);
    menuItem[size-1] = '\0';
    printf("------------------------------------------------------\n");
    return menuItem;
}

///////////////////////////////////////////////////////////////////////////////////////////

//catalog menu options
int catalogMenuOptions(char *menuItem, char *user) {
    FILE *catalog;
    char buf[1000];
    if (strcmp(menuItem, "1") == 0) { //list movies
        catalog = fopen(user, "r");
        if (catalog == NULL) {
            printf("Error: could not open catalog.\n");
            return 5;
        }
        fseek(catalog, 0, SEEK_END);
        if (ftell(catalog) == 0) {
            fclose(catalog);
            printf("Your catalog is empty. You should add some movies to it first!\n");
            printf("------------------------------------------------------\n");
            return 3;
        }
        fseek(catalog, 0, SEEK_SET);
        while (fgets(buf, 1000, catalog) != NULL) { //change since it parses lines into separate words
            printf("%s", buf);
        }
        printf("------------------------------------------------------\n");
        fclose(catalog);
        printf("Press the ENTER key to go back.\n");
        while (1) { //this might fuckin fail
            fgets(buf, 1000, stdin);
            if (buf[0] == '\n') {
                printf("------------------------------------------------------\n");
                return 3;
            }
        }
        return 3;
    }
    else if (strcmp(menuItem, "2") == 0) { //add movie
        return 4;
    }
    else if (strcmp(menuItem, "3") == 0) { //delete movie
        //open file and open new temp file
        //account for empty
        //read in by line and print (save counter number)
        //prompt to enter counter number
        //read in file again but print lines to new temp file, except don't print counter number line
        //delete file and rename new temp file
        //close file
        return 3;
    }
    else if (strcmp(menuItem, "4") == 0) { //go to main menu
        printf("Going back...\n");
        return 2;
    }
    else if (strcmp(menuItem, "5") == 0) { //quit program
        printf("Goodbye! Your catalog(s) will be saved for future reference.\n");
        printf("------------------------------------------------------\n");
        return 5;
    }
    else {
        printf("Error: Must choose menu options 1-5. Please try again.\n");
        printf("------------------------------------------------------\n");
        return 3;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

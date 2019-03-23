#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <ctype.h>
#include "classes.h"

///////////////////////////////////////////////////////////////////////////////////////////

//function that loads data into an array of structs
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

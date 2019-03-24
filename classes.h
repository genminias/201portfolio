#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

///////////////////////////////////////////////////////////////////////////////////////////

#ifndef MOVIE_NODE
#define MOVIE_NODE
typedef struct movie {
    char *tconst;
    char *titleType;
    char *primaryTitle;
    char *originalTitle;
    char *isAdult;
    char *startYear; //can be /N
    char *runtimeMinutes; //can be /N
    char *genres; //can be /N
    struct movie *left;
    struct movie *right;
    struct movie *listNext;
} movie;
#endif

///////////////////////////////////////////////////////////////////////////////////////////

struct movie *loadDataset(int *movLength);
void insert(movie *root, movie *newMovie);

char *username();

int printMainMenu(int menuItem);
void mainMenuOptions(int menuItem, char *user);

int printCatalogMenu(int menuItem);
void catalogMenuOptions(int menuItem, char *user);

///////////////////////////////////////////////////////////////////////////////////////////

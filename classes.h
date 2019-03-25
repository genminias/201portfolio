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
    //char *nonArticleTitle;
} movie;
#endif

///////////////////////////////////////////////////////////////////////////////////////////

struct movie *loadDataset(int *movLength);
void insert(movie *root, movie *newMovie);
struct movie *searchTree(char *keyword, movie *root);

void addMovieToLog(movie *match, char *user);
char *matchingTitle();
char *username();

char *printMainMenu(char *menuItem);
int mainMenuOptions(char *menuItem, char *user);
char *printCatalogMenu(char *menuItem);
int catalogMenuOptions(char *menuItem, char *user);

///////////////////////////////////////////////////////////////////////////////////////////

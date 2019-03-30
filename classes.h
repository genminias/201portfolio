#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

///////////////////////////////////////////////////////////////////////////////////////////

#ifndef MOVIE_NODE
#define MOVIE_NODE
typedef struct movie {
    char *primaryTitle;
    char *nonArticleTitle;
    char *startYear; //can be /N
    char *runtimeMinutes; //can be /N
    char *genres; //can be /N
    struct movie *left;
    struct movie *right;
    struct movie *listNext;
} movie;
#endif

///////////////////////////////////////////////////////////////////////////////////////////

extern int movieCount;
extern struct movie **array;

struct movie *loadDataset(int *movLength);
void insert(movie *root, movie *newMovie);
void preorder(movie *temp, char *keyword);
struct movie *searchTree(char *keyword, movie *root);
void freeTree(movie *root);

int validDate(int mm, int dd, int yy);
void addMovieToLog(movie *match, char *user);
char *matchingTitle();
char *username();

char *printMainMenu(char *menuItem);
int mainMenuOptions(char *menuItem, char *user);
char *printCatalogMenu(char *menuItem);
int catalogMenuOptions(char *menuItem, char *user);

///////////////////////////////////////////////////////////////////////////////////////////

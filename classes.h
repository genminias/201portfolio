#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <ctype.h>

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

#ifndef CATALOG_LIST
#define CATALOG_LIST
typedef struct catalogs {
    char *catalogName;
    struct catalogs *next;
} catalogs;
#endif

#ifndef HEAD
#define HEAD
typedef struct catalogList {
    struct catalogs *head;
} catalogList;
#endif

///////////////////////////////////////////////////////////////////////////////////////////

struct movie *loadDataset(int *movLength);
void insert(movie *root, movie *newMovie);

///////////////////////////////////////////////////////////////////////////////////////////

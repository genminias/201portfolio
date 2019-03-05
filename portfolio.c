#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include "classes.h"

//MAKE A MAKEFILE :)

//put this in classes.h
typedef struct movie {
    char *tconst;
    char *titleType;
    char *primaryTitle;
    char *originalTitle;
    char *isAdult;
    char *startYear; //can be /N
    char *runtimeMinutes; //can be /N
    char *genres; //can be /N
} movie;

struct movie **loadDataset(int *movLength) {
    //open file
    FILE *basics = fopen("title.basics.tsv", "r");
    if (!basics) {
        printf("Error: dataset could not be opened for reading");
        return NULL;
    }

    //allocate memory for 100 movie *
    const int stepSize = 100;
    int arrLen = stepSize;
    struct movie **movies = malloc(arrLen * sizeof(movie *));
    if (movies == NULL) {
        printf("Error: space not allocated for array of char *");
        return NULL;
    }

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

        //reallocate space in chuncks of 100 movie *
        if (i == arrLen) {
            arrLen += stepSize;
            struct movie **newSpace = realloc(movies, arrLen * sizeof(movie *));
            if (!newSpace) {
                printf("Error: could not reallocate memory while reading in dataset");
                return NULL;
            }
            movies = newSpace;
        }

        //if movie, allocate new struct
        char *moviesWord = "movie";
        int length = 0;
        if (strcmp(moviesWord, titleTypeBuf) == 0) {
            struct movie *newMovie = malloc(sizeof(movie));

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

            movies[i++] = newMovie;
        }
    }
    *movLength = i; //does it need to be i-1 ??
    fclose(basics);
    return movies;
}

int main(int argc, char *argv[]) {

    //gets # of lines in dataset
    /*FILE *dataset = fopen("title.basics.tsv", "r");
    if (!dataset) {
        printf("Error: dataset could not be opened for reading");
        return -2;
    }
    char buf[1000];
    int count = 0;
    while(fgets(buf, 1000, dataset) != NULL) {
        count++;
    }
    fclose(dataset);
    printf("%d\n", count);*/

    //READ DATASET HERE
    int movLength = 0;
    movie **movArr = loadDataset(&movLength);
    if (movArr == NULL) {
        return -1;
    }
    printf("%d", movLength);

    //start UI
    char catalogName[20];
    printf("Welcome to your movie catalog!\n");
    printf("What would you like to name your first catalog? (must be 15 characters or less): ");
    scanf("%s", catalogName);
    if (strlen(catalogName) > 15) { //maybe make this separate function so it doesn't exit the whole program?
        printf("Error: catalog name must be 15 characters or less, please try again\n");
        return -2;
    }
    strcat(catalogName, ".txt");

    //FILE *logFile = fopen(catalogName, "w");

    //MENU HERE (printMenu function?)

    return 0;
}
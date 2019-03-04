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

    //allocate memory for 100 char *
    const int stepSize = 100;
    int arrLen = stepSize;
    struct movie **movies = malloc(arrLen * sizeof(char *));

    //read whole lines into buffer array then use strtok() to parse into separate variables
    char buf[1000];
    int i = 0;
    while (fgets(buf, 1000, basics)) {

        //TEST LOOP FOR 10 STRUCTS (TAKE OUT)
        for (int a = 0; a < 10; a++) {

            //reallocate space in chuncks of 100 char *
            if (i == arrLen) {
                arrLen += stepSize;
                struct movie **newSpace = realloc(movies, arrLen * sizeof(char *));
                if (!newSpace) {
                    printf("Error: could not reallocate memory while reading in dataset");
                    return NULL;
                }
                movies = newSpace;
            }

            buf[strlen(buf)-1] = '\0'; //trims off newline char

            char *token = strtok(buf, "/t"); //tconst
            int tlen1 = strlen(token);
            char *temp1 = token;

            token = strtok(NULL, "/t"); //titleType
            int tlen = strlen(token);
            char *temp2 = "movie";

            //if movie, allocate space for struct variables and continue to parse string
            if (strcmp(temp2, token) == 0) {
                struct movie *newMovie = malloc(sizeof(movie)); //allocate space for struct
                newMovie->tconst = malloc((tlen1 + 1) * sizeof(char)); //allocate space for tconst
                strcpy(newMovie->tconst, temp1);
                newMovie->titleType = malloc((tlen + 1) * sizeof(char)); //allocate space for titleType
                strcpy(newMovie->titleType, token);

                token = strtok(NULL, "/t"); //primaryTitle
                tlen = strlen(token);
                newMovie->primaryTitle = malloc((tlen + 1) * sizeof(char));
                strcpy(newMovie->primaryTitle, token);

                token = strtok(NULL, "/t"); //originalTitle
                tlen = strlen(token);
                newMovie->originalTitle = malloc((tlen + 1) * sizeof(char));
                strcpy(newMovie->originalTitle, token);

                token = strtok(NULL, "/t"); //isAdult
                tlen = strlen(token);
                newMovie->isAdult = malloc((tlen + 1) * sizeof(char));
                strcpy(newMovie->isAdult, token);

                token = strtok(NULL, "/t"); //startYear
                tlen = strlen(token);
                newMovie->startYear = malloc((tlen + 1) * sizeof(char));
                strcpy(newMovie->startYear, token);

                token = strtok(NULL, "/t"); //skips endYear

                token = strtok(NULL, "/t"); //runtimeMinutes
                tlen = strlen(token);
                newMovie->runtimeMinutes = malloc((tlen + 1) * sizeof(char));
                strcpy(newMovie->runtimeMinutes, token);

                token = strtok(NULL, "/t"); //genres
                tlen = strlen(token);
                newMovie->genres = malloc((tlen + 1) * sizeof(char));
                strcpy(newMovie->genres, token);

                movies[i++] = newMovie;
            }
        }
    }

    movLength = &i;
    fclose(basics); //do I need to free any memory? prob not
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
    /*char catalogName[20];
    printf("Welcome to your movie catalog!\n");
    printf("What would you like to name your first catalog? (must be 15 characters or less): ");
    scanf("%s", catalogName);
    if (strlen(catalogName) > 15) { //maybe make this separate function so it doesn't exit the whole program?
        printf("Error: catalog name must be 15 characters or less, please try again\n");
        return -2;
    }
    strcat(catalogName, ".txt");*/

    //FILE *logFile = fopen(catalogName, "w");

    //MENU HERE (printMenu function?)

    return 0;
}
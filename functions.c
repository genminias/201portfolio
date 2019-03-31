#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"

///////////////////////////////////////////////////////////////////////////////////////////

//function that loads data into a binary search tree
struct movie *loadDataset(int *movLength) {

    //open file
    FILE *basics = fopen("title.basics.tsv", "r");
    if (!basics) {
        basics = fopen("data.tsv", "r");
        if (!basics) {
            printf("Error: dataset could not be opened for reading.\n");
            return NULL;
        }
    }

    struct movie *root = NULL; //root node

    //read whole lines into buffer arrays
    int i = 0;
    char titleTemp[500];
    char *token, *temp;
    char *tconstBuf = malloc(20 * sizeof(char));
    char *titleTypeBuf = malloc(30 * sizeof(char));
    char *primaryTitleBuf = malloc(500 * sizeof(char));
    char *originalTitleBuf = malloc(500 * sizeof(char));
    char *isAdultBuf = malloc(15 * sizeof(char));
    char *startYearBuf = malloc(15 * sizeof(char));
    char *endYearBuf = malloc(15 * sizeof(char));
    char *runtimeMinutesBuf = malloc(15 * sizeof(char));
    char *genresBuf = malloc(300 * sizeof(char));

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
            
            length = strlen(primaryTitleBuf); //primaryTitle
            newMovie->primaryTitle = malloc((length + 1) * sizeof(char));
            strcpy(newMovie->primaryTitle, primaryTitleBuf);

            strcpy(titleTemp, primaryTitleBuf); //nonArticleTitle
            token = strtok(primaryTitleBuf, " ");
            if ((strcmp(token, "The") == 0) || (strcmp(token, "A") == 0) || (strcmp(token, "An") == 0)) {
                token = strtok(NULL, " ");
                if (token == NULL) {
                    length = strlen(titleTemp);
                    newMovie->nonArticleTitle = malloc((length + 1) * sizeof(char));
                    strcpy(newMovie->nonArticleTitle, titleTemp);
                }
                else {
                    temp = strchr(titleTemp, ' ');
                    temp = temp + 1;
                    length = strlen(temp);
                    newMovie->nonArticleTitle = malloc((length + 1) * sizeof(char));
                    strcpy(newMovie->nonArticleTitle, temp);
                }
            }
            else {
                length = strlen(titleTemp);
                newMovie->nonArticleTitle = malloc((length + 1) * sizeof(char));
                strcpy(newMovie->nonArticleTitle, titleTemp);
            }

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
    free(endYearBuf);
    free(runtimeMinutesBuf);
    free(genresBuf);
    return root;
}

///////////////////////////////////////////////////////////////////////////////////////////

//insert movie node into binary search tree, sorted by nonArticleTitle
void insert(movie *root, movie *newMovie) {
    struct movie *cursor = root;
    if (strcmp(newMovie->nonArticleTitle, cursor->nonArticleTitle) < 0) { //traverse left tree
        if (cursor->left != NULL) {
            insert(cursor->left, newMovie);
        }
        else {
            cursor->left = newMovie;
        }
    }
    else if (strcmp(newMovie->nonArticleTitle, cursor->nonArticleTitle) > 0) { //traverse right tree
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

int movieCount;
struct movie **array;
//traverses subtree of first found node from keyword
void preorder(movie *temp, char *keyword) {
    if (temp == NULL) {
        return;
    }
    char caseTitle[500]; //make traversal case insensitive
    int j = 0;
    strcpy(caseTitle, temp->nonArticleTitle);
    while (caseTitle[j]) {
        caseTitle[j] = toupper(caseTitle[j]);
        j++;
    }
    int length = strlen(keyword);
    int length2 = strlen(caseTitle);
    if (length > length2) {
        length = length2;
    }
    int found = 0;
    for (int i = 0; i < length; i++) {
        if (caseTitle[i] == keyword[i]) {
            found++;
        }
    }
    preorder(temp->left, keyword); //traverse left subtree
    if (movieCount == 50) {
        return;
    }
    if ((found == length) && (strstr(caseTitle, keyword) != NULL)) { //keyword found
        array[movieCount] = temp;
        movieCount++;
        printf("%d - %s (%s)\n", movieCount, temp->primaryTitle, temp->startYear);
        if (temp->listNext != NULL) {
            struct movie *head = temp;
            while ((head->listNext != NULL) && (movieCount < 50)) {
                head = head->listNext;
                array[movieCount] = head;
                movieCount++;
                printf("%d - %s (%s)\n", movieCount, head->primaryTitle, head->startYear);
            }
        }
    }
    preorder(temp->right, keyword); //traverse right subtree
}

///////////////////////////////////////////////////////////////////////////////////////////

//search tree for given movie
struct movie *searchTree(char *keyword, movie *root) {
    struct movie *cursor = root;
    char caseTitle[500], val[50]; //make traversal case insensitive
    int j = 0;
    movieCount = 0;
    strcpy(caseTitle, cursor->nonArticleTitle);
    while (caseTitle[j]) {
        caseTitle[j] = toupper(caseTitle[j]);
        j++;
    }
    int length = strlen(keyword);
    int length2 = strlen(caseTitle);
    if (length > length2) {
        length = length2;
    }
    int found = 0;
    for (int i = 0; i < length; i++) {
        if (caseTitle[i] == keyword[i]) {
            found++;
        }
    }
    if (found == length) { //keyword found
        struct movie *temp = cursor;
        array = malloc(100 * sizeof(movie *));
        printf("Which movie would you like to add?\n\n");
        preorder(temp, keyword);
        if (movieCount >= 50) {
            printf("\nMax amount of movies shown.\n");
            printf("If you don't see the one you're looking for, then press\n");
            printf("the ENTER key to go back and try using more words in your search.\n");
            printf("\nType the corresponding number (or ENTER): ");
        }
        else {
            printf("\nType the corresponding number: ");
        }
        int tries = 0;
        do {
            fgets(val, 50, stdin);
            tries++;
        } while (strchr(val, '\n') == NULL);
        if (tries != 1) {
            strcpy(val, "lolllll");
        }
        if ((val[0] == '\n') && (movieCount >= 50)) {
            printf("------------------------------------------------------\n");
            printf("No movie will be added.\n");
            printf("------------------------------------------------------\n");
            return NULL;
        }
        length = strlen(val);
        val[length-1] = '\0';
        int choice = atoi(val);
        printf("------------------------------------------------------\n");
        if ((choice < 1) || (choice > movieCount)) {
            printf("Error: entered invalid number. No movie will be added.\n");
            printf("------------------------------------------------------\n");
            return NULL;
        }
        return array[choice-1];
    }
    else if (strcmp(keyword, caseTitle) < 0) { //traverse left tree
        if (cursor->left != NULL) {
            return searchTree(keyword, cursor->left);
        }
        else {
            printf("Sorry! This movie does not exist. Try searching again.\n");
            printf("------------------------------------------------------\n");
            return NULL;
        }
    }
    else if (strcmp(keyword, caseTitle) > 0) { //traverse right tree
        if (cursor->right != NULL) { 
            return searchTree(keyword, cursor->right);
        }
        else {
            printf("Sorry! This movie does not exist. Try searching again.\n");
            printf("------------------------------------------------------\n");
            return NULL;
        }
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////

//free allocated memory for binary search tree
void freeTree(movie *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    if (root->listNext != NULL) {
        freeTree(root->listNext);
        root->listNext = NULL;

    }
    free(root->primaryTitle);
    free(root->nonArticleTitle);
    free(root->startYear);
    free(root->runtimeMinutes);
    free(root->genres);
    free (root);
}

///////////////////////////////////////////////////////////////////////////////////////////

//checks if user inputted date is valid
int validDate(int mm, int dd, int yy) {
    if (mm < 1 || mm > 12) {
        return 0;
    }
    int days = 31;
    if (mm == 2) {
        days = 28;
        if ((yy % 400 == 0) || ((yy % 4 == 0) && (yy % 100 != 0))) {
            days = 29;
        }
    }
    else if ((mm == 4) || (mm == 6) || (mm == 9) || (mm == 11)) {
        days = 30;
    }
    if ((dd < 1) || (dd > days)) {
        return 0;
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////

//add movie to catalog file
void addMovieToLog(movie *match, char *user) {
    char buf[500], temp[500]; 
    char mediaType[20], date[15];
    int found = 0, count = 0;
    int mm = 0, dd = 0, yy = 0;
    FILE *catalog = fopen(user, "r");
    if (!catalog) {
        printf("Error: could not open file.\n");
        printf("------------------------------------------------------\n");
        free(array);
        return;
    }
    sprintf(temp, "%s (%s)\n", match->primaryTitle, match->startYear); //find if movie is already in catalog
    while (fgets(buf, 500, catalog) != NULL) {
        if (strcmp(buf, temp) == 0) {
            found = 1;
        }
    }
    if (found == 1) {
        printf("This movie is already in your catalog. It will not be added again.\n");
        printf("------------------------------------------------------\n");
        fclose(catalog);
        free(array);
        return;
    }
    fclose(catalog);
    printf("What is the media type of this movie?\n\n"); //get media type
    printf("1 - DVD\n");
    printf("2 - Blu-ray\n");
    printf("3 - Digital\n\n");
    printf("Type the corresponding number: ");
    int tries = 0, choice = 0;
    do {
        fgets(mediaType, 20, stdin);
        tries++;
    } while (strchr(mediaType, '\n') == NULL);
    int size = strlen(mediaType);
    mediaType[size-1] = '\0';
    choice = atoi(mediaType);
    if ((tries != 1) || (choice < 1) || (choice > 3)) {
        printf("------------------------------------------------------\n");
        printf("Error: entered invalid number. Please try again.\n");
        printf("------------------------------------------------------\n");
        addMovieToLog(match, user);
        return;
    }
    printf("------------------------------------------------------\n"); //get date added
    printf("Type the date added (MM/DD/YYYY): ");
    tries = 0;
    do {
        fgets(date, 15, stdin);
        tries++;
    } while (strchr(date, '\n') == NULL);
    size = strlen(date);
    for (int a = 0; a < size; a++) {
        if (date[a] == '/') {
            count++;
        }
    }
    if ((tries != 1) || (count != 2)) {
        printf("------------------------------------------------------\n");
        printf("Error: entered invalid date. Please try again.\n");
        printf("------------------------------------------------------\n");
        addMovieToLog(match, user);
        return;
    }
    sscanf(date, "%d/%d/%d", &mm, &dd, &yy); //valid date function
    int valid = validDate(mm, dd, yy);
    if (valid == 0) {
        printf("------------------------------------------------------\n");
        printf("Error: entered invalid date. Please try again.\n");
        printf("------------------------------------------------------\n");
        addMovieToLog(match, user);
        return;
    }
    catalog = fopen(user, "a");
    if (!catalog) {
        printf("Error: could not open file.\n");
        printf("------------------------------------------------------\n");
        free(array);
        return;
    }
    fprintf(catalog, "%s (%s)\n", match->primaryTitle, match->startYear); //print movie to file
    fprintf(catalog, "%s minutes\n", match->runtimeMinutes);
    fprintf(catalog, "%s\n", match->genres);
    if (choice == 1) {
        fprintf(catalog, "DVD\n");
    }
    else if (choice == 2) {
        fprintf(catalog, "Blu-ray\n");
    }
    else {
        fprintf(catalog, "Digital\n");
    }
    fprintf(catalog, "%d/%d/%d\n\n", mm, dd, yy);
    fclose(catalog);
    printf("------------------------------------------------------\n");
    printf("%s (%s) has been added to your catalog!\n", match->primaryTitle, match->startYear);
    printf("------------------------------------------------------\n");
    free(array);
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////

//get user inputted movie to search database with (case insensitive)
char *matchingTitle() {
    char *temp, *art;
    char keyword[500], titleTemp[500];
    int j = 0;
    printf("What movie would you like to add to your catalog?\n"); //get user inputted movie
    printf("Enter a movie or keyword: ");
    int tries = 0;
    do {
        fgets(keyword, 500, stdin);
        tries++;
    } while (strchr(keyword, '\n') == NULL);
    if ((tries != 1) || (keyword[0] == '\n')) {
        strcpy(keyword, "kslfajslkdfsslkdfj");
    }
    int size = strlen(keyword);
    keyword[size-1] = '\0';
    printf("------------------------------------------------------\n");
    while (keyword[j]) {
        keyword[j] = toupper(keyword[j]);
        j++;
    }
    strcpy(titleTemp, keyword);
    char *token = strtok(titleTemp, " ");
    if ((strcmp(token, "THE") == 0) || (strcmp(token, "A") == 0) || (strcmp(token, "AN") == 0)) { //remove starting articles
        token = strtok(NULL, " ");
        if (token == NULL) {
            size = strlen(keyword);
            temp = malloc((size + 1) * sizeof(char));
            strcpy(temp, keyword);
            return temp;
        }
        else {
            art = strchr(keyword, ' ');
            art = art + 1;
            size = strlen(art);
            temp = malloc((size + 1) * sizeof(char));
            strcpy(temp, art);
            return temp;
        }
    }
    size = strlen(keyword);
    temp = malloc((size + 1) * sizeof(char));
    strcpy(temp, keyword);
    return temp;
}

///////////////////////////////////////////////////////////////////////////////////////////

//get username
char *username() {
    char buf[40];
    char *user;
    int j = 0, size = 0;
    printf("What is your username? (must be less than 30 characters): ");
    int tries = 0;
    do {
        fgets(buf, 32, stdin);
        tries++;
    } while (strchr(buf, '\n') == NULL);
    if ((tries != 1) || (buf[0] == '\n')) {
        printf("------------------------------------------------------\n");
        if (tries != 1) {
            printf("Error: username is too long. Please try again.\n");
        }
        else {
            printf("Error: invalid username (does not fit filename parameters). Please try again.\n");
        }
        printf("------------------------------------------------------\n");
        strcpy(buf, "error");
        size = strlen(buf);
        user = malloc((size + 1) * sizeof(char));
        strcpy(user, buf);
        return user;
    }
    size = strlen(buf);
    buf[size-1] = '\0';
    strcat(buf, ".txt");
    while (buf[j]) {
        buf[j] = tolower(buf[j]);
        j++;
    }
    FILE *userCatalog = fopen(buf, "r");
    if (!userCatalog) {
        userCatalog = fopen(buf, "w");
        if (!userCatalog) {
            printf("------------------------------------------------------\n");
            printf("Error: invalid username (does not fit filename parameters). Please try again.\n");
            printf("------------------------------------------------------\n");
            strcpy(buf, "error");
            size = strlen(buf);
            user = malloc((size + 1) * sizeof(char));
            strcpy(user, buf);
            return user;
        }
        fclose(userCatalog);
        printf("\nThis username does not exist. I'll create it for you!\n");
        printf("\nEntering user catalog...\n");
    }
    else {
        printf("\nEntering user catalog...\n");
    }
    size = strlen(buf);
    user = malloc((size + 1) * sizeof(char));
    strcpy(user, buf);
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
    int tries = 0;
    do {
        fgets(menuItem, 50, stdin);
        tries++;
    } while (strchr(menuItem, '\n') == NULL);
    if (tries == 1) {
        int size = strlen(menuItem);
        menuItem[size-1] = '\0';
        printf("------------------------------------------------------\n");
        return menuItem;
    }
    else {
        printf("------------------------------------------------------\n");
        strcpy(menuItem, "lol");
        return menuItem;
    }
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
        if (!catalog) {
            printf("Error: could not overwrite catalog\n");
            printf("------------------------------------------------------\n");
            return 5;
        }
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
    else { //user input error
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
    printf("4 - Update movie in the catalog\n");
    printf("5 - Go back to main menu\n");
    printf("6 - Quit program\n\n");
    printf("Type the corresponding number: ");
    int tries = 0;
    do {
        fgets(menuItem, 50, stdin);
        tries++;
    } while (strchr(menuItem, '\n') == NULL);
    if (tries == 1) {
        int size = strlen(menuItem);
        menuItem[size-1] = '\0';
        printf("------------------------------------------------------\n");
        return menuItem;
    }
    else {
        printf("------------------------------------------------------\n");
        strcpy(menuItem, "lol");
        return menuItem;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

//catalog menu options
int catalogMenuOptions(char *menuItem, char *user) {
    FILE *catalog;
    char buf[1000];
    if (strcmp(menuItem, "1") == 0) { //list movies
        catalog = fopen(user, "r");
        if (!catalog) {
            printf("Error: could not open catalog.\n");
            return 5;
        }
        fseek(catalog, 0, SEEK_END); //check if catalog is empty
        if (ftell(catalog) == 0) {
            fclose(catalog);
            printf("Your catalog is empty. You should add some movies to it first!\n");
            printf("------------------------------------------------------\n");
            return 3;
        }
        fseek(catalog, 0, SEEK_SET);
        while (fgets(buf, 1000, catalog) != NULL) { //print file contents
            printf("%s", buf);
        }
        printf("------------------------------------------------------\n");
        fclose(catalog);
        printf("Press the ENTER key to go back.\n");
        do {
            fgets(buf, 1000, stdin);
        } while (strchr(buf, '\n') == NULL);
        printf("------------------------------------------------------\n");
        return 3;
    }
    else if (strcmp(menuItem, "2") == 0) { //add movie
        return 4;
    }
    else if (strcmp(menuItem, "3") == 0) { //delete movie
        catalog = fopen(user, "r");
        if (!catalog) {
            printf("Error: could not open catalog.\n");
            return 5;
        }
        fseek(catalog, 0, SEEK_END);
        if (ftell(catalog) == 0) { //check if catalog is empty
            fclose(catalog);
            printf("Your catalog is empty. You should add some movies to it first!\n");
            printf("------------------------------------------------------\n");
            return 3;
        }
        fseek(catalog, 0, SEEK_SET);
        printf("Which movie would you like to delete?\n\n");
        int movCounter = 0, lineCounter = 0, countCounter = 0, choice = 0;
        char val[50];
        while (fgets(buf, 1000, catalog) != NULL) { //print movies
            if (lineCounter == countCounter) {
                movCounter++;
                countCounter = countCounter + 6;
                printf("%d - %s", movCounter, buf);
            }
            lineCounter++;
        }
        printf("\nType the corresponding number: "); //get choice
        int tries = 0;
        do {
            fgets(val, 50, stdin);
            tries++;
        } while (strchr(val, '\n') == NULL);
        if (tries != 1) {
            strcpy(val, "lolllll");
        }
        printf("------------------------------------------------------\n");
        int size = strlen(val);
        val[size-1] = '\0';
        choice = atoi(val);
        if ((choice < 1) || (choice > movCounter)) {
            printf("Error: entered invalid number. No movie will be deleted.\n");
            printf("------------------------------------------------------\n");
            fclose(catalog);
            return 3;
        }
        fseek(catalog, 0, SEEK_SET);
        FILE *temp = fopen("temp.txt", "w");
        if (!temp) {
            printf("Error: could not move files.\n");
            printf("------------------------------------------------------\n");
            return 5;
        }
        choice--;
        lineCounter = 0;
        countCounter = choice * 6;
        char lineStorage[1000];
        while (fgets(buf, 1000, catalog) != NULL) {
            if ((lineCounter < countCounter) || (lineCounter > (countCounter+5))) { //delete movie from file
                fprintf(temp, "%s", buf);
            }
            if (lineCounter == countCounter) {
                strcpy(lineStorage, buf);
                int len = strlen(lineStorage);
                lineStorage[len-1] = '\0';
            }
            lineCounter++;
        }
        fclose(catalog);
        fclose(temp);
        int status = remove(user);
        if (status != 0) {
            printf("Error: could not move files.\n");
            return 5;
        }
        rename("temp.txt", user);
        printf("%s has been deleted from your catalog!\n", lineStorage);
        printf("------------------------------------------------------\n");
        return 3;
    }
    else if (strcmp(menuItem, "4") == 0) { //update movie
        catalog = fopen(user, "r");
        if (!catalog) {
            printf("Error: could not open catalog.\n");
            return 5;
        }
        fseek(catalog, 0, SEEK_END); //check if catalog is empty
        if (ftell(catalog) == 0) {
            fclose(catalog);
            printf("Your catalog is empty. You should add some movies to it first!\n");
            printf("------------------------------------------------------\n");
            return 3;
        }
        fseek(catalog, 0, SEEK_SET);
        printf("Which movie would you like to update?\n\n");
        int movCounter = 0, lineCounter = 0, countCounter = 0, choice = 0;
        char val[50];
        while (fgets(buf, 1000, catalog) != NULL) { //print movies
            if (lineCounter == countCounter) {
                movCounter++;
                countCounter = countCounter + 6;
                printf("%d - %s", movCounter, buf);
            }
            lineCounter++;
        }
        printf("\nType the corresponding number: "); //get choice
        int tries = 0;
        do {
            fgets(val, 50, stdin);
            tries++;
        } while (strchr(val, '\n') == NULL);
        if (tries != 1) {
            strcpy(val, "lolllll");
        }
        printf("------------------------------------------------------\n");
        int size = strlen(val);
        val[size-1] = '\0';
        choice = atoi(val);
        if ((choice < 1) || (choice > movCounter)) {
            printf("Error: entered invalid number. No movie will be updated.\n");
            printf("------------------------------------------------------\n");
            fclose(catalog);
            return 3;
        }
        char mediaType[20], date[15];
        printf("What is the new media type of this movie?\n\n"); //get new media type
        printf("1 - DVD\n");
        printf("2 - Blu-ray\n");
        printf("3 - Digital\n\n");
        printf("Type the corresponding number: ");
        tries = 0;
        do {
            fgets(mediaType, 20, stdin);
            tries++;
        } while (strchr(mediaType, '\n') == NULL);
        size = strlen(mediaType);
        mediaType[size-1] = '\0';
        int mediaChoice = atoi(mediaType);
        if ((tries != 1) || (mediaChoice < 1) || (mediaChoice > 3)) {
            printf("------------------------------------------------------\n");
            printf("Error: entered invalid number. Please try again.\n");
            printf("------------------------------------------------------\n");
            catalogMenuOptions(menuItem, user);
            return 3;
        }
        printf("------------------------------------------------------\n"); //get new date
        printf("Type the new date added (MM/DD/YYYY): ");
        int mm = 0, dd = 0, yy = 0, count = 0;
        tries = 0;
        do {
            fgets(date, 15, stdin);
            tries++;
        } while (strchr(date, '\n') == NULL);
        size = strlen(date);
        for (int a = 0; a < size; a++) {
            if (date[a] == '/') {
                count++;
            }
        }
        if ((tries != 1) || (count != 2)) {
            printf("------------------------------------------------------\n");
            printf("Error: entered invalid date. Please try again.\n");
            printf("------------------------------------------------------\n");
            catalogMenuOptions(menuItem, user);
            return 3;
        }
        sscanf(date, "%d/%d/%d", &mm, &dd, &yy); //valid date function
        int valid = validDate(mm, dd, yy);
        if (valid == 0) {
            printf("------------------------------------------------------\n");
            printf("Error: entered invalid date. Please try again.\n");
            printf("------------------------------------------------------\n");
            catalogMenuOptions(menuItem, user);
            return 3;
        }
        fseek(catalog, 0, SEEK_SET);
        FILE *temp = fopen("temp.txt", "w");
        if (!temp) {
            printf("Error: could not move files.\n");
            printf("------------------------------------------------------\n");
            return 5;
        }
        choice--;
        lineCounter = 0;
        countCounter = (choice * 6) + 3;
        char lineStorage[1000];
        while (fgets(buf, 1000, catalog) != NULL) {
            if ((lineCounter < countCounter) || (lineCounter > (countCounter+1))) { //update movie in file
                fprintf(temp, "%s", buf);
            }
            if (lineCounter == (countCounter-3)) {
                strcpy(lineStorage, buf);
                size = strlen(lineStorage);
                lineStorage[size-1] = '\0';
            }
            if (lineCounter == countCounter) {
                if (mediaChoice == 1) {
                    fprintf(temp, "DVD\n");
                }
                else if (mediaChoice == 2) {
                    fprintf(temp, "Blu-ray\n");
                }
                else {
                    fprintf(temp, "Digital\n");
                }
            }
            else if (lineCounter == (countCounter+1)) {
                fprintf(temp, "%d/%d/%d\n", mm, dd, yy);
            }
            lineCounter++;
        }
        fclose(catalog);
        fclose(temp);
        int status = remove(user);
        if (status != 0) {
            printf("Error: could not move files.\n");
            return 5;
        }
        rename("temp.txt", user);
        printf("------------------------------------------------------\n");
        printf("%s has been updated!\n", lineStorage);
        printf("------------------------------------------------------\n");
        return 3;
    }
    else if (strcmp(menuItem, "5") == 0) { //go to main menu
        printf("Going back...\n");
        return 2;
    }
    else if (strcmp(menuItem, "6") == 0) { //quit program
        printf("Goodbye! Your catalog(s) will be saved for future reference.\n");
        printf("------------------------------------------------------\n");
        return 5;
    }
    else { //user input error
        printf("Error: Must choose menu options 1-6. Please try again.\n");
        printf("------------------------------------------------------\n");
        return 3;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

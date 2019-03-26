#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"

int main(int argc, char *argv[]) {
    printf("------------------------------------------------------\n");
    printf("Loading in dataset, please wait a moment...\n");
    printf("------------------------------------------------------\n");

    //read dataset
    int movLength = 0;
    struct movie *root = loadDataset(&movLength);
    if (root == NULL) {
        return -1;
    }

    printf("Welcome to your movie database! :)\n\n");

    char *user, *keyword;
    char *menuItem = malloc(50 * sizeof(char));

    //UI start
    int choice = 1;
    while (choice != 5) { //end / error
        switch (choice) {
            case 1: //start / 3rd and 4th main menu options
                user = username();
                choice = 2;
                break;
            case 2: //wrong # main menu / 4th catalog menu option
                menuItem = printMainMenu(menuItem);
                choice = mainMenuOptions(menuItem, user);
                break;
            case 3: //1st and 2nd main menu options / 1st, 2nd, 3rd, and wrong # catalog menu options
                menuItem = printCatalogMenu(menuItem);
                choice = catalogMenuOptions(menuItem, user);
                break;
            case 4: //add movie
                keyword = matchingTitle();
                struct movie *match = searchTree(keyword, root);
                if (match == NULL) {
                    printf("------------------------------------------------------\n");
                    choice = 3;
                    break;
                }
                addMovieToLog(match, user);
                choice = 3;
                break;
        }
    }
    
    //free memory allocated for binary search tree
    freeTree(root);
    return 0;
}

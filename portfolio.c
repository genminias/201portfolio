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

    //get username
    char *user = username();

    //print main menu and go through options
    int menuItem = 0;
    menuItem = printMainMenu(menuItem);
    while ((menuItem < 1) || (menuItem > 5)) {
        printf("Error: Must choose menu options 1-5. Please try again.\n");
        menuItem = printMainMenu(menuItem);
    }
    mainMenuOptions(menuItem, user);

    return 0;
}
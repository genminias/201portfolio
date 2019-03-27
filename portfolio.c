#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"

/*
SOURCES USED:
https://www.youtube.com/watch?v=5wzmEKjNqiU - helped with reading in IMDB dataset
https://www.thecrazyprogrammer.com/2015/03/c-program-for-binary-search-tree-insertion.html - helped with node insertion into binary search tree
https://www.programiz.com/c-programming/c-file-input-output - helped with file streams
https://codeforwin.org/2018/02/c-program-remove-word-from-file.html - helped with removing an entry from catalog
https://www.techonthenet.com/c_language/standard_library_functions/ctype_h/toupper.php - helped with conversion to uppercase
https://stackoverflow.com/questions/1484817/how-do-i-make-a-simple-makefile-for-gcc-on-linux - helped with creating a makefile
plus many many more (for smaller syntax things)! thanks stackoverflow :)
*/

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
                if (strcmp(user, "error") == 0) {
                    choice = 1;
                }
                else {
                    choice = 2;
                }
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
                    choice = 3;
                    break;
                }
                addMovieToLog(match, user);
                choice = 3;
                break;
        }
    }
    
    //free memory allocated
    free(menuItem);
    freeTree(root);
    return 0;
}

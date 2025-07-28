// CS Amusement Park
// main.c
// Written by <YOUR-NAME>, <YOUR-ZID>
// on <TODAYS-DATE>
//
// <PROGRAM DESCRIPTION>

#include <stdio.h>

#include "cs_amusement_park.h"

int main(void) {
    // Welcome message
    printf("Welcome to CS Amusement Park!\n");
    
    // NOTE: The printing of the ascii park will fail `1091 style`. 
    // You will not be marked on this.
    printf(
        "                                           o\n"
        "                                         o |\n"
        "                                         |\n"
        "      .       .           ._._.    _                     .===.\n"
        "      |`      |`        ..'\\ /`.. |H|        .--.      .:'   `:.\n"
        "     //\\-...-/|\\         |- o -|  |H|`.     /||||\\     ||     ||\n"
        " ._.'//////,'|||`._.    '`./|\\.'` |\\\\||:. .'||||||`.   `:.   .:'\n"
        " ||||||||||||[ ]||||      /_T_\\   |:`:.--'||||||||||`--..`=:='...\n\n"
    );

    printf("Enter the name of the park: ");
    char name[MAX_SIZE];
    scan_name(name);
    struct park *park = initialise_park(name);

    // Command loop
    command_loop(park);

    // Free all allocated memory
    free_park(park);

    // End message
    printf("\nGoodbye!\n");

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"

int main(){
    // We have to add the scenario initialisations here.


    // Menu:
    printf("Do you wish to start a new game? (Y/N): ");
    char new_game[N];
    scanf("%s\n", &new_game);
    if(strcmp(new_game, "Y") == 0){
        // create new character
    }
    return 0;
}
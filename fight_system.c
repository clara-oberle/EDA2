#include "fight_system.h"
#include <stdbool.h>

Queue *create_queue(Character *player, Enemy *enemy){
    // Create the queue to decide the turns
    // A generator should choose a fighter N times with 50-50 odds, enqueuing the turn generated at each draw
    for(int i=0; i<MAX_TURNS; i++){

    }
}

// Functions used in a fight:
Skill *choose_enemy_skill(Enemy *enemy, Skill *skills[3]){
    // Randomly choose a skill for the enemy
}

void implement_skill(Skill *chosen_skill, Character *player, Enemy *enemy){
    // modify HP, ATK or DEF accordingly
    // Keep track of duration of the skill
}

void time_strike(){ // Parameters are the stack and the enemy structure to modify
    /*There must be a move called "Time Strike," or an equivalent representative name 
    according to the narrative, which allows access to the history of moves executed by
    the player (which is a stack) and randomly selects the k-th move executed counting 
    from the last one, then executes it again with double power. This move can only be 
    used once during the battle */
}

int check_win(Character *player, Enemy *enemy){
    // Check HP points of enemy and player
    // return 0 if character has won, 1 if enemy has won and -1 if they both still have HP
}

bool check_empty_queue(Queue *fight_queue){
    // return true if the queue is empty
}

void end_fight(){
    /* When fights end, in case of victory, the player is prompted with the next scene and its 
    narrative. On the contrary, in case of defeat, the player is prompted with the ability to 
    restart the game or restart the scenario. */

}

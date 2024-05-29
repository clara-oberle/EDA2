#include "fight_system.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//function to get 0 or 1 --> If 0; char turn, if 1; enemy turn
int getRandomZeroOrOne(){
    return rand() % 2;
}

//initialize the queue
void init_queue(FightQueue *queue) {
    queue->first = NULL;
    queue->last = NULL;
    queue->size = 0;
}

//check if empty
bool is_empty(FightQueue *queue){
    return (queue->size == 0);
}

//to enqueue the char
void enqueue_player(FightQueue *queue, Character *player){
    //configure new fighter
    Fighter* new_fighter = (Fighter*)malloc(sizeof(Fighter));
    strcpy(new_fighter->name, player->name);
    new_fighter->type = 0;
    new_fighter->next= NULL;

    if(is_empty(queue)){
        //queue is empty, we configure the queue first and last
        queue->first = new_fighter;
        queue->last = new_fighter;
    }
    else{
        //queue is not empty
        //the next fighter from last is the new fighter, the new last is the new fighter
        queue->last->next = new_fighter;
        queue->last = new_fighter;
    }
    queue->size ++;
}

//to enqueue the enemy
void enqueue_enemy(FightQueue *queue, Enemy *enemy){
    //allocate memory for new fighter
    Fighter* new_fighter = (Fighter*)malloc(sizeof(Fighter));

    //configure the name, type and next
    strcpy(new_fighter->name, enemy->name);
    new_fighter->type = 1;
    new_fighter->next = NULL;

    if(is_empty(queue)){
        //queue is empty, we configure first and last
        queue->first = new_fighter;
        queue->last = new_fighter;
    }
    else{
        //queue is not empty
        //the next fighter from last is the new fighter, the new last is the new fighter
        queue->last->next = new_fighter;
        queue->last = new_fighter;
    }
    queue->size++;
}

FightQueue *create_queue(Character *player, Enemy *enemy){
    // Create the queue to decide the turns
    // A generator should choose a fighter N times with 50-50 odds, enqueuing the turn generated at each draw
    //allocate space for queue
    FightQueue* queue = (FightQueue*)malloc(sizeof(FightQueue));
    // Initialize the queue
    init_queue(queue);

    srand(time(NULL)); // Initialize random number generator with current time
    for(int i=0; i<MAX_TURNS; i++){
        int randomNumber = getRandomZeroOrOne(); // Generate either 0 or 1

        //if random number is 0 --> char turn
        if(randomNumber == 0){
            enqueue_player(queue, player);
        }
        else{
            //random number = 1 --> enemy turn
            enqueue_enemy(queue, enemy);
        }
    }
    //queue is created, we can return it
    return queue;
}

void dequeue(FightQueue *queue){
    // Remove the first fighter from the queue:
    if(queue->size != 0) {
        // make a pointer to the first element
        Fighter *temp = queue->first;
        // make the first element the next element
        queue->first = queue->first->next;
        // free the memory of the dequeued element
        free(temp);
        // update the size of the queue
        queue->size--;
        if (queue->size == 0) {
            queue->last = NULL;
            }
    }  
}

// Functions used in a fight:
int generate_random_index(){
    // Randomly choose an index that will be used to choose the enemy's skill
    return rand() % 3; // select a random index from 0 to 2
}

void init_overlap_queue(OverlapQueue *overlap_queue){
    overlap_queue->first = NULL;
    overlap_queue->last = NULL;
    overlap_queue->size = 0;
}

void enqueue_overlap_skill(OverlapQueue *queue, Skill *skill, int fighter_type){
    // Add the skill into the queue of skills that have duration > 1:
    QueueSkill *q_skill = (QueueSkill *)malloc(sizeof(QueueSkill));
    // initialise q_skill
    q_skill->skill = skill;
    q_skill->next = NULL;
    q_skill->fighter = fighter_type;
    
    // if queue is empty, set head and tail to q_skill
    if (queue->size == 0) {
        queue->first = q_skill;
        queue->last = q_skill;
    } else {
        // otherwise, add the new q_skill to the end of the queue
        queue->last->next = q_skill;
        queue->last = q_skill;
    }
    queue->size++; // increase queue by 1
}

// Remove the skills that have finshed their duration turns from the overlap_queue:
void remove_finished_skills(OverlapQueue *queue){
    if (queue->size != 0) {
        // keep track of the previous and current element when going through the queue
        QueueSkill *current = queue->first; // start with the first element
        QueueSkill *previous = NULL; // previous of first element is NULL

        while (current != NULL) { // while the end of the queue is not reached
            // check if the duration turn of the current skill is 0
            if (current->skill->duration_turn == 0) {
                QueueSkill *to_remove = current; // save the current skill to be removed
                // if so, remove it from the queue
                if (previous == NULL) { // if it is the first element
                    queue->first = current->next; // the next element becomes the first
                } else{
                    previous->next = current->next; // skip the skill to be removed
                }

                if(current->next == NULL){ // if it was the last skill
                    queue->last = previous; // update the last skill to be the previous one
                }

                // go the next element in the queue
                current = current->next;
                free(to_remove); // free memory of removed skill
                queue->size--; // decrease the size of the queue by 1
            
            } else { // if the element/skill still has duration turns
                // move to the next element
                previous = current;
                current = current->next;
            }
        }
    }
}

void init_skill_copy(Skill *skill_copy, Skill *original_skill){
    // initialise the variables of skill_copy to those of original_skill
    strcpy(skill_copy->name, original_skill->name);
    strcpy(skill_copy->description, original_skill->description);
    skill_copy->duration_turn = original_skill->duration_turn;
    skill_copy->modifier[0] = original_skill->modifier[0];
    skill_copy->modifier[1] = original_skill->modifier[1];
    skill_copy->modifier[2] = original_skill->modifier[2];
    skill_copy->type = original_skill->type;
}

// Look for a skill in the overlap_queue:
bool find_in_queue(Skill *skill, OverlapQueue *queue){
    // Start searching from the first element:
    QueueSkill *current = queue->first;
    // Loop through the queue:
    while (current != NULL) {
        // Compare the skill name of the current skill with the target skill name
        if(strcmp(current->skill->name, skill->name) == 0){
            return true; // skill found
        }
        current = current->next; // go to next skill
    }
    return false; // skill not found
}

// Loop for a skill in the stack of previously used player skills:
bool find_in_stack(Skill *skill, SkillStack *stack){
    // loop through the stack starting from the top
    if(stack->top == -1){ // if the stack is empty
        return false; // return not found (i.e. false)
    }
    for(int i = stack->top; i >= 0; i--){
        // compare the skill in the stack to the target skill
        if (strcmp(stack->skills[i]->name, skill->name) == 0) {
            return true; // if it's a match return true (found)
        }
    }
    return false; // otherwise, return false (not found)
} 

// Check if the chosen skill is one that can only be used once and it has already been used:
bool one_time_skill(Skill *chosen_skill, SkillStack *player_used_skills){
    if((strcmp(chosen_skill->name, "Health Exchange") == 0) && find_in_stack(chosen_skill, player_used_skills) == true){
        return true;
    } else if((strcmp(chosen_skill->name, "Time Warp") == 0) && find_in_stack(chosen_skill, player_used_skills) == true){
        return true;
    }
    return false;
}

void add_to_stack(Skill *skill, SkillStack *stack){
    ++stack->top;
    // allocate memory for a new Skill
    stack->skills[stack->top] = malloc(sizeof(Skill));
    // Copy the contents of the skill to the newly allocated memory
    init_skill_copy(stack->skills[stack->top], skill);
}

void pop_stack(SkillStack *stack){
    // check if the stack is empty:
    if(stack->top == -1){
        return;
    }
    // pointer to the skill at the top of the stack:
    Skill *skill_to_free = stack->skills[stack->top];
    // free the memory of the skill
    free(skill_to_free);
    // reduce the stack top by one
    --stack->top;
}

// Find the DEF modifiers that have been previously used to protect the fighter against an attack:
float find_used_DEF_modifier(OverlapQueue *queue, int fighter_type){
    float DEF_modifier =  1; // variable to keep track of the DEF modifier, default is 1 because if there is no modifier DEF*1=DEF
    // Loop through the queue and find the skill that modifies the figther_type's DEF: (player -> 0, enemy -> 1)
    QueueSkill *current = queue->first;
    while(current != NULL){
        if(current->fighter == fighter_type){ // check if the skill belongs to the desired fighter
        /* check if the skill modifies the fighter's DEF - if it were negative it would modify the other 
        fighter's DEF, and if it were 1 it wouldn't modify the DEF since DEF*1 = DEF */
            if(current->skill->modifier[2] > 1){
                DEF_modifier *= current->skill->modifier[2];
                --current->skill->duration_turn; // decrease the duration turn
            }
        }
        current = current->next;
    }
    return DEF_modifier;
}

void print_overlap_queue(OverlapQueue *queue, int fighter_type){
    bool found = false; // keep track of whether a skill that still has duration turns left has been found or not
    // loop through the queue and print the skills that belong to the fighter_type (player -> 0, enemy -> 1)
    QueueSkill *current = queue->first;
    while (current != NULL){
        // check that the skill is not a defence skill as this will not be implemented in the current turn but in the next attack from the other fighter
        if(current->fighter == fighter_type && current->skill->modifier[2] == 1){ 
            printf("- %s: %d turn/s left\n", current->skill->name, current->skill->duration_turn);
            found = true;
        }
        current = current->next;
    }
    if(found == false){ // if none are found print...
        printf("- There are no skills with remaining duration turns.\n");
    }
}

void implement_player_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue, SkillStack *player_used_skills){
    // add the skill to the player_used_skills stack
    add_to_stack(chosen_skill, player_used_skills);
    // remove finished skills (overlapping skills that have reached 0 duration turns):
    remove_finished_skills(overlap_queue);
    // let the player know the skills that are in the overlap queue:
    printf("Your skills that still have duration turns left and will also be applied in this turn:\n");
    print_overlap_queue(overlap_queue, 0);
    // variables to keep track of the player's modified ATK points and the enemy's modified DEF points:
    float ATK_points = player->points[1];
    float enemy_DEF = enemy->points[2];

    /* Find the modifiers of the overlapping player skills (i.e. those with duration > 1) and modify the
    ATK_points and enemy_DEF variables accordingly:*/
    QueueSkill *current = overlap_queue->first;
    while(current != NULL){ // loop through the overlap_queue to find the modifiers for current skill that belongs to the player
        if(current->fighter == 0 && current->skill->duration_turn > 0){ // double check that there are duration turns left just in case
            // modify player's ATK (if modifier is 1 then it stays the same):
            ATK_points *= current->skill->modifier[1];
            // if the DEF modifier is negative then it affects the enemy's DEF:
            if(current->skill->modifier[2] < 0){
                enemy_DEF *= (-1*current->skill->modifier[2]); // get rid of the negative sign
            }
            --current->skill->duration_turn; // decrease the duration turn by one
        }
        // go to the next skill in the overlap_queue
        current = current->next;
    }

    if(chosen_skill->type == 0){ // if the skill is a temporal modifier
        // apply the modifiers of the chosen skill to the ATK_points:
        ATK_points *= chosen_skill->modifier[1];
        // if the enemy previously used a defence skill that increases their DEF, calculate by how much (multiplier):
        float DEF_modifier = find_used_DEF_modifier(overlap_queue, 1); // find the DEF modifier previously used by the enemy (if there is none return 1 since DEF*1 = DEF)
        // apply the DEF modifiers previously used by the enemy to fend of this attack: (if none used then DEF stays the same i.e. DEF*1)
        enemy_DEF *= DEF_modifier;
        // Let the player know if the enemy has previously selected a defence skill that partially protects them from this attack:
        if(DEF_modifier > 1){
            printf("-> The enemy chose a defence skill before this attack, so their DEF increase.\n");
        }

        // check if the player's chosen skill also modifies the enemy's DEF:
        if(chosen_skill->modifier[2] < 0){
            // if so, modify them:
            enemy_DEF *= -1*(chosen_skill->modifier[2]);
        }

        printf("\nYour ATK points: %.2f\n", ATK_points);
        printf("The enemy's DEF: %.2f\n", enemy_DEF);

        // implement the damage to the enemy:
        float damage = ATK_points - (enemy_DEF);
        if(damage > 0){ // check that there is actual damage being done (DEF doesn't stop all ATK)
            printf("Total damage done: %.2f\n", damage);
            enemy->points[0] -= damage; // enemy HP = enemy HP - damage
            printf("\n>>> The enemy's current HP: %.2f\n", enemy->points[0]);
        }else{ // if the defence overcame the attack
            printf("-> The enemy has fended off your attack and emerges unharmed.");
        }
        // decrease the skill duration for the chosen_skill
        --chosen_skill->duration_turn;

    } else if(chosen_skill->type == 1){ // if the skill is a direct attack
        // implement the special skill: (each has to be done separately)
        if(strcmp(chosen_skill->name, "Health Exchange") == 0){
            // swap the enemy and player's HP
            int temp = enemy->points[0];
            enemy->points[0] = player->points[0];
            player->points[0] = temp;
            printf("\n>>> The enemy's current HP: %.2f\n", enemy->points[0]);
            printf(">>> Your current HP: %.2f\n", player->points[0]);
        } else if(strcmp(chosen_skill->name, "Time Warp") == 0){
            // restore half of the player's initial HP
            player->points[0] += 200;
            printf("\n>>> Your current HP: %.2f\n", player->points[0]);
        }
    }
}

void implement_enemy_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue){
    // remove finished skills (overlapping skills that have reached 0 duration turns):
    remove_finished_skills(overlap_queue);
    // let the player know the enemy's skills that are in the overlap queue:
    printf("Enemy skills that still have duration turns left:\n");
    print_overlap_queue(overlap_queue, 1);
    // variables to keep track of the enemy's modified ATK points and the player's modified DEF points:
    float ATK_points = enemy->points[1];
    float player_DEF = player->points[2];

    /* Find the modifiers of the overlapping enemy skills (i.e. those with duration > 1) and modify the
    ATK_points and player_DEF variables accordingly:*/
    QueueSkill *current = overlap_queue->first;
    while(current != NULL){ // loop through the overlap_queue to find the modifiers for current skill that belong to the enemy
        if(current->fighter == 1 && current->skill->duration_turn > 0){ // double check that there are duration turns left just in case
            // modify enemy's ATK (if modifier is 1 then it stays the same):
            ATK_points *= current->skill->modifier[1];
            // if the DEF modifier is negative then it affects the player's DEF:
            if(current->skill->modifier[2] < 0){
                player_DEF *= -1*(current->skill->modifier[2]); // use abs() function to get rid of the negative sign
            }
            --current->skill->duration_turn; // decrease the duration turn by one
            }
        // go to the next skill in the overlap_queue
        current = current->next;
    }

    if(chosen_skill->type == 0){ // if the skill is a temporal modifier
        // apply the modifiers of the chosen skill to the ATK_points:
        ATK_points *= chosen_skill->modifier[1];
        // if the player previously used a skill/s that increases their DEF calculate by how much (multiplier):
        float DEF_modifier = find_used_DEF_modifier(overlap_queue, 0);
        // apply the DEF modifiers previously used by the player to fend of this attack: (if none used then DEF stays the same i.e. DEF*1)
        player_DEF *= DEF_modifier;
        // Let the player know if the enemy has previously selected a defence skill that partially protects them from this attack:
        if(DEF_modifier > 1){
            printf("-> You chose a defence skill before this attack, so your DEF points increase.\n");
        }
        // check if the enemy's chosen skill also modifies the player's DEF:
        if(chosen_skill->modifier[2] < 0){
            // if so, modify them:
            player_DEF *= -1*(chosen_skill->modifier[2]);
        }

        printf("\nThe enemy's ATK points: %.2f\n", ATK_points);
        printf("Your DEF: %.2f\n", player_DEF);

        // implement the damage to the enemy:
        float damage = ATK_points - (player_DEF);
        if(damage > 0){ // check that there is actual damage being done (DEF doesn't stop all ATK)
            printf("Total damage done: %.2f\n", damage);
            player->points[0] -= damage; // player HP = player HP - damage
            printf("\n>>> Your current HP: %.2f\n", player->points[0]);
        } else{ // if the DEF overcame the ATK points
            printf("-> You have avoided your enemy's attack and emerge unharmed.");
        }
        // decrease the skill duration for the chosen_skill
        --chosen_skill->duration_turn;

    } else if(strcmp(chosen_skill->name, "Healing Wave") == 0){
        // implement the special skill
        enemy->points[0] *= chosen_skill->modifier[0]; // restores the enemy's HP by 30%
        printf("\n>>> Enemy HP has increased to: %.2f\n", enemy->points[0]);
    }
}

int check_win(Character *player, Enemy *enemy){ 
    // Check HP points of enemy and player
    // return 0 if character has won, 1 if enemy has won and -1 if they both still have HP left
    if(enemy->points[0] <= 0){
        return 0;
    } else if(player->points[0] <= 0){
        return 1;
    }
    return -1;
}

void printf_battle_specifications(){
    printf("\nUseful information about the battles:\n"
    "- Some of your attack skills last for more than one turn. This means that their corresponding modifiers "
    "will be applied in each of your turns until the skill runs out of duration turns.\n- You cannot choose a skill that "
    "has remaining duration turns left.\n- When you choose a defence skill, it will only be implemented if you are attacked "
    "by the enemy in the next turn. This means that if after choosing the defence it is your turn again, this defence will be "
    "lost.\n- You cannot choose a defence skill two times in a row (if you do so you will get a 'try again' message). If you loose "
    "a defence then tough luck!\n- When you choose a defence, you still attack the enemy in that turn but there are no modifiers "
    "for you ATK points (unless there is a previously used skill that still has duration turns left).\n\n");
}

void reset_player_points(Character *player){
    player->points[0] = 400;
    player->points[1] = 40;
    player->points[2] = 20;
}

// function for a battle - uses all the above functions:
// (returns true if player has won batlle and false if not)
bool battle(Character *character, Enemy *enemy, FightQueue *fight_queue, OverlapQueue *overlap_queue, SkillStack *player_used_skills) {
    printf("\nPrepare yourself, for in this battle you will confront the formidable %s. Good luck!\n", enemy->name);
    bool used_time_strike = false; // Keep track of whether the time strike has been used or not

    while (fight_queue->size != 0) { // Check that the queue is not empty
        if (check_win(character, enemy) == -1) { // If they both still have HP
            if (fight_queue->first->type == 0) { // Character's turn
                int skill_number;
                printf("\nYour turn. Choose a skill:\n1- %s\n2- %s\n"
                       "3- %s\n4- %s\n5- Time Strike\nEnter the number of the chosen skill: ",
                       character->skills[0]->name,
                       character->skills[1]->name, character->skills[2]->name, character->skills[3]->name);
                scanf("%d", &skill_number); // Ask the player to choose a skill

                // Check that the user's input is valid
                while (skill_number > 5 || skill_number < 1) {
                    printf("Invalid input. Try again: ");
                    scanf("%d", &skill_number);
                }

                // If the chosen skill is Time Strike and it has already been used or there are no skills in the stack, tell the user to choose another skill
                while ((skill_number == 5 && used_time_strike == true) || (skill_number == 5 && player_used_skills->top == -1)) {
                    printf("You can only use Time Strike once in a battle and if you have previously used other skills. Choose another skill: ");
                    scanf("%d", &skill_number);
                    while (skill_number > 5 || skill_number < 1) {
                        printf("Invalid input. Try again: ");
                        scanf("%d", &skill_number);
                    }
                }

                // If the chosen skill is Time Strike and it has not been used, implement Time Strike
                if (skill_number == 5 && used_time_strike == false) {
                    used_time_strike = true; // Set the flag to true indicating Time Strike has been used
                    time_strike(player_used_skills, character, enemy, overlap_queue);
                } else {
                    // Create a copy of the skill (this way its duration turns can be modified without affecting the original skill)
                    Skill *chosen_skill = (Skill *)malloc(sizeof(Skill));
                    init_skill_copy(chosen_skill, character->skills[skill_number - 1]);

                    // Check if the skill is one that can only be used once (if so ask the player to choose a different skill)
                    while (one_time_skill(chosen_skill, player_used_skills) == true) {
                        free(chosen_skill);
                        printf("\nThis skill can only be used once during the battle and it has already been used. "
                               "Choose a different skill: ");
                        scanf("%d", &skill_number);
                        chosen_skill = (Skill *)malloc(sizeof(Skill));
                        init_skill_copy(chosen_skill, character->skills[skill_number - 1]);
                    }

                    // Check if the skill is one that has more than one duration turn and still has duration turns left (if so ask the player to choose a different skill)
                    while (find_in_queue(chosen_skill, overlap_queue) == true) {
                        free(chosen_skill);
                        printf("\nThis skill still has duration turns left. Choose a different skill: ");
                        scanf("%d", &skill_number);
                        chosen_skill = (Skill *)malloc(sizeof(Skill));
                        init_skill_copy(chosen_skill, character->skills[skill_number - 1]);
                    }

                    printf("\nYou have chosen %s\n---------------------------------------------\n", chosen_skill->name);
                    // Implement the skill (modify ATK, HP, and DEF accordingly):
                    implement_player_skill(chosen_skill, character, enemy, overlap_queue, player_used_skills);

                    // Add the skill to the overlap queue if its duration turn was more than one:
                    if (chosen_skill->duration_turn > 0) {
                        enqueue_overlap_skill(overlap_queue, chosen_skill, 0);
                    } else { // Otherwise free the copy of the chosen skill
                        free(chosen_skill);
                    }
                }

                // Check if the player has won after their turn
                if (check_win(character, enemy) == 0) { // If the player has won, return true
                    printf("\nCongratulations, you have emerged victorious!\n");
                    return true;
                }
            } else if (fight_queue->first->type == 1) { // Enemy's turn
                Skill *random_skill = (Skill *)malloc(sizeof(Skill));
                srand(time(NULL)); // Initialize random number generator with current time
                int index = generate_random_index(); // Get a random index from 0 to 2

                // Create a copy of the skill corresponding to the randomly generated index
                init_skill_copy(random_skill, enemy->skills[index]);

                // If it is a skill that still has duration turns left, choose another one:
                while (find_in_queue(random_skill, overlap_queue) == true) {
                    index = generate_random_index();
                    init_skill_copy(random_skill, enemy->skills[index]);
                }

                printf("\n%s has chosen %s\n---------------------------------------------\n", enemy->name, random_skill->name);
                // Implement the skill (modify ATK, HP, and DEF accordingly):
                implement_enemy_skill(random_skill, character, enemy, overlap_queue);

                // Add the skill to the overlap queue if its duration turn was more than one:
                if (random_skill->duration_turn > 0) {
                    enqueue_overlap_skill(overlap_queue, random_skill, 1);
                } else { // Otherwise, free the copy of the chosen skill
                    free(random_skill);
                }
            }

            // Check if the player has won or lost after the enemy's turn
            if (check_win(character, enemy) == 0) { // If the player has won, return true
                printf("\nCongratulations, you have emerged victorious!\n");
                return true;
            } else if (check_win(character, enemy) == 1) { // If the player has lost, return false
                printf("\nYou have been defeated. Better luck next time!\n");
                return false;
            }

            dequeue(fight_queue); // Next turn
        }
    }

    if (check_win(character, enemy) == -1) { // If the player and enemy still have HP left but the queue is empty
        // The battle is over and the enemy has won, so return false
        printf("\nThe battle is over and %s is still alive. You lose.\n", enemy->name);
        return false;
    }
}

/*Time Strike - allows access to the history of moves executed by
the player (which is a stack) and randomly selects the k-th move executed counting 
from the last one, then executes it again with double power. This move can only be 
used once during the battle */
void time_strike(SkillStack *stack, Character *player, Enemy *enemy, OverlapQueue *overlap_queue){
    // generate a random index from 0 to the index of the stack top
    int top = stack->top;
    int index;
    if(top == 0){
        index = 0;
    }else{
        index = rand() % top+1;
    }
    // create a copy of the chosen skill at the random index:
    Skill *skill_copy = (Skill*)malloc(sizeof(Skill));
    init_skill_copy(skill_copy, stack->skills[index]);
    // inform the player about the rondomly selected skill:
    printf("\nTime Strike skill: %s\n", skill_copy->name);
    // double the power of the skill:
    // if it is a special skill (Health Exchange or Time Warp) there is no way of 'doubling the power' so they stay the same
    if(skill_copy->type == 0){ // if it is a temporal modifier
        if(skill_copy->modifier[1] > 1){ // if there is an ATK modifier
            skill_copy->modifier[1] *= 2; // double it
            printf("New ATK modifier: %.2f\n", skill_copy->modifier[1]);
        }
        if(skill_copy->modifier[2] < 1){ // if there is a DEF modifier that affects the enemy's DEF (i.e. it is negative)
            skill_copy->modifier[2] /= 2; // since it is a decimal (e.g. -0.85) to make it have double power it is divided by 2
            printf("New enemy DEF modifier (makes the enemy DEF decrease): %.2f\n", skill_copy->modifier[2]);
        }
        if(skill_copy->modifier[2] > 1){ // if is is a defence skill
            skill_copy->modifier[2] *= 2; // double the DEF points
            printf("New DEF modifier: %.2f\n", skill_copy->modifier[2]);
        }
    }
    // implement the skill that now has double power:
    implement_player_skill(skill_copy, player, enemy, overlap_queue, stack);
    // remove the skill from the stack since the implement_player_skill function adds it
    pop_stack(stack);
    // free the memory 
    free(skill_copy);
}
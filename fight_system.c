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

void remove_finished_skills(OverlapQueue *queue){
    if (queue->size != 0) {
        // keep track of the previous and current element when going through the queue
        QueueSkill *current = queue->first; // start with the first element
        QueueSkill *previous = NULL; // previous of first element is NULL

        while (current != NULL) { // while the end of the queue is not reached
            // check if the duration turn of the current skill is 0
            if (current->skill->duration_turn == 0) {
                // if so, remove it from the queue
                if (previous == NULL) { // if it is the first element
                    queue->first = current->next; // the next element becomes the first
                } else { // otherwise...
                    previous->next = current->next; // the next of the previous becomes the next of the current
                }
                if (current == queue->last) { // if the element is also the last
                    queue->last = previous; // set the last to the previous
                }

                // free the memory of the removed element
                QueueSkill *temp = current; // create a temporary pointer to the element
                current = current->next; // go the next element in the queue
                free(temp); // free the memory of the removed element

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

void free_skill_copy(Skill *skill){
    if(skill != NULL){
        free(skill->description);
        free(skill->duration_turn);
        free(skill->modifier);
        free(skill->name);
        free(skill->type);
        free(skill);
    }
}

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

bool find_in_stack(Skill *skill, SkillStack *stack){
    // loop through the stack starting from the top
    for(int i = stack->top; i >= 0; i--){
        // compare the skill in the stack to the target skill
        if (stack->skills[i] == skill) {
            return true; // if it's a match return true (found)
        }
    }
    return false; // otherwise, return false (not found)
} 

bool one_time_skill(Skill *chosen_skill, SkillStack *player_used_skills){
    // check if the chosen skill is one that can only be used once and it has already been used:
    if(strcmp(chosen_skill->name, "Health Exchange") && find_in_stack(chosen_skill, player_used_skills) == true){
        return true;
    } else if(strcmp(chosen_skill->name, "Time Warp") && find_in_stack(chosen_skill, player_used_skills) == true){
        return true;
    }
    return false;
}

void add_to_stack(Skill *skill, SkillStack *stack){
    ++stack->top;
    stack->skills[stack->top] = skill;
}

int find_used_DEF_modifiers(float modifiers[MAX_DURATION], OverlapQueue *queue, int fighter_type){
    // Loop through the queue and find the skills that modify the figther_type's DEF: (player -> 0, enemy -> 1)
    QueueSkill *current = queue->first;
    int index = 0; // variable to keep track of the index of the modifers array
    while(current != NULL){
        if(current->skill->type == fighter_type){ // check if the skill belongs to the desired fighter
        /* check if the skill modifies the fighter's DEF - if it were negative it would modify the other 
        fighter's DEF, and if it were 1 it wouldn't modify the DEF since DEF*1 = DEF */
            if(current->skill->modifier[2] > 1){
                modifiers[index] = current->skill->modifier[2]; // save the modifer in the array
                ++index;
            }
        }
        current = current->next;
    }
    // Add a 1 to the end of the array to ensure that the array is never empty (and a 1 doesn't modify the DEF since DEF*1=DEF)
    modifiers[index] = 1;
    int size = index+1;
    return size; // return the size of the modifiers array
}

void print_overlap_queue(OverlapQueue *queue) {
    printf("Overlap Queue:\n");
    if (queue->size == 0) {
        printf("Queue is empty.\n");
    }

    QueueSkill *current = queue->first;
    while (current != NULL) {
        printf("Name: %s\n", current->skill->name);
        printf("Duration turns: %d\n", current->skill->duration_turn);
        current = current->next;
    }
}

void implement_player_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue, SkillStack *player_used_skills){
    // add the skill to the player_used_skills stack
    add_to_stack(chosen_skill, player_used_skills);
    printf("Stack top: %s\n", player_used_skills->skills[player_used_skills->top]);
    // remove finished skills (overlapping skills that have reached 0 duration turns):
    printf("Before removing used up overlap skills:\n");
    print_overlap_queue(overlap_queue);
    remove_finished_skills(overlap_queue);
    printf("After removing used up overlap skills:\n");
    print_overlap_queue(overlap_queue);
    // variables to keep track of the player's modified ATK points and the enemy's modified DEF points:
    float ATK_points = player->points[1];
    float enemy_DEF = enemy->points[2];

    /* Find the modifiers of the overlapping player skills (i.e. those with duration > 1) and modify the
    ATK_points and enemy_DEF variables accordingly:*/
    QueueSkill *current = overlap_queue->first;
    while(current != NULL){ // loop through the overlap_queue to find the modifiers for current skill
        if(current->skill->type == 0){ // if it is a player's skill
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
    printf("Overlap skill modified ATK points: %f\n", ATK_points);
    printf("Overlap skill modified enemy DEF points: %f\n", enemy_DEF);

    if(chosen_skill->type == 0){ // if the skill is a temporal modifier
        // apply the modifiers of the chosen skill to the ATK_points:
        ATK_points *= chosen_skill->modifier[1];
        // if the enemy previously used a skill/s that increases their DEF calculate by how much (multiplier):
        /* array to store the DEF modifiers: (this way if there are multiple defence skills in the overlap_queue
        they can all be implemented) */
        float DEF_modifiers[MAX_DURATION];
        int size = find_used_DEF_modifiers(DEF_modifiers, overlap_queue, 1); // add the modifiers into the array and return its size
        float total_DEF_modifier = 1; // variable to keep track of the total multiplier for player's DEF
        for(int i=0; i<size; i++){
            total_DEF_modifier *= DEF_modifiers[i];
        }
        // check if the player's chosen skill also modifies the enemy's DEF:
        if(chosen_skill->modifier[2] < 0){
                // if so, modify them:
                enemy_DEF *= -1*(chosen_skill->modifier[2]);
            }

        printf("Player's modified ATK: %f\n", ATK_points);
        printf("Enemy's modified DEF: %f\n", enemy_DEF);

        // implement the damage to the enemy:
        float damage = ATK_points - (enemy_DEF*total_DEF_modifier);
        printf("Damage: %f\n", damage);
        if(damage > 0){ // check that there is actual damage being done (DEF doesn't stop all ATK)
            enemy->points[0] -= damage; // enemy HP = enemy HP - damage
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
        } else if(strcmp(chosen_skill->name, "Time Warp") == 0){
            // restore half of the player's initial HP
            player->points[0] += 200;
        }
    }
}

void implement_enemy_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue){
    // remove finished skills (overlapping skills that have reached 0 duration turns):
    printf("Before removing used up overlap skills:\n");
    print_overlap_queue(overlap_queue);
    remove_finished_skills(overlap_queue);
    printf("After removing used up overlap skills:\n");
    print_overlap_queue(overlap_queue);
    // variables to keep track of the enemy's modified ATK points and the player's modified DEF points:
    float ATK_points = enemy->points[1];
    float player_DEF = player->points[2];

    /* Find the modifiers of the overlapping enemy skills (i.e. those with duration > 1) and modify the
    ATK_points and player_DEF variables accordingly:*/
    QueueSkill *current = overlap_queue->first;
    while(current != NULL){ // loop through the overlap_queue to find the modifiers for current skill
        if(current->skill->type == 1){
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

    printf("Overlap skill modified ATK points: %f\n", ATK_points);
    printf("Overlap skill modified player DEF points: %f\n", player_DEF);

    if(chosen_skill->type == 0){ // if the skill is a temporal modifier
        // apply the modifiers of the chosen skill to the ATK_points:
        ATK_points *= chosen_skill->modifier[1];
        // if the player previously used a skill/s that increases their DEF calculate by how much (multiplier):
        float DEF_modifiers[MAX_DURATION]; // array to store the DEF modifiers
        int size = find_used_DEF_modifiers(DEF_modifiers, overlap_queue, 0);
        float total_DEF_modifier = 1; // variable to keep track of the total multiplier for player's DEF
        for(int i=0; i<size; i++){
            total_DEF_modifier *= DEF_modifiers[i];
        }
        // check if the enemy's chosen skill also modifies the player's DEF:
        if(chosen_skill->modifier[2] < 0){
                // if so, modify them:
                player_DEF *= -1*(current->skill->modifier[2]);
            }

        printf("Enemy's modified ATK: %f\n", ATK_points);
        printf("Player's modified DEF: %f\n", player_DEF);

        // implement the damage to the enemy:
        float damage = ATK_points - (player_DEF*total_DEF_modifier);
        printf("Damage: %f\n", damage);
        if(damage > 0){ // check that there is actual damage being done (DEF doesn't stop all ATK)
            player->points[0] -= damage; // player HP = player HP - damage
        }
        // decrease the skill duration for the chosen_skill
        --chosen_skill->duration_turn;

    } else if(chosen_skill->type == 1){ // if the skill is a direct attack
        // implement the special skill: (each has to be done separately)
        if(strcmp(chosen_skill->name, "") == 0){
            // To do
        }
    }
}

int check_win(Character *player, Enemy *enemy){ 
    // Check HP points of enemy and player
    // return 0 if character has won, 1 if enemy has won and -1 if they both still have HP left
    if(enemy->points[0] == 0){
        return 0;
    } else if(player->points[0] == 0){
        return 1;
    }
    return -1;
}

void time_strike(){ // Parameters are the stack and the enemy structure to modify
    /*There must be a move called "Time Strike," or an equivalent representative name 
    according to the narrative, which allows access to the history of moves executed by
    the player (which is a stack) and randomly selects the k-th move executed counting 
    from the last one, then executes it again with double power. This move can only be 
    used once during the battle */
}

void end_fight(){
    /* When fights end, in case of victory, the player is prompted with the next scene and its 
    narrative. On the contrary, in case of defeat, the player is prompted with the ability to 
    restart the game or restart the scenario. */
}
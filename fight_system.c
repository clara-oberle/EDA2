#include "fight_system.h"
#include "stdbool.h"
#include <stdlib.h>
#include <time.h>

//function to get 0 or 1 --> If 0; char turn, if 1; enemy turn
int getRandomZeroOrOne() {
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

    for(int i=0; i<MAX_TURNS; i++){
        srand(time(NULL)); // Initialize random number generator with current time
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
    if(queue->size =! 0) {
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
    srand(time(NULL)); // Initialize random number generator with current time
    return rand() % 3; // select a random index from 0 to 2
}

void enqueue_overlap_skill(OverlapQueue *queue, Skill *skill){
    // Add the skill into the queue of skills that have duration > 1:
    QueueSkill *q_skill = (QueueSkill *)malloc(sizeof(QueueSkill));
    // initialise q_skill
    q_skill->skill = skill;
    q_skill->next = NULL;
    
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

void remove_finished_skill(OverlapQueue *queue){
    if (queue->size =! 0) {
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
                free(temp); // free the memory of the already analysed element

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
        if (current->skill->name == skill->name) {
            return true; // skill found
        }
        current = current->next; // go to next skill
    }
    return false; // skill not found
}

void implement_player_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue){
    if(chosen_skill->type == 0){ // if the skill is a temporal modifier
        // find the modifiers of the overlapping skills (i.e. those with duration > 1)

        // apply the modifiers of the chosen skill and the overlapping skills

        // decrease the skill duration for the chosen and overlapping skills

        // remove finished overlapping skills (i.e. duration turns have reached 0)

    } else if(chosen_skill->type == 1){ // if the skill is a direct attack
        // implement the special skill: (each has to be done separately)

    }

}

void implement_enemy_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue){
    
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

    // I think we will have to code this in lab 3 when we do the graph
}
#ifndef FIGHT_SYSTEM_H
#define FIGHT_SYSTEM_H

#define MAX_TURNS 20 
#define MAX_DURATION 10 // maximum duration turns of a skill
#include <stdbool.h>
#include "struct_definitions.h"

// Queue to decide turns:
typedef struct{
    char name[N];
    int type; // Character -> 0, Enemy -> 1;
    struct Fighter *next;
}Fighter;

typedef struct{
    Fighter *first; //head
    Fighter *last; //tail
    int size; //size of the queue
}FightQueue;

// Queue to keep track of skills that have duration > 1:
typedef struct{
    int fighter; // what fighter the skill belongs to: character -> 0, enemy -> 1
    Skill *skill;
    struct QueueSkill *next;
}QueueSkill;

typedef struct{
    QueueSkill *first; //head
    QueueSkill *last; //tail
    int size; //size of the queue
}OverlapQueue;

// Stack to keep track of player's moves:
typedef struct{
    int top;
    Skill *skills[MAX_TURNS];
}SkillStack;

// functions:
int getRandomZeroOrOne();
void init_queue(FightQueue *queue);
bool is_empty(FightQueue *queue);
void enqueue_player(FightQueue *queue, Character *player);
void enqueue_enemy(FightQueue *queue, Enemy *enemy);
FightQueue* create_queue(Character *player, Enemy *enemy);
void dequeue(FightQueue *queue);
int generate_random_index();
void init_overlap_queue(OverlapQueue *overlap_queue);
void enqueue_overlap_skill(OverlapQueue *queue, Skill *skill, int fighter_type);
void remove_finished_skills(OverlapQueue *queue);
void init_skill_copy(Skill *skill_copy, Skill *original_skill);
bool find_in_queue(Skill *skill, OverlapQueue *queue);
bool find_in_stack(Skill *skill, SkillStack *stack);
bool one_time_skill(Skill *chosen_skill, SkillStack *player_used_skills);
void add_to_stack(Skill *skill, SkillStack *stack);
int find_used_DEF_modifiers(float modifiers[MAX_DURATION], OverlapQueue *queue, int fighter_type);
void print_overlap_queue(OverlapQueue *queue, int fighter_type);
void implement_player_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue, SkillStack *player_used_skills);
void implement_enemy_skill(Skill *chosen_skill, Character *player, Enemy *enemy, OverlapQueue *overlap_queue);
int check_win(Character *player, Enemy *enemy);
bool battle(Character *character, Enemy *enemy, FightQueue *fight_queue, OverlapQueue *overlap_queue, SkillStack *player_used_skills);
void time_strike();
void end_fight();

#endif
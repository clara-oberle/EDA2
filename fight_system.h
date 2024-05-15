#ifndef FIGHT_SYSTEM_H
#define FIGHT_SYSTEM_H

#define MAX_TURNS 20 
#include "struct_definitions.h"

// Queue to decide turns:
typedef struct{
    char name[N];
    int type; // Character -> 0, Enemy -> 1;
    Fighter *next;
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
    QueueSkill *next;
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
}TimeStrikeStack;

#endif
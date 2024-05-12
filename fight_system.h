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
}Queue;

// Stack to keep track of player's moves:
typedef struct{
    int top;
    Skill *skills[MAX_TURNS];
}TimeStrikeStack;

#endif
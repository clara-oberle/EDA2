#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 20 // max number of letters in the name
#define M 200 //max number of letters for description

typedef struct{
    char name[N];
    char description[M];
    int type; //if type = 0 --> temporarie modifier, else (type = 1) --> direct attack
    int duration_turn; //how many turns the skill lasts
    int modifier[3]; //modifier[0] = life_points, modifier[1] = attack_points, modifier[2] = defense_points 
}Skill;
/*
--> Just to remember how it will have to be accessed printed later on
Assign values to the name and description members
    strcpy(mySkill.name, "Vine Bind");
    strcpy(mySkill.description, "Traps the player with twisting vines, making them slower and easier to hit for one turn.");

Printing the name and description
    printf("Skill Name: %s\n", mySkill.name);
    printf("Description: %s\n", mySkill.description);
*/

typedef struct{
    char name[N];
    int life_points, attack_points, defense_points;
    Skill skills[4]; //array of skills (of type Skill, the structure)
}Character;
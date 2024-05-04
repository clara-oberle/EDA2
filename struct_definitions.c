#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 20 // max number of letters in the name
#define M 200 //max number of letters for description
#define S 4 //number of skills
#define MAX_ENEMIES 3 //max number of enemies

typedef struct{
    char name[N]; char description[M];
    int type; //if type = 0 --> temporary modifier, else (type = 1) --> direct attack
    int duration_turn; //how many turns the skill lasts
    //should i create a macro for the modifier? it will always be modifier[3]
    int modifier[3]; //modifier[0] = life_points, modifier[1] = attack_points, modifier[2] = defense_points 
}Skill;
/*
--> Just to remember how it will have to be accessed and printed later on
Assign values to the name and description members
    strcpy(mySkill.name, "Vine Bind");
    strcpy(mySkill.description, "Traps the player with twisting vines, making them slower and easier to hit for one turn.");

Printing the name and description
    printf("Skill Name: %s\n", mySkill.name);
    printf("Description: %s\n", mySkill.description);
*/
//
typedef struct{
    char name[N];
    int points[3]; //points[0] = life_points; points[1] = attack points; points[2] = defense points
    Skill skills[S]; //array of skills (of type Skill, the structure)
}Character;

typedef struct{
    char name[N], description[M];
    int decision; //if decision = 0 --> left path; else (decision = 1) --> right path
}Scenario;

typedef struct{
    char name[N];
    int points[3]; //points[0] = life_points; points[1] = attack points; points[2] = defense points
}Enemy;

typedef struct{
    char question_text[M], option[M];
    int number_options;
}Decision;

typedef struct{
    char response_text[M], narrative_text_before[M], narrative_text_after[M];
    //narrative text before the battle and after the battle
    Enemy enemies[MAX_ENEMIES];
    int num_enemies; //to know exactly how many enemies are in the array
}Option;
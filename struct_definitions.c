#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 20 // max number of letters in the name
#define M 500 //max number of letters for description
#define S 4 //number of skills
#define MAX_ENEMIES 3 //max number of enemies

typedef struct {
    char name[N];
    char description[M];
    int type; // if type = 0 --> temporary modifier, else (type = 1) --> direct attack
    int duration_turn; // how many turns the skill lasts
    int modifier[3]; // modifier[0] = life_points, modifier[1] = attack_points, modifier[2] = defense_points 
} Skill;
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
    struct Decision *decision;
}Scenario;

typedef struct{
    char name[N];
    int points[3]; //points[0] = life_points; points[1] = attack points; points[2] = defense points
    Skill skills[S];
}Enemy;

typedef struct{
    char question_text[M];
    Option options_list[2]; // There are maximum two options to choose from: left path or right path
                            // Except for the last scenario where there is only one
    int num_options;
}Decision;

typedef struct{
    char response_text[M], narrative_text_before[M], narrative_text_after[M];
    //narrative text before the battle and after the battle
    Enemy enemies[MAX_ENEMIES];
    int num_enemies; //to know exactly how many enemies are in the array
}Option;

// Initialize first scenario
Scenario scenario1 = {
    .name = "The Race of Shadows",
    .description = "[The screen fades from black to reveal the protagonist seated in a sleek, futuristic vehicle, the hum of its engine vibrating through their bones. The starting line looms ahead, illuminated by the glare of neon lights and the distant roar of an eager crowd.] The Race of Shadows begins, and the fate of the seeker hangs in the balance. Four skills pulsate within their grasp, each a weapon to be wielded with precision or cast aside in the heat of battle. [As the countdown commences, the protagonist surveys the winding track ahead, split into two diverging paths, each cloaked in uncertainty.",
    .decision = {
        .question_text = "A decision must be made, a choice that will shape the course of destiny. Will they veer left, towards the path less traveled, or right, where the shadows writhe with hidden dangers?",
        .option = {"Left path", "Right path"},
        .number_options = 2
    }
};

// Initialize the enemies for the left path of scenario 1
Enemy leftPathEnemies[MAX_ENEMIES] = {
    {
        .name = "Shadow Stalker",
        .points = {0, 0, 0},
        .num_skills = 0 // No skills for now
    },
    {
        .name = "Thorn Strangle",
        .points = {0, 0, 0},
        .num_skills = 0 // No skills for now
    }
};

// Initialize the enemies for the right path of scenario 1
Enemy rightPathEnemies[MAX_ENEMIES] = {
    {
        .name = "Inferno Fiend",
        .points = {0, 0, 0},
        .num_skills = 0 // No skills for now
    }
};

// Initialize the second scenario
Scenario scenario2 = {
    .name = "The Crossroads of Destiny",
    .description = "As the protagonist's vehicle hurtles down the track, they approach a fork in the road, each path shrouded in its own mystery and peril. The decision they make now will shape the course of their journey, determining not only the challenges they face but also the fate of those who stand in their way. The protagonist must choose between two diverging paths:",
    .decision = {
        .question_text = "With the fate of their journey hanging in the balance, the protagonist must choose their path wisely. Do they venture into the depths of the Forgotten Ruins, where ancient mysteries await, or brave the tempestuous waters of the Stormy Seas, risking life and limb for the promise of untold rewards?",
        .option = {"The Forgotten Ruins", "The Stormy Seas"},
        .number_options = 2
    }
};

// Initialize enemies for the Forgotten Ruins
Enemy guardianOfTheRuins = {
    .name = "The Guardian of the Forgotten Ruins",
    .points = {0, 0, 0},
    .num_skills = 0 // No skills for now
};

// Initialize enemies for the Stormy Seas
Enemy seaMarauders[MAX_ENEMIES] = {
    {
        .name = "Captain Blackbeard",
        .points = {0, 0, 0},
        .num_skills = 0 // No skills for now
    },
    {
        .name = "Siren the Sorceress",
        .points = {0, 0, 0},
        .num_skills = 0 // No skills for now
    }
};



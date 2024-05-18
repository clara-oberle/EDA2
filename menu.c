#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"
#include "init_character_skills.h"
#include "init_character_skills.c"
#include "init_scenarios.h"
#include "init_scenarios.c"
#include "init_enemy_skills.h"
#include "init_enemy_skills.c"
#include "fight_system.h"
#include "fight_system.c"

int main(){
    // Menu:
    printf("Do you wish to start a new game? (Y/N): ");
    char new_game[N];
    scanf("%s", new_game);
    // Check if input is valid
    while(strcmp(new_game, "Y") != 0 && strcmp(new_game, "N") != 0){
        printf("Invalid input.\n");
        printf("Do you wish to start a new game? (Y/N): ");
        scanf("%s", new_game);
    }
    // Start new game
    if(strcmp(new_game, "Y") == 0){
        // Storyline Intro
        printf("\nThe screen fades from black to reveal a dimly lit chamber, ancient runes etched into the walls "
        "flickering with an otherworldly glow. A haunting melody echoes in the background, sending shivers down "
        "the spine of those who dare to listen. The words 'The Quest for the Sacred Gemstones' materialize in "
        "ethereal script.\n\nWelcome, seeker of destiny, to The Quest for the Sacred Gemstones. In the realm of "
        "shadows and whispers, where the fabric of reality bends to the will of the unknown, only the worthy shall "
        "prevail.\n\nThe ultimate prize awaits the one who dares to embark on this journey: The Sacred Gemstones, three "
        "ancient relics, each bestowing power over a unique aspect of existence - time, space, and spirituality. "
        "Possession of these gems allows the bearer to navigate the flow of time, traverse the boundless expanse of "
        "space, and commune with the depths of the spiritual realm. But to claim them, you must prove your worth by "
        "conquering the four challenges that await within this ethereal realm.\n\nThe first three challenges will reveal "
        "fragments of a riddle that you must solve to uncover the location of the gemstones, which you shall retrieve "
        "in the final trial.\nEnter, brave soul, and heed the call of destiny. The Quest for the Sacred Gemstones awaits "
        "those who dare to seek enlightenment amidst the shadow.\n\n");

        // Create character
        Character *new_character = (Character*)malloc(sizeof(Character)); // Dynamic memory allocation for character structure
        printf("Create your character\nName: ");
        char name[N];
        scanf("%s", name);
        strcpy(new_character->name, name);
        new_character->points[0] = 400; // HP
        new_character->points[1] = 40; // ATK
        new_character->points[2] = 20; // DEF
        printf("\nWelcome %s! You have:\n- %d health points (HP)\n- %d attack points (ATK)\n- %d defence points (DEF)\n"
        "They will regenerate at the start of each battle.\n", new_character->name, new_character->points[0], 
        new_character->points[1], new_character->points[2]);
        
        // Choose 4 skills
        // Initialise the skills:
        Skill *shadow_blade = (Skill*)malloc(sizeof(Skill));
        init_shadowblade(shadow_blade);
        Skill *frostbite = (Skill*)malloc(sizeof(Skill));
        init_frostbite(frostbite);
        Skill *health_exchange = (Skill*)malloc(sizeof(Skill));
        init_health_exchange(health_exchange);
        Skill *fireball = (Skill*)malloc(sizeof(Skill));
        init_fireball(fireball);
        Skill *healing_aura = (Skill*)malloc(sizeof(Skill));
        init_healing_aura(healing_aura);
        Skill *thunderbolt = (Skill*)malloc(sizeof(Skill));
        init_thunderbolt(thunderbolt);
        Skill *time_warp = (Skill*)malloc(sizeof(Skill));
        init_time_warp(time_warp);

        init_character_skills(new_character, shadow_blade, frostbite, 
                              health_exchange, fireball, healing_aura, thunderbolt, time_warp);
    }
    return 0;
}

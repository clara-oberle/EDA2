#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"
#include "init_character_skills.h"
#include "init_scenarios.h"
#include "init_character_skills.c"
#include "init_scenarios.c"

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
        Skill *shadow_blade = init_shadowblade();
        Skill *frostbite = init_frostbite();
        Skill *health_exchange = init_health_exchange();
        Skill *fireball = init_fireball();
        Skill *healing_aura = init_healing_aura();
        Skill *thunderbolt = init_thunderbolt();
        Skill *time_warp = init_time_warp();

        // Let the player preview the skills (see a description of each before choosing)
        printf("\nIt is time to select the four skills that will help you battle your way through this quest. Choose "
        "wisely for your fate relies on them. You can view a description of each skill before selecting it using the menu below:\n"
        "1. Shadowblade strike\n2. Frostbite\n3. Health exchange\n4. Fireball\n5. Healing Aura\n6. ThunderBolt\n7. Time Warp\n");
        printf("\nEnter the number of the skill you wish to preview. When you are done previewing them enter -1: ");
        int skill_preview;
        scanf("%d", &skill_preview);
        while(skill_preview != -1){
            switch(skill_preview){
            case 1:
                printf("- %s:\n%s\n", shadow_blade->name, shadow_blade->description);
                break;
            case 2:
                printf("- %s:\n%s\n", frostbite->name, frostbite->description);
                break;
            case 3:
                printf("- %s:\n%s\n", health_exchange->name, health_exchange->description);
                break;
            case 4:
                printf("- %s:\n%s\n", fireball->name, fireball->description);
                break;
            case 5:
                printf("- %s:\n%s\n",healing_aura ->name, healing_aura->description);
                break;
            case 6:
                printf("- %s:\n%s\n",thunderbolt->name, thunderbolt->description);
                break;
            case 7:
                printf("- %s:\n%s\n", time_warp->name, time_warp->description);
                break;
            default: // In case the input is not a number in the menu
                printf("Invalid input\n");
            }
            printf("\nEnter the number of the skill you wish to preview. When you are done previewing them enter -1: ");
            scanf("%d", &skill_preview);
        }

        // Assigning the skills of the character:
        printf("\nNow that you have become familiar with the available skills. Enter the number of the skill that "
        "you wish to have:\n");
        for(int i=0; i<4; ++i){
            int selected_skill;
            printf("Skill %d: ", i+1);
            scanf("%d", &selected_skill);
            while(selected_skill < 1 || selected_skill > 7){
                //while the selected skill is not a number from 1 to 7, print error
                printf("Invalid input. Enter the number of the skill (from 1 to 7)");
                scanf("%d", &selected_skill);
            }
            switch(selected_skill){
                case 1:
                    new_character->skills[i] = *shadow_blade;
                    break;
                case 2:
                    new_character->skills[i] = *frostbite;
                    break;
                case 3:
                    new_character->skills[i] = *health_exchange;
                    break;
                case 4:
                    new_character->skills[i] = *fireball;
                    break;
                case 5:
                    new_character->skills[i] = *healing_aura;
                    break;
                case 6:
                    new_character->skills[i] = *thunderbolt;
                    break;
                case 7:
                    new_character->skills[i] = *time_warp;
                    break;
            }
        }
        printf("\nThe skills you have chosen are:\n");
        for(int i=0; i<4; i++){
            printf("- %s\n", new_character->skills[i].name);
        }
        printf("Good Luck!\n");
    } 
    return 0;
}

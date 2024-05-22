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
#include "graphs.h"


/*unit test suite: to code a function to check if the functions of the code work
end to end test suite: a function to test all the other unit tests suites
*/

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

        // Initialize scenarios
        Scenario *scenario1 = (Scenario*)malloc(sizeof(Scenario));
        init_scenario1(scenario1);
        Scenario *scenario2 = (Scenario*)malloc(sizeof(Scenario));
        init_scenario2(scenario2);
        Scenario *scenario3 = (Scenario*)malloc(sizeof(Scenario));
        init_scenario3(scenario3);
        Scenario *scenario4 = (Scenario*)malloc(sizeof(Scenario));
        init_scenario4(scenario4);

        // Track completed scenarios
        bool completed_scenarios[4] = {false, false, false, false};
        completed_scenarios[0] = true; // First scenario is always completed first

        // Current scenario pointer
        Scenario *current_scenario = scenario1;

        // Game loop for navigating scenarios
        while (current_scenario) {
            printf("You are now in: %s\n", current_scenario->name);
            printf("%s\n", current_scenario->description);

            Decision *decision = current_scenario->decision;
            if (decision) {
                printf("%s\n", decision->question_text);
                for (int i = 0; i < decision->num_options; i++) {
                    printf("%d: %s\n", i + 1, decision->options_list[i].response_text);
                }
                int choice;
                scanf("%d", &choice);
                if (choice >= 1 && choice <= decision->num_options) {
                    Option chosen_option = decision->options_list[choice - 1];
                    printf("%s\n", chosen_option.narrative_text_before);

                    // Call a battle for each enemy in the chosen option:
                    for(int i=0; i<chosen_option.num_enemies; i++){
                        // initialise the queue to decide the turns, the queue for skills with duration > 1, and the stack to store player's used skills
                        FightQueue *fight_queue = create_queue(new_character, &chosen_option.enemies[i]);
                        OverlapQueue *overlap_queue = (OverlapQueue*)malloc(sizeof(OverlapQueue));
                        init_overap_queue(overlap_queue);
                        SkillStack *player_used_skills = (SkillStack*)malloc(sizeof(SkillStack));
                        player_used_skills->top = -1;
                        // do the battle and return wether the player has won (win = true) or lost (win = false):
                        bool win = battle(new_character, &chosen_option.enemies[i], fight_queue, overlap_queue, player_used_skills);
                    }
                    printf("%s\n", chosen_option.narrative_text_after);
                } else {
                    printf("Invalid choice. Try again.\n");
                    continue;
                }
            }

            // Move to the next scenario
            if (current_scenario == scenario1) {
                // From the first scenario, choose between second and third
                printf("Choose your next scenario:\n");
                printf("1: %s\n", scenario2->name);
                printf("2: %s\n", scenario3->name);
                int next_choice;
                scanf("%d", &next_choice);
                if (next_choice == 1) {
                    current_scenario = scenario2;
                    completed_scenarios[1] = true;
                } else if (next_choice == 2) {
                    current_scenario = scenario3;
                    completed_scenarios[2] = true;
                } else {
                    printf("Invalid choice. Try again.\n");
                    continue;
                }
            } else if (current_scenario == scenario2 || current_scenario == scenario3) {
                // After completing either second or third, check if both are done
                if (completed_scenarios[1] && completed_scenarios[2]) {
                    current_scenario = scenario4;
                } else {
                    // Choose the other middle scenario
                    if (!completed_scenarios[1]) {
                        current_scenario = scenario2;
                        completed_scenarios[1] = true;
                    } else {
                        current_scenario = scenario3;
                        completed_scenarios[2] = true;
                    }
                }
            } else {
                // Last scenario, end the game
                break;
            }
        }
        printf("Congratulations! You have completed the game.\n");
    }
    return 0;
}
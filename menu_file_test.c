#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"
#include "init_character_skills.h"
#include "init_character_skills.c"
#include "init_scenarios_test.h"
#include "init_scenarios_test.c"
#include "init_enemy_skills.h"
#include "init_enemy_skills.c"
#include "fight_system.h"
#include "fight_system.c"
#include "graphs.h"
#include "graphs.c"

/*
- finish errors init scenarios + comments 
- change graphs (1 - 2 h) (data structures --> Names + last scenario check)
- function to know which scenario to initialize
- adapt menu for graphs
- MAYBE unit test suite
- Time strike
*/

/*unit test suite: to code a function to check if the functions of the code work
end to end test suite: a function to test all the other unit tests suites
*/

void print_intro(){
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
}

int main(){
    // Menu:
    printf("\nDo you wish to start a new game? (Y/N): ");
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
        print_intro();

        // Create character
        Character *new_character = (Character*)malloc(sizeof(Character)); // Dynamic memory allocation for character structure
        printf("Create your character\nName: ");
        char name[N];
        scanf("%s", name);
        strcpy(new_character->name, name);
        new_character->points[0] = 400; // HP
        new_character->points[1] = 40; // ATK
        new_character->points[2] = 20; // DEF
        printf("\nWelcome %s! You have:\n- %.2f health points (HP)\n- %.2f attack points (ATK)\n- %.2f defence points (DEF)\n"
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

        printf_battle_specifications(); // print useful information about the battles;

        // Initialize scenarios
        Scenario *scenario1 = (Scenario*)malloc(sizeof(Scenario));
        initialize_scenario1_from_file(scenario1, "race_of_shadows.txt");

        // Initialize graph
        Graph *graph = create_graph(4);
        //add the four scenarios as nodes
        add_scenario(graph, "The Race of Shadows");
        add_scenario(graph, "The Crossroads of Destiny");
        add_scenario(graph, "Abandoned Castle");
        add_scenario(graph, "The Battle for the Gemstones");

        //add edges between the nodes. You can travel from:
        /*Scenario 1 to scenario 2 or 3
        Scenario 2 to scenario 3 and 4 (only if completed 3)
        Scenario 3 to scenario 2 and 4 (only if comleted 2)
        Scenario 4 nowhere*/
        
        add_edge(graph, "The Race of Shadows", "The Crossroads of Destiny");
        add_edge(graph, "The Race of Shadows", "Abandoned Castle");
        add_edge(graph, "The Crossroads of Destiny", "Abandoned Castle");
        add_edge(graph, "The Crossroads of Destiny", "The Battle for the Gemstones");
        add_edge(graph, "Abandoned Castle", "The Crossroads of Destiny");
        add_edge(graph, "Abandoned Castle", "The Battle for the Gemstones");

        //inform the player the possible routes
        printf("Scenario Navigation:\n");
        printGraph(graph);

        // Track completed scenarios
        bool completed_scenarios[4] = {false, false, false, false};
        //completed_scenarios[0] = true; // First scenario is always completed first

        // Current scenario pointer
        Scenario *current_scenario = scenario1;

        //we'll assume the player has won, when they lose, this variable will be false
        bool won = true; // variable used to know if player has won or lost, after the while loop

        // Game loop for navigating scenarios
        //While the fourth scenario is not completed
        while (completed_scenarios[3] != true) {
            printf("bleh\nYou are now in: %s\n", current_scenario->name);
            printf("----------------------------------------------\n");
            printf("%s\n", current_scenario->description);

            Decision *decision = current_scenario->decision;
            if (decision != NULL) {
                printf("\n%s", current_scenario->decision->question_text);
                char answer[N];
                int choice;
                // check if it is the last scenario
                if(strcmp(current_scenario->name, "The Battle for the Gemstones") == 0 ){
                    // input the answer to the riddle
                    scanf("%s", answer);
                    choice = 1; // there is only one option: to enter the final battle
                    while(strcmp(answer, "e") != 0){ // while the answer is not correct
                        printf("Wrong answer! Try again (remember it has to be lowercase): ");
                        scanf("%s", answer);
                    }
                }
                else{
                    strcpy(answer, "e"); // since it is not the last scenario make the defualt for the answer the correct one
                    scanf("%d", &choice); // choose between left (1) or right (2)
                }
                //while the choice is not correct (must be between 1 and 4)
                while (choice < 1 && choice > decision->num_options){
                    printf("Invalid choice. Try again.\n%s", current_scenario->decision->question_text);
                    strcpy(answer, "e"); // since it is not the last scenario make the defualt for the answer the correct one
                    scanf("%d", &choice); // choose between left (1) or right (2)
                }
               
                Option *chosen_option = decision->options_list[choice-1];
                printf("\n%s\n", chosen_option->response_text);
                printf("\n%s\n", chosen_option->narrative_text_before);

                // Call a battle for each enemy in the chosen option here
                bool win_battle;
                for(int i=0; i<chosen_option->num_enemies; i++){
                    // initialise the queue to decide the turns, the queue for skills with duration > 1, and the stack to store player's used skills
                    FightQueue *fight_queue = create_queue(new_character, chosen_option->enemies[i]);
                    OverlapQueue *overlap_queue = (OverlapQueue*)malloc(sizeof(OverlapQueue));
                    init_overlap_queue(overlap_queue);
                    SkillStack *player_used_skills = (SkillStack*)malloc(sizeof(SkillStack));
                    player_used_skills->top = -1;
                    win_battle = battle(new_character, chosen_option->enemies[i], fight_queue, overlap_queue, player_used_skills);
                    free(fight_queue);
                    free(overlap_queue);
                    free(player_used_skills);
                    reset_player_points(new_character); // reset the player's points ready for the next fight
                    if(win_battle == false){ // if the player looses a fight with one of the enemies they cannot continue to fight the next enemy
                        won = false;
                        break; // exit the for loop 
                    }
                }
                /*
                When fights end, in case of victory, the player is prompted with the next scene and its narrative. 
                On the contrary, in case of defeat, the player is prompted with the ability to restart the game or 
                restart the scenario.
                */
                if(win_battle == false){
                    printf("Do you wish to end the game (1) or restart the scenario (2)?: ");
                    int restart;
                    scanf("%d", &restart);
                    while(1 > restart && restart > 2){
                        printf("Invalid input, either 1 or 2: ");
                        scanf("%d", &restart);
                    }
                    if(restart == 1){
                        free_scenario(current_scenario);
                        completed_scenarios[3] = true;
                    } else{
                        //wants to restart scenario, hence, we leave current scenario as it is
                        continue;
                    }
                }
                else{
                    printf("\n%s\n", chosen_option->narrative_text_after);
                    //to update the completed scenario
                    //find the index of the scenario in the graph's adj_list:
                    int index;
                    for(int i=0; i<graph->num_scenarios; i++){
                        if(strcmp(graph->adj_list[i]->name, current_scenario->name) == 0){
                            index = i;
                            break;
                        }
                    }
                    //update the completed_scenarios array using the index:
                    completed_scenarios[index] = true;
                    //if the last scenario has been completed, the while loop will stop
                    //if not, navigate to the next scenario
                    navigate_scenarios(graph, current_scenario); 
                    printf("%s\n, hey\n", current_scenario->name);
                }
            }
        }
        if(won == false){
            printf("\nGame Over!\n");
        } else{
            printf("\nCongratulations! You have completed the game.\n");
        }
    }
}
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
#include "graph.h"


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
        Scenario *scenario1 = init_scenario1();
        Scenario *scenario2 = init_scenario2();
        Scenario *scenario3 = init_scenario3();
        Scenario *scenario4 = init_scenario4();

        // Create the graph to represent the scenarios
        int num_scenarios = 4;
        Graph *graph = create_graph(num_scenarios);

        graph->adj_list[0] = (GraphNode*)malloc(sizeof(GraphNode));
        graph->adj_list[0]->scenario = scenario1;
        graph->adj_list[1] = (GraphNode*)malloc(sizeof(GraphNode));
        graph->adj_list[1]->scenario = scenario2;
        graph->adj_list[2] = (GraphNode*)malloc(sizeof(GraphNode));
        graph->adj_list[2]->scenario = scenario3;
        graph->adj_list[3] = (GraphNode*)malloc(sizeof(GraphNode));
        graph->adj_list[3]->scenario = scenario4;

        add_edge(graph, 0, 1);
        add_edge(graph, 1, 2);
        add_edge(graph, 2, 3);

        // Current scenario pointer
        GraphNode *current_node = graph->adj_list[0];

        // Game loop for navigating scenarios
        while (current_node) {
            printf("You are now in: %s\n", current_node->scenario->name);
            printf("%s\n", current_node->scenario->description);

            Decision *decision = current_node->scenario->decision;
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

                    // Here, you could call a battle function with new_character and chosen_option.enemies

                    printf("%s\n", chosen_option.narrative_text_after);
                } else {
                    printf("Invalid choice. Try again.\n");
                    continue;
                }
            }

            // Move to the next scenario (for now, just move linearly through the graph)
            current_node = current_node->next;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"
#include "init_character_skills.h"
#include "init_character_skills.c"
#include "init_scenarios.h"
#include "init_scenarios.c"
#include "fight_system.c"
#include "fight_system.h"
#include "init_enemy_skills.h"
#include "init_enemy_skills.c"

int main(){
    Skill *thunder_bolt = (Skill*)malloc(sizeof(Skill));
    init_thunderbolt(thunder_bolt);
    Skill *frostbite = (Skill*)malloc(sizeof(Skill));
    init_frostbite(frostbite);
    Skill *health_exchange = (Skill*)malloc(sizeof(Skill));
    init_health_exchange(health_exchange);
    Skill *fireball = (Skill*)malloc(sizeof(Skill));
    init_fireball(fireball);

    Skill *shadow_strike = (Skill*)malloc(sizeof(Skill));
    init_shadow_strike(shadow_strike);
    Skill *evasive_maneuver = (Skill*)malloc(sizeof(Skill));
    init_evasive_maneuver(evasive_maneuver);
    Skill *cloak_of_darkness = (Skill*)malloc(sizeof(Skill));
    init_cloak_of_darkness(cloak_of_darkness);

    Character *new_character = (Character*)malloc(sizeof(Character));
    strcpy(new_character->name, "Player1");
    new_character->points[0] = 400; // HP
    new_character->points[1] = 40; // ATK
    new_character->points[2] = 20; // DEF
    new_character->skills[0] = *thunder_bolt;
    new_character->skills[1] = *frostbite;
    new_character->skills[2] = *health_exchange;
    new_character->skills[3] = *fireball;

    Enemy *new_enemy = (Enemy*)malloc(sizeof(Enemy));
    strcpy(new_enemy->name, "Enemy1");
    new_enemy->points[0] = 250;
    new_enemy->points[1] = 20;
    new_enemy->points[2] = 10;
    new_enemy->skills[0] = *shadow_strike;
    new_enemy->skills[1] = *evasive_maneuver;
    new_enemy->skills[2] = *cloak_of_darkness;

    FightQueue *fight_queue = create_queue(new_character, new_enemy);
    OverlapQueue *overlap_queue = (OverlapQueue*)malloc(sizeof(OverlapQueue));
    init_overlap_queue(overlap_queue);
    SkillStack *player_used_skills = (SkillStack*)malloc(sizeof(SkillStack));
    player_used_skills->top = -1;

    printf("fight queue size: %d\n", fight_queue->size);
    while(fight_queue->size != 0){ // check that the queue is not empty
        printf("Check win: %d\n", check_win(new_character, new_enemy));
        if(check_win(new_character, new_enemy) == -1){ // if they both still have HP
            printf("Fighter: %d\n", fight_queue->first->type);
            if(fight_queue->first->type == 0){ // character's turn
                int skill_number;
                printf("Skills:\n1- Thunder Bolt\n2- Frost bite\n"
                "3- Health exchange\n4- Fire ball\nEnter the number of the chosen skill: ");
                scanf("%d", &skill_number);
                Skill *chosen_skill = (Skill*)malloc(sizeof(Skill));
                init_skill_copy(chosen_skill, &new_character->skills[skill_number-1]);
                printf("One time skill: %d\n", one_time_skill(chosen_skill, player_used_skills));
                while(one_time_skill(chosen_skill, player_used_skills) == true){
                    free_skill_copy(chosen_skill);
                    printf("This skill can only be used once during the battle and it has already been used."
                    "Choose a different skill: ");
                    scanf("%d", &skill_number);
                    Skill *chosen_skill = (Skill*)malloc(sizeof(Skill));
                    init_skill_copy(chosen_skill, &new_character->skills[skill_number-1]);
                }
                printf("Find in queue: %d\n", find_in_queue(chosen_skill, overlap_queue));
                while(find_in_queue(chosen_skill, overlap_queue) == true){
                    free_skill_copy(chosen_skill);
                    printf("This skill still has duration turns left. Choose a different skill: ");
                    scanf("%d", &skill_number);
                    Skill *chosen_skill = (Skill*)malloc(sizeof(Skill));
                    init_skill_copy(chosen_skill, &new_character->skills[skill_number-1]);
                }
                printf("Chosen skill: %s\n", chosen_skill->name);
                printf("Enemy HP before: %f\n", new_enemy->points[0]);
                implement_player_skill(chosen_skill, new_character, new_enemy, overlap_queue, player_used_skills);
                printf("Enemy HP after: %f\n", new_enemy->points[0]);
                if(chosen_skill->duration_turn > 0){
                    enqueue_overlap_skill(overlap_queue, chosen_skill, 0);
                } else{
                    free(chosen_skill);
                }
                printf("Overlap queue at the end of the turn:\n");
                print_overlap_queue(overlap_queue);
            }else if(fight_queue->first->type == 1){ // enemy's turn
                Skill *random_skill = (Skill*)malloc(sizeof(Skill));
                srand(time(NULL)); // initialize random number generator with current time
                int index = generate_random_index();
                printf("Chosen skill index: %d\n", index);
                init_skill_copy(random_skill, &new_enemy->skills[index]);
                printf("Find in queue: %d\n", find_in_queue(random_skill, overlap_queue));
                while(find_in_queue(random_skill, overlap_queue) == true){
                    free_skill_copy(random_skill);
                    int index = generate_random_index();
                    init_skill_copy(random_skill, &new_enemy->skills[index]);
                }
                printf("Chosen skill: %s\n", random_skill->name);
                printf("Player HP before: %f\n", new_character->points[0]);
                implement_enemy_skill(random_skill, new_character, new_enemy, overlap_queue);
                printf("Player HP after: %f\n", new_character->points[0]);
                if(random_skill->duration_turn > 0){
                    enqueue_overlap_skill(overlap_queue, random_skill, 1);
                } else{
                    free_skill_copy(random_skill);
                }
            }
        } else if(check_win(new_character, new_enemy) == 0){
            printf("You win!\n");
        } else if(check_win(new_character, new_enemy) == 1){
            printf("You loose\n");
        }
        dequeue(fight_queue);
    }
    printf("Size of fight queue: %d\n", fight_queue->size);
    if(check_win(new_character, new_enemy) == -1){
        printf("You loose\n");
    }
}

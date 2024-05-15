#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"
#include "init_character_skills.h"
#include "init_scenarios.h"
#include "init_character_skills.c"
#include "init_scenarios.c"
#include "fight_system.c"
#include "fight_system.h"

int main(){
    Skill *thunder_bolt = init_thunderbolt();
    Skill *frostbite = init_frostbite();
    Skill *health_exchange = init_health_exchange();
    Skill *fireball = init_fireball();

    Skill *shadow_strike = init_shadow_strike();
    Skill *evasive_maneuver = init_evasive_maneuver();
    Skill *cloak_of_darkness = init_cloak_of_darkness();

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
    SkillStack *player_used_skills = (SkillStack*)malloc(sizeof(SkillStack));
    player_used_skills->top = -1;

    while(fight_queue->size != 0){ // check that the queue is not empty
        if(check_win(new_character, new_enemy) == -1){ // if they both still have HP
            if(fight_queue->first->type == 0){ // character's turn
                int skill_number;
                printf("Skills:\n1- Shadow blade\n2- Energy barrier\n"
                "3- Health exchange\n4- Fire ball\nEnter the number of the chosen skill: ");
                scanf("%d", &skill_number);
                Skill *chosen_skill = (Skill*)malloc(sizeof(Skill));
                init_skill_copy(chosen_skill, &new_character->skills[skill_number-1]);
                while(one_time_skill(chosen_skill, player_used_skills) == true){
                    free_skill_copy(chosen_skill);
                    printf("This skill can only be used once during the battle and it has already been used."
                    "Choose a different skill: ");
                    scanf("%d", &skill_number);
                    Skill *chosen_skill = (Skill*)malloc(sizeof(Skill));
                    init_skill_copy(chosen_skill, &new_character->skills[skill_number-1]);
                }
                while(find_in_queue(chosen_skill, overlap_queue) == true){
                    free_skill_copy(chosen_skill);
                    printf("This skill still has duration turns left. Choose a different skill: ");
                    scanf("%d", &skill_number);
                    Skill *chosen_skill = (Skill*)malloc(sizeof(Skill));
                    init_skill_copy(chosen_skill, &new_character->skills[skill_number-1]);
                }
                implement_player_skill(chosen_skill, new_character, new_enemy, overlap_queue, player_used_skills);
                if(chosen_skill->duration_turn > 0){
                    enqueue_overlap_skill(overlap_queue, chosen_skill, 0);
                } else{
                    free_skill_copy(chosen_skill);
                }
            }else if(fight_queue->first->type == 1){ // enemy's turn
                Skill *random_skill = (Skill*)malloc(sizeof(Skill));
                int index = generate_random_index();
                init_skill_copy(random_skill, &new_enemy->skills[index]);
                while(find_in_queue(random_skill, overlap_queue) == true){
                    free_skill_copy(random_skill);
                    int index = generate_random_index();
                    init_skill_copy(random_skill, &new_enemy->skills[index]);
                }
                implement_enemy_skill(random_skill, new_character, new_enemy, overlap_queue);
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
    if(check_win(new_character, new_enemy) == -1){
        printf("You loose\n");
    }
}

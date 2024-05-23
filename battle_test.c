#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"
#include "init_character_skills.h"
#include "init_character_skills.c"
#include "init_enemy_skills.h"
#include "init_enemy_skills.c"
#include "fight_system.h"
#include "fight_system.c"

int main(){
    Character *new_character = (Character*)malloc(sizeof(Character)); // Dynamic memory allocation for character structure
    strcpy(new_character->name, "Player");
    new_character->points[0] = 400; // HP
    new_character->points[1] = 40; // ATK
    new_character->points[2] = 20; // DEF

    new_character->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *thunder_bolt = new_character->skills[0];
    init_thunderbolt(thunder_bolt);
    new_character->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *frostbite = new_character->skills[1];
    init_frostbite(frostbite);
    new_character->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *health_exchange = new_character->skills[2];
    init_health_exchange(health_exchange);
    new_character->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *fireball = new_character->skills[3];
    init_fireball(fireball);

    Enemy *enemy1 = (Enemy*)malloc(sizeof(Enemy));
    strcpy(enemy1->name, "Enemy1");
    enemy1->points[0] = 400;
    enemy1->points[1] = 40;
    enemy1->points[2] = 20;

    enemy1->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike = enemy1->skills[0];
    init_shadow_strike(shadow_strike);
    enemy1->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast = enemy1->skills[1];
    init_arcane_blast(arcane_blast);
    enemy1->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash = enemy1->skills[2];
    init_cutlass_slash(cutlass_slash);
    
    FightQueue *fight_queue = create_queue(new_character, enemy1);
    OverlapQueue *overlap_queue = (OverlapQueue*)malloc(sizeof(OverlapQueue));
    init_overlap_queue(overlap_queue);
    SkillStack *player_used_skills = (SkillStack*)malloc(sizeof(SkillStack));
    player_used_skills->top = -1;
    bool win = battle(new_character, enemy1, fight_queue, overlap_queue, player_used_skills);

}
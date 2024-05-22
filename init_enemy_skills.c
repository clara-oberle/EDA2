#include "init_enemy_skills.h"

void init_shadow_strike(Skill *shadow_strike){
    strcpy(shadow_strike->name, "Shadow Strike");
    strcpy(shadow_strike->description, "Deals moderate damage to the player.");
    shadow_strike->type = 0; // Temporary modifier
    shadow_strike->modifier[0] = 1; // HP is unchanged (HP*1)
    shadow_strike->modifier[1] = 1.2; // moderate damage (ATK*1.2)
    shadow_strike->modifier[2] = 1; // DEF is unchanged
    shadow_strike->duration_turn = 1; // modifies ATK points for only that turn
}

void init_evasive_maneuver(Skill *evasive_maneuver){
    strcpy(evasive_maneuver->name, "Evasive Maneuver");
    strcpy(evasive_maneuver->description, "Increases enemy evasion for a single turn.");
    evasive_maneuver->type = 0; // temporal modifier
    evasive_maneuver->modifier[0] = 1; // HP is unchanged
    evasive_maneuver->modifier[1] = 1; // ATK is unchanged
    evasive_maneuver->modifier[2] = 1.5; // increases evasion (DEF*1.5)
    evasive_maneuver->duration_turn = 3; // modifies DEF for the next turn, hence 2 (the current turn + next turn)
}

void init_cloak_of_darkness(Skill *cloak_of_darkness){
    strcpy(cloak_of_darkness->name, "Cloak of Darkness");
    strcpy(cloak_of_darkness->description, "Attack increases by 20 percent and player's DEF decreases by 15 percent for two turns.");
    cloak_of_darkness->type = 0; // temporal modifier
    cloak_of_darkness->modifier[0] = 1; // HP is unchanged
    cloak_of_darkness->modifier[1] = 1.2; // ATK = ATK*1.2 (20% increase)
    cloak_of_darkness->modifier[2] = -0.85; // DEF of player decreases by 15%
    cloak_of_darkness->duration_turn = 2; // lasts 2 turns
}
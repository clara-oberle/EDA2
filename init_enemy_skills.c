#include "init_enemy_skills.h"

//Attack
Skill *init_shadow_strike(){
    Skill *shadow_strike = (Skill*)malloc(sizeof(Skill));
    strcpy(shadow_strike->name, "Shadow Strike");
    strcpy(shadow_strike->description, "Deals moderate damage to the player.");
    shadow_strike->type = 0; // Temporary modifier
    shadow_strike->modifier[0] = 1; // HP is unchanged (HP*1)
    shadow_strike->modifier[1] = 1.2; // moderate damage (ATK*1.2)
    shadow_strike->modifier[2] = 1; // DEF is unchanged
    shadow_strike->duration_turn = 1; // modifies ATK points for only that turn
}

Skill *init_arcane_blast(){
    Skill *arcane_blast = (Skill*)malloc(sizeof(Skill));
    strcpy(arcane_blast->name, "Arcane Blast");
    strcpy(arcane_blast->description, "Unleashes a burst of magical energy towards the player.");
    arcane_blast->type = 0; // temporary modifier
    arcane_blast->modifier[0] = 1; // HP is unchanged
    arcane_blast->modifier[1] = 1.5; // ATK = ATK*1.5
    arcane_blast->modifier[2] = 1; // DEF is unchanged
    arcane_blast->duration_turn = 1; // modifies ATK points for only that turn
    return arcane_blast;
}

Skill *init_cutlass_slash(){
    Skill *cutlass_slash = (Skill*)malloc(sizeof(Skill));
    strcpy(cutlass_slash->name, "Cutlass Slash");
    strcpy(cutlass_slash->description, "Swings cutlass at the player, increasing enemy's attack for one turn");
    cutlass_slash->type = 1; // direct attack
    cutlass_slash->modifier[0] = 1; // 
    cutlass_slash->modifier[1] = 1.3; // ATK 
    cutlass_slash->modifier[2] = 1; // DEF is unchanged
    cutlass_slash->duration_turn = 1; // modifies HP points for only that turn
    return cutlass_slash;
}

//Defense
Skill *init_evasive_maneuver(){
    Skill *evasive_maneuver = (Skill*)malloc(sizeof(Skill));
    strcpy(evasive_maneuver->name, "Evasive Maneuver");
    strcpy(evasive_maneuver->description, "Increases enemy evasion for a single turn.");
    evasive_maneuver->type = 0; // temporal modifier
    evasive_maneuver->modifier[0] = 1; // HP is unchanged
    evasive_maneuver->modifier[1] = 1; // ATK is unchanged
    evasive_maneuver->modifier[2] = 1.5; // increases evasion (DEF*1.5)
    evasive_maneuver->duration_turn = 2; // modifies DEF for the next turn, hence 2 (the current turn + next turn)
    return evasive_maneuver;
}

Skill *init_thorny_veil(){
    Skill *thorny_veil = (Skill*)malloc(sizeof(Skill));
    strcpy(thorny_veil->name, "Thorny Veil");
    strcpy(thorny_veil->description, "Shrouds the enemy in darkness, making them harder to hit and giving them a chance to avoid attacks for one turn.");
    thorny_veil->type = 0; // temporal modifier
    thorny_veil->modifier[0] = 1; // HP is unchanged
    thorny_veil->modifier[1] = 1; // ATK is unchanged
    thorny_veil->modifier[2] = 1.3; // increases evasion
    thorny_veil->duration_turn = 1; // modifies DEF points for the next turn
    return thorny_veil;
}

Skill *init_thorny_veil(){
    Skill *thorny_veil = (Skill*)malloc(sizeof(Skill));
    strcpy(thorny_veil->name, "Thorny Veil");
    strcpy(thorny_veil->description, "Shrouds the enemy in darkness, making them harder to hit and giving them a chance to avoid attacks for one turn.");
    thorny_veil->type = 0; // temporal modifier
    thorny_veil->modifier[0] = 1; // HP is unchanged
    thorny_veil->modifier[1] = 1; // ATK is unchanged
    thorny_veil->modifier[2] = 1.3; // increases evasion
    thorny_veil->duration_turn = 1; // modifies DEF points for the next turn
    return thorny_veil;
}

void init_cloak_of_darkness(Skill *cloak_of_darkness){
    strcpy(cloak_of_darkness->name, "Cloak of Darkness");
    strcpy(cloak_of_darkness->description, "Attack increases by 20 percent and player's DEF decreases by 15 percent for two turns.");
    cloak_of_darkness->type = 0; // temporal modifier
    cloak_of_darkness->modifier[0] = 1; // HP is unchanged
    cloak_of_darkness->modifier[1] = -1; // ATK of player is changed, so that damage = defense - attack is positive
    cloak_of_darkness->modifier[2] = 1; // DEF is unchanged
    cloak_of_darkness->duration_turn = 1; // makes enemy immune for the next turn
    return cloak_of_darkness;
}

//special
Skill *init_vine_bind(){
    Skill *vine_bind = (Skill*)malloc(sizeof(Skill));
    strcpy(vine_bind->name, "Vine Bind");
    strcpy(vine_bind->description, "Traps the player with twisting vines, making them slower and easier to hit for one turn.");
    vine_bind->type = 0; // temporal modifier
    vine_bind->modifier[0] = 1; // HP is unchanged
    vine_bind->modifier[1] = 1.5; // makes player slower == make enemy faster
    vine_bind->modifier[2] = -0.9; // DEF of char is changed
    vine_bind->duration_turn = 1; // modifies speed for only that turn
    return vine_bind;
}

Skill *init_flame_burst(){
    Skill *flame_burst = (Skill*)malloc(sizeof(Skill));
    strcpy(flame_burst->name, "Flame Burst");
    strcpy(flame_burst->description, "Inflicts fire damage over time on the player.");
    flame_burst->type = 1; // direct attack
    flame_burst->modifier[0] = 0.9; // fire damage over time (HP = HP*0.9)
    flame_burst->modifier[1] = 1; // ATK is unchanged
    flame_burst->modifier[2] = 1; // DEF is unchanged
    flame_burst->duration_turn = 3; // reduces HP points every 3 turns
    return flame_burst;
}


Skill *init_healing_wave(){
    Skill *healing_wave = (Skill*)malloc(sizeof(Skill));
    strcpy(healing_wave->name, "Healing Wave");
    strcpy(healing_wave->description, "Sends a wave of healing energy, restoring health to the enemy");
    healing_wave->type = 1; // direct attack
    healing_wave->modifier[0] = 1.3; // restores health HP = HP*1.2
    healing_wave->modifier[1] = 1; // ATK is unchanged
    healing_wave->modifier[2] = 1; // DEF is unchanged
    healing_wave->duration_turn = 1; // modifies HP points for only that turn
    return healing_wave;
}
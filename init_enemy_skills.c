#include "init_enemy_skills.h"
#include "string.h"

//Attack
Skill *init_shadow_strike(Skill *shadow_strike){
    strcpy(shadow_strike->name, "Shadow Strike");
    strcpy(shadow_strike->description, "Deals moderate damage to the player.");
    shadow_strike->type = 0; // temporary modifier
    shadow_strike->modifier[0] = 1; // HP is unchanged (HP*1)
    shadow_strike->modifier[1] = 1.2; // moderate damage (ATK*1.2)
    shadow_strike->modifier[2] = 1; // DEF is unchanged
    shadow_strike->duration_turn = 1; // modifies ATK points for only that turn
    return shadow_strike;
}

Skill *init_arcane_blast(Skill *arcane_blast){
    strcpy(arcane_blast->name, "Arcane Blast");
    strcpy(arcane_blast->description, "Unleashes a burst of magical energy towards the player. Lasts"
    "three turns.");
    arcane_blast->type = 0; // temporary modifier
    arcane_blast->modifier[0] = 1; // HP is unchanged
    arcane_blast->modifier[1] = 1.5; // ATK = ATK*1.5
    arcane_blast->modifier[2] = 1; // DEF is unchanged
    arcane_blast->duration_turn = 3; // modifies ATK points for that turn and the next two (so total 3)
    return arcane_blast;
}

Skill *init_cutlass_slash(Skill *cutlass_slash){
    strcpy(cutlass_slash->name, "Cutlass Slash");
    strcpy(cutlass_slash->description, "Swings cutlass at the player, increasing enemy's attack for two turns.");
    cutlass_slash->type = 0; // temporary modifier
    cutlass_slash->modifier[0] = 1; // 
    cutlass_slash->modifier[1] = 1.3; // ATK increases 30%
    cutlass_slash->modifier[2] = 1; // DEF is unchanged
    cutlass_slash->duration_turn = 2; // modifies ATK points for that turn and the next
    return cutlass_slash;
}

//Defense
Skill *init_evasive_maneuver(Skill *evasive_maneuver){
    strcpy(evasive_maneuver->name, "Evasive Maneuver");
    strcpy(evasive_maneuver->description, "Increases enemy evasion for a single turn.");
    evasive_maneuver->type = 0; // temporal modifier
    evasive_maneuver->modifier[0] = 1; // HP is unchanged
    evasive_maneuver->modifier[1] = 1; // ATK is unchanged
    evasive_maneuver->modifier[2] = 1.5; // increases evasion (DEF*1.5)
    evasive_maneuver->duration_turn = 2; // modifies DEF for the next turn, hence 2 (the current turn + next turn)
    return evasive_maneuver;
}

Skill *init_thorny_veil(Skill *thorny_veil){
    strcpy(thorny_veil->name, "Thorny Veil");
    strcpy(thorny_veil->description, "Shrouds the enemy in darkness, making them harder to hit and giving them a chance to avoid attacks for one turn.");
    thorny_veil->type = 0; // temporal modifier
    thorny_veil->modifier[0] = 1; // HP is unchanged
    thorny_veil->modifier[1] = 1; // ATK is unchanged
    thorny_veil->modifier[2] = 1.3; // increases evasion
    thorny_veil->duration_turn = 2; // modifies DEF for the next turn, hence 2 (the current turn + next turn)
    return thorny_veil;
}

//special
Skill *init_vine_bind(Skill *vine_bind ){
    strcpy(vine_bind->name, "Vine Bind");
    strcpy(vine_bind->description, "Traps the player with twisting vines, making them slower and easier to hit for one turn.");
    vine_bind->type = 0; // temporal modifier
    vine_bind->modifier[0] = 1; // HP is unchanged
    vine_bind->modifier[1] = 1.5; // makes player slower == make enemy faster
    vine_bind->modifier[2] = -0.9; // DEF of player decreases by 10%
    vine_bind->duration_turn = 1; // modifies speed for only that turn
    return vine_bind;
}

Skill *init_flame_burst(Skill *flame_burst){
    strcpy(flame_burst->name, "Flame Burst");
    strcpy(flame_burst->description, "Inflicts fire damage over time on the player.");
    flame_burst->type = 0; // temporal modifier
    flame_burst->modifier[0] = 1; // HP is unchanged
    flame_burst->modifier[1] = 1.6; // ATK = ATK*1.6
    flame_burst->modifier[2] = -0.85; // player's DEF decreases by 15%
    flame_burst->duration_turn = 3; // lasts that turn and the next two (so 3 in total)
    return flame_burst;
}

Skill *init_healing_wave(Skill *healing_wave){
    strcpy(healing_wave->name, "Healing Wave");
    strcpy(healing_wave->description, "Sends a wave of healing energy, restoring health to the enemy");
    healing_wave->type = 1; // direct attack
    healing_wave->modifier[0] = 1.3; // restores health HP = HP*1.3
    healing_wave->modifier[1] = 1; // ATK is unchanged
    healing_wave->modifier[2] = 1; // DEF is unchanged
    healing_wave->duration_turn = 1; // modifies HP points for only that turn
    return healing_wave;
}
#include "init_enemy_skills.h"

//SCENARIO 1 enemy 1 left path
Skill *init_shadow_strike(){
    Skill *shadow_strike = (Skill*)malloc(sizeof(Skill));
    strcpy(shadow_strike->name, "Shadow Strike");
    strcpy(shadow_strike->description, "Deals moderate damage to the playerr.");
    shadow_strike->type = 1; // direct attack
    shadow_strike->modifier[0] = NULL; // HP is unchanged
    shadow_strike->modifier[1] = 1.2; // moderate damage
    shadow_strike->modifier[2] = NULL; // DEF is unchanged
    shadow_strike->duration_turn = 1; // modifies ATK points for only that turn
    return shadow_strike;
}

Skill *init_evasive_maneuver(){
    Skill *evasive_maneuver = (Skill*)malloc(sizeof(Skill));
    strcpy(evasive_maneuver->name, "Evasive Maneuver");
    strcpy(evasive_maneuver->description, "Increases enemy evasion for a single turn.");
    evasive_maneuver->type = 0; // temporal modifier
    evasive_maneuver->modifier[0] = NULL; // HP is unchanged
    evasive_maneuver->modifier[1] = NULL; // ATK is unchanged
    evasive_maneuver->modifier[2] = 1.5; // increases evasion
    evasive_maneuver->duration_turn = 1; // modifies DEF points for only that turn
    return evasive_maneuver;
}

Skill *init_cloak_of_darkness(){
    Skill *cloak_of_darkness = (Skill*)malloc(sizeof(Skill));
    strcpy(cloak_of_darkness->name, "Cloak of Darkness");
    strcpy(cloak_of_darkness->description, "Grants the enemy temporary invisibility, making them immune to player attacks for one turn.");
    cloak_of_darkness->type = 0; // temporal modifier
    cloak_of_darkness->modifier[0] = NULL; // HP is unchanged
    cloak_of_darkness->modifier[1] = NULL; // ATK is unchanged
    cloak_of_darkness->modifier[2] = NULL; // DEF is unchanged
    cloak_of_darkness->duration_turn = 1; // makes enemy immune for only that turn
    return cloak_of_darkness;
}

//SCENARIO 1 enemy 2 left path
Skill *init_vine_bind(){
    Skill *vine_bind = (Skill*)malloc(sizeof(Skill));
    strcpy(vine_bind->name, "Vine Bind");
    strcpy(vine_bind->description, "Traps the player with twisting vines, making them slower and easier to hit for one turn.");
    vine_bind->type = 0; // temporal modifier
    vine_bind->modifier[0] = NULL; // HP is unchanged
    vine_bind->modifier[1] = 0.8; // makes player slower
    vine_bind->modifier[2] = NULL; // DEF is unchanged
    vine_bind->duration_turn = 1; // modifies speed for only that turn
    return vine_bind;
}

Skill *init_thorny_veil(){
    Skill *thorny_veil = (Skill*)malloc(sizeof(Skill));
    strcpy(thorny_veil->name, "Thorny Veil");
    strcpy(thorny_veil->description, "Shrouds the enemy in darkness, making them harder to hit and giving them a chance to avoid attacks for one turn.");
    thorny_veil->type = 0; // temporal modifier
    thorny_veil->modifier[0] = NULL; // HP is unchanged
    thorny_veil->modifier[1] = NULL; // ATK is unchanged
    thorny_veil->modifier[2] = 1.2; // increases evasion
    thorny_veil->duration_turn = 1; // modifies DEF points for only that turn
    return thorny_veil;
}

Skill *init_life_drain(){
    Skill *life_drain = (Skill*)malloc(sizeof(Skill));
    strcpy(life_drain->name, "Life Drain");
    strcpy(life_drain->description, "Drains the player's health, hurting them while healing the enemy a bit with the stolen life force.");
    life_drain->type = 1; // direct attack
    life_drain->modifier[0] = 0.5; // drains player's health
    life_drain->modifier[1] = NULL; // ATK is unchanged
    life_drain->modifier[2] = 0.2; // heals enemy
    life_drain->duration_turn = 1; // modifies HP points for only that turn
    return life_drain;
}

//SCENARIO 1 enemy 1 right PATH
Skill *init_flame_burst(){
    Skill *flame_burst = (Skill*)malloc(sizeof(Skill));
    strcpy(flame_burst->name, "Flame Burst");
    strcpy(flame_burst->description, "Inflicts fire damage over time on the player.");
    flame_burst->type = 1; // direct attack
    flame_burst->modifier[0] = 0.5; // fire damage over time
    flame_burst->modifier[1] = NULL; // ATK is unchanged
    flame_burst->modifier[2] = NULL; // DEF is unchanged
    flame_burst->duration_turn = 3; // reduces HP points every 3 turns
    return flame_burst;
}

Skill *init_infernal_barrier(){
    Skill *infernal_barrier = (Skill*)malloc(sizeof(Skill));
    strcpy(infernal_barrier->name, "Infernal Barrier");
    strcpy(infernal_barrier->description, "Shields the enemy, reducing incoming damage for one turn.");
    infernal_barrier->type = 0; // temporal modifier
    infernal_barrier->modifier[0] = NULL; // HP is unchanged
    infernal_barrier->modifier[1] = NULL; // ATK is unchanged
    infernal_barrier->modifier[2] = 1.5; // reduces damage
    infernal_barrier->duration_turn = 1; // modifies DEF points for only that turn
    return infernal_barrier;
}

Skill *init_heatwave(){
    Skill *heatwave = (Skill*)malloc(sizeof(Skill));
    strcpy(heatwave->name, "Heatwave");
    strcpy(heatwave->description, "Inflicts damage to the player while reducing their defense for one turn.");
    heatwave->type = 1; // direct attack
    heatwave->modifier[0] = 0.8; // inflicts damage
    heatwave->modifier[1] = NULL; // ATK is unchanged
    heatwave->modifier[2] = 0.8; // reduces defense
    heatwave->duration_turn = 1; // modifies HP and DEF points for only that turn
    return heatwave;
}


// SCENARIO 2 left path 
Skill *init_stone_smash(){
    Skill *stone_smash = (Skill*)malloc(sizeof(Skill));
    strcpy(stone_smash->name, "Stone Smash");
    strcpy(stone_smash->description, "The golem smashes the ground with its stone fist, causing damage to the player.");
    stone_smash->type = 1; // direct attack
    stone_smash->modifier[0] = 1.8; // high damage
    stone_smash->modifier[1] = NULL; // ATK is unchanged
    stone_smash->modifier[2] = NULL; // DEF is unchanged
    stone_smash->duration_turn = 1; // modifies ATK points for only that turn
    return stone_smash;
}

Skill *init_arcane_blast(){
    Skill *arcane_blast = (Skill*)malloc(sizeof(Skill));
    strcpy(arcane_blast->name, "Arcane Blast");
    strcpy(arcane_blast->description, "The golem unleashes a burst of magical energy towards the player, dealing damage.");
    arcane_blast->type = 1; // direct attack
    arcane_blast->modifier[0] = 1.5; // moderate damage
    arcane_blast->modifier[1] = NULL; // ATK is unchanged
    arcane_blast->modifier[2] = NULL; // DEF is unchanged
    arcane_blast->duration_turn = 1; // modifies ATK points for only that turn
    return arcane_blast;
}

Skill *init_protective_aura(){
    Skill *protective_aura = (Skill*)malloc(sizeof(Skill));
    strcpy(protective_aura->name, "Protective Aura");
    strcpy(protective_aura->description, "The golem surrounds itself with a protective aura, reducing damage taken for a short time.");
    protective_aura->type = 0; // temporal modifier
    protective_aura->modifier[0] = NULL; // HP is unchanged
    protective_aura->modifier[1] = NULL; // ATK is unchanged
    protective_aura->modifier[2] = 1.5; // reduces damage
    protective_aura->duration_turn = 1; // modifies DEF points for only that turn
    return protective_aura;
}

// SCENARIO 2 right path 
Skill *init_cutlass_slash(){
    Skill *cutlass_slash = (Skill*)malloc(sizeof(Skill));
    strcpy(cutlass_slash->name, "Cutlass Slash");
    strcpy(cutlass_slash->description, "Captain Blackbeard swings his cutlass at the player, dealing damage.");
    cutlass_slash->type = 1; // direct attack
    cutlass_slash->modifier[0] = 1.6; // moderate damage
    cutlass_slash->modifier[1] = NULL; // ATK is unchanged
    cutlass_slash->modifier[2] = NULL; // DEF is unchanged
    cutlass_slash->duration_turn = 1; // modifies ATK points for only that turn
    return cutlass_slash;
}

Skill *init_rapid_dodge(){
    Skill *rapid_dodge = (Skill*)malloc(sizeof(Skill));
    strcpy(rapid_dodge->name, "Evasive Maneuver");
    strcpy(rapid_dodge->description, "Captain Blackbeard quickly dodges, making him harder to hit for a turn.");
    rapid_dodge->type = 0; // temporal modifier
    rapid_dodge->modifier[0] = NULL; // HP is unchanged
    rapid_dodge->modifier[1] = NULL; // ATK is unchanged
    rapid_dodge->modifier[2] = 2; // increases evasion
    rapid_dodge->duration_turn = 1; // modifies DEF points for only that turn
    return rapid_dodge;
}

Skill *init_rally_crew(){
    Skill *rally_crew = (Skill*)malloc(sizeof(Skill));
    strcpy(rally_crew->name, "Rally Crew");
    strcpy(rally_crew->description, "Captain Blackbeard calls for backup, boosting his attack for a turn.");
    rally_crew->type = 0; // temporal modifier
    rally_crew->modifier[0] = NULL; // HP is unchanged
    rally_crew->modifier[1] = 1.5; // increases ATK
    rally_crew->modifier[2] = NULL; // DEF is unchanged
    rally_crew->duration_turn = 1; // modifies ATK points for only that turn
    return rally_crew;
}

Skill *init_storm_strike(){
    Skill *storm_strike = (Skill*)malloc(sizeof(Skill));
    strcpy(storm_strike->name, "Storm Strike");
    strcpy(storm_strike->description, "Siren summons a bolt of lightning to strike the player, causing damage.");
    storm_strike->type = 1; // direct attack
    storm_strike->modifier[0] = 1.2; // moderate damage
    storm_strike->modifier[1] = NULL; // ATK is unchanged
    storm_strike->modifier[2] = NULL; // DEF is unchanged
    storm_strike->duration_turn = 1; // modifies ATK points for only that turn
    return storm_strike;
}

Skill *init_ensnaring_song(){
    Skill *ensnaring_song = (Skill*)malloc(sizeof(Skill));
    strcpy(ensnaring_song->name, "Ensnaring Song");
    strcpy(ensnaring_song->description, "Siren sings a mesmerizing song, immobilizing the player for a turn.");
    ensnaring_song->type = 0; // temporal modifier
    ensnaring_song->modifier[0] = NULL; // HP is unchanged
    ensnaring_song->modifier[1] = NULL; // ATK is unchanged
    ensnaring_song->modifier[2] = NULL; // DEF is unchanged
    ensnaring_song->duration_turn = 1; // immobilizes player for only that turn
    return ensnaring_song;
}

Skill *init_healing_wave(){
    Skill *healing_wave = (Skill*)malloc(sizeof(Skill));
    strcpy(healing_wave->name, "Healing Wave");
    strcpy(healing_wave->description, "Siren sends a wave of healing energy, restoring health to herself or allies.");
    healing_wave->type = 0; // temporal modifier
    healing_wave->modifier[0] = 0.2; // restores health
    healing_wave->modifier[1] = NULL; // ATK is unchanged
    healing_wave->modifier[2] = NULL; // DEF is unchanged
    healing_wave->duration_turn = 1; // modifies HP points for only that turn
    return healing_wave;
}

// SCENARIO 3 LEFT PATH 
Skill *init_shadow_leap(){
    Skill *shadow_leap = (Skill*)malloc(sizeof(Skill));
    strcpy(shadow_leap->name, "Shadow Leap");
    strcpy(shadow_leap->description, "The ghoul swiftly vanishes into the darkness and reappears behind its prey, launching a surprise attack.");
    shadow_leap->type = 1; // direct attack
    shadow_leap->modifier[0] = 1.6; // moderate damage
    shadow_leap->modifier[1] = NULL; // ATK is unchanged
    shadow_leap->modifier[2] = NULL; // DEF is unchanged
    shadow_leap->duration_turn = 1; // modifies ATK points for only that turn
    return shadow_leap;
}

Skill *init_reflective_aura(){
    Skill *reflective_aura = (Skill*)malloc(sizeof(Skill));
    strcpy(reflective_aura->name, "Reflective Aura");
    strcpy(reflective_aura->description, "The ghoul creates a reflective aura, reflecting a portion of incoming attacks back at the attacker.");
    reflective_aura->type = 0; // temporal modifier
    reflective_aura->modifier[0] = NULL; // HP is unchanged
    reflective_aura->modifier[1] = NULL; // ATK is unchanged
    reflective_aura->modifier[2] = 0.5; // reflects damage back at attacker
    reflective_aura->duration_turn = 1; // modifies DEF points for only that turn
    return reflective_aura;
}

Skill *init_soul_grasp(){
    Skill *soul_grasp = (Skill*)malloc(sizeof(Skill));
    strcpy(soul_grasp->name, "Soul Grasp");
    strcpy(soul_grasp->description, "The ghoul extends its claws to grasp at the soul of its prey, draining a portion of their health points.");
    soul_grasp->type = 1; // direct attack
    soul_grasp->modifier[0] = 0.8; // drains health
    soul_grasp->modifier[1] = NULL; // ATK is unchanged
    soul_grasp->modifier[2] = NULL; // DEF is unchanged
    soul_grasp->duration_turn = 1; // modifies ATK points for only that turn
    return soul_grasp;
}

// SCENARIO 3 RIGHT PATH ENEMY 1 
Skill *init_granite_slam(){
    Skill *granite_slam = (Skill*)malloc(sizeof(Skill));
    strcpy(granite_slam->name, "Granite Slam");
    strcpy(granite_slam->description, "The granite guardian smashes the ground with massive fists, causing shockwaves that damage anyone nearby.");
    granite_slam->type = 1; // direct attack
    granite_slam->modifier[0] = 1.8; // high damage
    granite_slam->modifier[1] = NULL; // ATK is unchanged
    granite_slam->modifier[2] = NULL; // DEF is unchanged
    granite_slam->duration_turn = 1; // modifies ATK points for only that turn
    return granite_slam;
}

Skill *init_petrifying_gaze(){
    Skill *petrifying_gaze = (Skill*)malloc(sizeof(Skill));
    strcpy(petrifying_gaze->name, "Petrifying Gaze");
    strcpy(petrifying_gaze->description, "The granite guardian turns the target to stone with a single look, making them unable to do anything in their next turn.");
    petrifying_gaze->type = 0; // temporal modifier
    petrifying_gaze->modifier[0] = NULL; // HP is unchanged
    petrifying_gaze->modifier[1] = NULL; // ATK is unchanged
    petrifying_gaze->modifier[2] = NULL; // DEF is unchanged
    petrifying_gaze->duration_turn = 1; // immobilizes player for only that turn
    return petrifying_gaze;
}

Skill *init_mighty_fortress(){
    Skill *mighty_fortress = (Skill*)malloc(sizeof(Skill));
    strcpy(mighty_fortress->name, "Mighty Fortress");
    strcpy(mighty_fortress->description, "The granite guardian summons a stone barrier to protect itself from the protagonist’s attack.");
    mighty_fortress->type = 0; // temporal modifier
    mighty_fortress->modifier[0] = NULL; // HP is unchanged
    mighty_fortress->modifier[1] = NULL; // ATK is unchanged
    mighty_fortress->modifier[2] = 1.5; // increases defense
    mighty_fortress->duration_turn = 1; // modifies DEF points for only that turn
    return mighty_fortress;
}

//SCENARIO 3 RIGHT PATH ENEMY 2 
Skill *init_venomous_blossoms(){
    Skill *venomous_blossoms = (Skill*)malloc(sizeof(Skill));
    strcpy(venomous_blossoms->name, "Venomous Blossoms");
    strcpy(venomous_blossoms->description, "Deadly Nightshade releases a cloud of toxic spores from its flowers, poisoning anyone nearby.");
    venomous_blossoms->type = 0; // direct attack
    venomous_blossoms->modifier[0] = 0.5; // moderate poison damage
    venomous_blossoms->modifier[1] = NULL; // ATK is unchanged
    venomous_blossoms->modifier[2] = NULL; // DEF is unchanged
    venomous_blossoms->duration_turn = 1; // modifies ATK points for only that turn
    return venomous_blossoms;
}

Skill *init_thorned_barricade(){
    Skill *thorned_barricade = (Skill*)malloc(sizeof(Skill));
    strcpy(thorned_barricade->name, "Thorned Barricade");
    strcpy(thorned_barricade->description, "Deadly Nightshade conjures a barrier of thorns, creating a defensive obstacle against the protagonist’s attack.");
    thorned_barricade->type = 0; // temporal modifier
    thorned_barricade->modifier[0] = NULL; // HP is unchanged
    thorned_barricade->modifier[1] = NULL; // ATK is unchanged
    thorned_barricade->modifier[2] = 2; // increases defense
    thorned_barricade->duration_turn = 1; // modifies DEF points for only that turn
    return thorned_barricade;
}

Skill *init_deadly_vines(){
    Skill *deadly_vines = (Skill*)malloc(sizeof(Skill));
    strcpy(deadly_vines->name, "Deadly Vines");
    strcpy(deadly_vines->description, "Deadly Nightshade lashes out at the protagonist like a deadly whip, inflicting damage to their health.");
    deadly_vines->type = 1; // direct attack
    deadly_vines->modifier[0] = 1.5; // moderate damage
    deadly_vines->modifier[1] = NULL; // ATK is unchanged
    deadly_vines->modifier[2] = NULL; // DEF is unchanged
    deadly_vines->duration_turn = 1; // modifies ATK points for only that turn
    return deadly_vines;
}



// SCENARIO 4 ENEMY 1
Skill *init_time_distortion(){
    Skill *time_distortion = (Skill*)malloc(sizeof(Skill));
    strcpy(time_distortion->name, "Time Distortion");
    strcpy(time_distortion->description, "Creates time distortions, making it harder for enemies to hit.");
    time_distortion->type = 0; // temporal modifier
    time_distortion->modifier[0] = NULL; // HP is unchanged
    time_distortion->modifier[1] = NULL; // ATK is unchanged
    time_distortion->modifier[2] = NULL; // DEF is unchanged
    time_distortion->duration_turn = 2; // affects opponent's accuracy and evasion for 2 turns
    return time_distortion;
}

Skill *init_time_bomb(){
    Skill *time_bomb = (Skill*)malloc(sizeof(Skill));
    strcpy(time_bomb->name, "Time Bomb");
    strcpy(time_bomb->description, "Explodes with time power, dealing damage and weakening enemies' attacks.");
    time_bomb->type = 1; // direct attack
    time_bomb->modifier[0] = 1.5; // moderate damage
    time_bomb->modifier[1] = 0.8; // reduces opponent's attack power
    time_bomb->modifier[2] = NULL; // DEF is unchanged
    time_bomb->duration_turn = 1; // modifies ATK points for only that turn
    return time_bomb;
}

Skill *init_temporal_shift(){
    Skill *temporal_shift = (Skill*)malloc(sizeof(Skill));
    strcpy(temporal_shift->name, "Temporal Shift");
    strcpy(temporal_shift->description, "Shifts through time, increasing evasion.");
    temporal_shift->type = 0; // temporal modifier
    temporal_shift->modifier[0] = NULL; // HP is unchanged
    temporal_shift->modifier[1] = NULL; // ATK is unchanged
    temporal_shift->modifier[2] = 2; // increases evasion
    temporal_shift->duration_turn = 2; // modifies DEF points for 2 turns
    return temporal_shift;
}

// SCENARIO 4 ENEMY 2
Skill *init_space_warp(){
    Skill *space_warp = (Skill*)malloc(sizeof(Skill));
    strcpy(space_warp->name, "Space Warp");
    strcpy(space_warp->description, "Warps space, reducing enemies' accuracy.");
    space_warp->type = 0; // temporal modifier
    space_warp->modifier[0] = NULL; // HP is unchanged
    space_warp->modifier[1] = NULL; // ATK is unchanged
    space_warp->modifier[2] = NULL; // DEF is unchanged
    space_warp->duration_turn = 2; // affects opponent's accuracy for 2 turns
    return space_warp;
}

Skill *init_cosmic_slash(){
    Skill *cosmic_slash = (Skill*)malloc(sizeof(Skill));
    strcpy(cosmic_slash->name, "Cosmic Slash");
    strcpy(cosmic_slash->description, "Slashes with cosmic energy, damaging and weakening enemies' defense.");
    cosmic_slash->type = 1; // direct attack
    cosmic_slash->modifier[0] = 1.6; // moderate damage
    cosmic_slash->modifier[1] = NULL; // ATK is unchanged
    cosmic_slash->modifier[2] = 0.7; // reduces opponent's defense
    cosmic_slash->duration_turn = 1; // modifies DEF points for only that turn
    return cosmic_slash;
}

Skill *init_spatial_shift(){
    Skill *spatial_shift = (Skill*)malloc(sizeof(Skill));
    strcpy(spatial_shift->name, "Spatial Shift");
    strcpy(spatial_shift->description, "Shifts in space, reducing damage received.");
    spatial_shift->type = 0; // temporal modifier
    spatial_shift->modifier[0] = NULL; // HP is unchanged
    spatial_shift->modifier[1] = NULL; // ATK is unchanged
    spatial_shift->modifier[2] = 0.5; // reduces damage received
    spatial_shift->duration_turn = 2; // modifies DEF points for 2 turns
    return spatial_shift;
}





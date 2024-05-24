#include "init_scenarios.h"
#include "init_enemy_skills.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_scenario1(Scenario *race_of_shadows ){
    // Scenario 1 - Race of Shadows
    strcpy(race_of_shadows->name, "The Race of Shadows");
    strcpy(race_of_shadows->description, "As the screen fades from black, you find yourself in a sleek, "
    "futuristic vehicle, its engine's hum reverberating through your bones. Ahead lies the starting line, "
    "bathed in neon lights and echoing with the distant roar of an eager crowd. The Race of Shadows begins, "
    "and your fate hangs in the balance. As the countdown begins, you survey the winding track ahead, split "
    "into two diverging paths, both shrouded in uncertainty.");

    // The decision is whether to take the left or right path:
    // dynamically allocate memory for the decision struct and for the options array inside the decision struct
    Decision *choose_path_race = (Decision*)malloc(sizeof(Decision));
    race_of_shadows->decision = choose_path_race;
    choose_path_race->num_options = 2;
    strcpy(choose_path_race->question_text, "A decision must be made, a choice that will shape the course "
    "of destiny. Will they veer left (1), towards the path less traveled, or right (2), where the shadows writhe "
    "with hidden dangers? Enter the number corresponding to your choice: ");

    // The left path takes the player to the Veil of Obscurity:
    choose_path_race->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *veil_of_obscurity = choose_path_race->options_list[0];
    strcpy(veil_of_obscurity->response_text, "To the left, the Veil of Obscurity looms like a shadowy abyss, "
    "its depths shrouded in mystery. The path winds through a dense forest of gnarled trees and twisting vines, "
    "their branches reaching out like grasping fingers to ensnare the unwary.");
    strcpy(veil_of_obscurity->narrative_text_before, "You steer your vehicle onto the left path, plunging into "
    "the dark and mysterious Veil of Obscurity. The shadows seem to close in around you as you navigate the "
    "winding track.");
    strcpy(veil_of_obscurity->narrative_text_after, "With adrenaline still coursing through your veins, you "
    "navigate your car through the aftermath of the battle. As the dust settles, your eyes catch a glint among "
    "the wreckage. Half-buried beneath the rubble is the first fragment of the riddle, its aged inscription "
    "illuminated by the faint light. A surge of anticipation grips you as you trace the ancient words etched "
    "into the stone, the first piece of the puzzle that will lead you to the final prize.");
    veil_of_obscurity->num_enemies = 2;

    // The enemies in the Veil of Obscurity:
    veil_of_obscurity->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *shadow_stalker = veil_of_obscurity->enemies[0];
    strcpy(shadow_stalker->name, "Shadow Stalker");
    shadow_stalker->points[0] = 250; // HP
    shadow_stalker->points[1] = 30; // ATK
    shadow_stalker->points[2] = 10; // DEF

    //initialize enemy skills of shadow stalker
    //We create a pointer to the skill that it's initialized and then, we add this skill to the array.
    //Lastly, we free the pointer. This is done for every skill of every enemy
    shadow_stalker->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike = shadow_stalker->skills[0];
    init_shadow_strike(shadow_strike);

    shadow_stalker->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver = shadow_stalker->skills[1];
    init_evasive_maneuver(evasive_maneuver);

    shadow_stalker->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst = shadow_stalker->skills[2];
    init_flame_burst(flame_burst);

    shadow_stalker->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast = shadow_stalker->skills[3];
    init_arcane_blast(arcane_blast);

    // next enemy in the veil of obscruity
    veil_of_obscurity->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *thorn_strangle = veil_of_obscurity->enemies[1];
    strcpy(thorn_strangle->name, "Thorn Strangle");
    thorn_strangle->points[0] = 200; // HP
    thorn_strangle->points[1] = 20; // ATK
    thorn_strangle->points[2] = 5; // DEF

    // Initialize skills of thorn strangle
    thorn_strangle->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash = thorn_strangle->skills[0];
    init_cutlass_slash(cutlass_slash);

    thorn_strangle->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *thorny_veil = thorn_strangle->skills[1];
    init_thorny_veil(thorny_veil);

    thorn_strangle->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind = thorn_strangle->skills[2];
    init_vine_bind(vine_bind);

    thorn_strangle->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave = thorn_strangle->skills[3];
    init_healing_wave(healing_wave);

    // The right path takes the player to the Gauntlet of Peril:
    choose_path_race->options_list[1] = (Option*)malloc(sizeof(Option));
    Option *gauntlet_of_peril = choose_path_race->options_list[1];
    strcpy(gauntlet_of_peril->response_text, "To the right, the Gauntlet of Peril stretches out like a "
    "terrifying passage of fire and brimstone. The landscape is a desolate wasteland of jagged rocks and "
    "bubbling lava pits, their fiery glow casting flickering shadows across the treacherous terrain.");
    strcpy(gauntlet_of_peril->narrative_text_before, "You steer your vehicle onto the right path, facing the "
    "daunting challenges of the Gauntlet of Peril. The heat of the lava pits and the stench of sulfur assault "
    "your senses as you navigate the treacherous track.");
    strcpy(gauntlet_of_peril->narrative_text_after, "With adrenaline still coursing through your veins, you "
    "navigate your car through the aftermath of the battle. Your eyes catch a glint among the wreckage. "
    "Half-buried beneath the rubble is the first fragment of the riddle, its aged inscription "
    "illuminated by the glow of lava. A surge of anticipation grips you as you trace the ancient words etched "
    "into the stone, the first piece of the puzzle that will lead you to the final prize.");
    gauntlet_of_peril->num_enemies = 1;

    // The enemy in the Gauntlet of Peril:
    gauntlet_of_peril->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *inferno_fiend = gauntlet_of_peril->enemies[0];
    strcpy(inferno_fiend->name, "Inferno Fiend");
    inferno_fiend->points[0] = 300; // HP
    inferno_fiend->points[1] = 25; // ATK
    inferno_fiend->points[2] = 15; // DEF

    // Initialize skills of inferno fiend
    inferno_fiend->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_fiend = inferno_fiend->skills[0];
    init_shadow_strike(shadow_strike_fiend);

    inferno_fiend->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_fiend = inferno_fiend->skills[1];
    init_healing_wave(healing_wave_fiend);

    inferno_fiend->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_fiend = inferno_fiend->skills[2];
    init_vine_bind(vine_bind_fiend);

    inferno_fiend->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_fiend = inferno_fiend->skills[3];
    init_evasive_maneuver(evasive_maneuver_fiend);
}

void init_scenario2(Scenario *crossroads_of_destiny){
    // Scenario 2 - Crossroads of Destiny
    strcpy(crossroads_of_destiny->name, "The Crossroads of Destiny");
    strcpy(crossroads_of_destiny->description, "As your vehicle hurtles down the track, "
    "you approach a fork in the road, each path shrouded in its own mystery and peril. The decision "
    "you make now will shape the course of your journey, determining not only the challenges you face "
    "but also the fate of those who stand in your way.");

    // The decision is to choose between the Forgotten Ruins or the Stormy Seas:
    Decision *choose_path_crossroads = (Decision*)malloc(sizeof(Decision));
    crossroads_of_destiny->decision = choose_path_crossroads;
    choose_path_crossroads->num_options = 2;
    strcpy(choose_path_crossroads->question_text, "With the fate of your journey hanging in the balance, "
    "you must choose your path wisely.\nDo you venture into the depths of the Forgotten Ruins (1), "
    "where ancient mysteries await, or brave the tempestuous waters of the Stormy Seas (2), risking life and limb "
    "for the promise of untold rewards? Enter the number corresponding to your choice: ");

    // Option A: The Forgotten Ruins
    choose_path_crossroads->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *forgotten_ruins = choose_path_crossroads->options_list[0];
    strcpy(forgotten_ruins->response_text, "To the left lies the path to the Forgotten Ruins, where ancient "
    "secrets lie buried beneath the crumbling stones. The air is heavy with the weight of history, and the ruins "
    "whisper tales of long-forgotten civilizations and untold treasures waiting to be discovered.");
    strcpy(forgotten_ruins->narrative_text_before, "You steer your vehicle towards the left, heading into the "
    "depths of the Forgotten Ruins. The crumbling structures and overgrown foliage create an eerie atmosphere as "
    "you navigate the winding path.");
    strcpy(forgotten_ruins->narrative_text_after, "With triumph coursing through your veins, you survey the "
    "aftermath of the battle. Among the debris, a weathered stone altar catches your eye, bearing another "
    "fragment of the riddle. Anticipation grips you as you approach, the ancient symbols beckoning you closer. "
    "With a steady hand, you claim the stone fragment etched with ancient words - one less fragment stands "
    "between you and the complete riddle. ");
    forgotten_ruins->num_enemies = 1;

    // Enemy in the Forgotten Ruins:
    forgotten_ruins->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *guardian_ruins = forgotten_ruins->enemies[0];
    strcpy(guardian_ruins->name, "Guardian of the Forgotten Ruins");
    guardian_ruins->points[0] = 400; // HP
    guardian_ruins->points[1] = 35; // ATK
    guardian_ruins->points[2] = 25; // DEF

    //Skills
    guardian_ruins->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_guardian = guardian_ruins->skills[0];
    init_evasive_maneuver(evasive_maneuver_guardian);

    guardian_ruins->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_guardian = guardian_ruins->skills[1];
    init_flame_burst(flame_burst_guardian);

    guardian_ruins->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_guardian = guardian_ruins->skills[2];
    init_arcane_blast(arcane_blast_guardian);

    guardian_ruins->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_guardian = guardian_ruins->skills[3];
    init_cutlass_slash(cutlass_slash_guardian);

    // Option B: The Stormy Seas
    choose_path_crossroads->options_list[1] = (Option*)malloc(sizeof(Option));
    Option *stormy_seas = choose_path_crossroads->options_list[1];
    strcpy(stormy_seas->response_text, "To the right stretches the path to the Stormy Seas, where towering "
    "waves crash against rocky cliffs, and the wind howls like a vengeful spirit. The sea churns with hidden "
    "dangers, promising both riches and ruin to those brave enough to brave its wrath.");
    strcpy(stormy_seas->narrative_text_before, "You veer towards the right, facing the treacherous waters of "
    "the Stormy Seas. The crashing waves and howling winds create a tumultuous environment as you navigate the "
    "rocky coastline.");
    strcpy(stormy_seas->narrative_text_after, "With victory coursing through your veins, you stand amidst the "
    "aftermath of the battle, the Stormy Seas raging beside you. Along the rugged coastline, where waves crash "
    "against the cliffs with relentless fury, another fragment of the riddle lies half-buried in the sand. "
    "Anticipation grips you as you approach the weathered stone, its ancient markings illuminated by the glow of "
    "your car lights - one less fragment stands between you and the complete riddle. ");
    stormy_seas->num_enemies = 2;

    // Enemies in the Stormy Seas:
    stormy_seas->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *sea_marauders = stormy_seas->enemies[0];
    strcpy(sea_marauders->name, "Captain Blackbeard");
    sea_marauders->points[0] = 300; // HP
    sea_marauders->points[1] = 30; // ATK
    sea_marauders->points[2] = 20; // DEF

    //skills:
    sea_marauders->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_marauder = sea_marauders->skills[0];
    init_cutlass_slash(cutlass_slash_marauder);

    sea_marauders->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *thorny_veil_marauder = sea_marauders->skills[1];
    init_thorny_veil(thorny_veil_marauder);

    sea_marauders->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_marauder = sea_marauders->skills[2];
    init_vine_bind(vine_bind_marauder);

    sea_marauders->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_marauder = sea_marauders->skills[3];
    init_healing_wave(healing_wave_marauder);

    stormy_seas->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *siren_sorceress = stormy_seas->enemies[0];
    strcpy(siren_sorceress->name, "Siren the Sorceress");
    siren_sorceress->points[0] = 250; // HP
    siren_sorceress->points[1] = 25; // ATK
    siren_sorceress->points[2] = 15; // DEF
    
    //Skills
    siren_sorceress->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_sorceress = siren_sorceress->skills[0];
    init_healing_wave(healing_wave_sorceress);

    siren_sorceress->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_sorceress = siren_sorceress->skills[1];
    init_evasive_maneuver(evasive_maneuver_sorceress);

    siren_sorceress->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_sorceress = siren_sorceress->skills[2];
    init_shadow_strike(shadow_strike_sorceress);

    siren_sorceress->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_sorceress = siren_sorceress->skills[3];
    init_arcane_blast(arcane_blast_sorceress);
}

void init_scenario3(Scenario *castle){
    // Scenario 3 - The Abandoned Castle:
    strcpy(castle->name, "Abandoned Castle");
    strcpy(castle->description, "The screen shifts to reveal an ancient castle "
    "enveloped in dense fog. Two paths diverge at the entrance, offering a crucial "
    "choice that will shape your journey ahead.");

    // The decision is wether to take the left or right path:
    Decision *choose_path = (Decision*)malloc(sizeof(Decision)); // Dynamic memory allocation for the decision struct
    castle->decision = choose_path;
    choose_path->num_options = 2;
    strcpy(choose_path->question_text, "Seeker of Gemstones, will you take " 
    "the left path (1) and venture deep into the castle's crypt, or will you explore "
    "the right trail (2) and wonder into the courtyard? Enter the number corresponding to your choice: ");

    // The left path takes the player to a crypt:
    choose_path->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *crypt = choose_path->options_list[0];
    strcpy(crypt->response_text, "You descend into the depths of the crypt "
    "where secrets and unseen horrors await amongst the bones of past generations.");
    strcpy(crypt->narrative_text_before, "As you reach the crypt, a fearsome creature "
    "emerges from the darkness - a Ghoul. This undead being lurks in the shadows of the crypt, "
    "agile and relentless, it is capable of leaping from the darkness to attack unsuspecting prey.");
    strcpy(crypt->narrative_text_after, "With victory pulsing through your veins, you survey the aftermath "
    "of the battle. Among the debris of the crypt you see a pedestal, atop it lies another fragment of the "
    "riddle. Anticipation grips you as you draw near, your hand reaches out to claim the ancient stone etched "
    "with the next words of the riddle.");
    crypt->num_enemies = 1;

    // The enemy of the crypt is a ghoul:
    crypt->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *ghoul = crypt->enemies[0];
    strcpy(ghoul->name, "Ghoul");
    ghoul->points[0] = 200; // HP (when this reaches 0 the enemy is defeated)
    ghoul->points[1] = 20; // ATK (an attack reduces the player's HP by 20)
    ghoul->points[2] = 15; // DEF (blocks 15 ATK)

    //Skill
    ghoul->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_ghoul = ghoul->skills[0];
    init_shadow_strike(shadow_strike_ghoul);

    ghoul->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_ghoul = ghoul->skills[1];
    init_evasive_maneuver(evasive_maneuver_ghoul);

    ghoul->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_ghoul = ghoul->skills[2];
    init_flame_burst(flame_burst_ghoul);

    ghoul->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_ghoul = ghoul->skills[3];
    init_arcane_blast(arcane_blast_ghoul);

    // The right path takes the player to a courtyard:
    choose_path->options_list[1] = (Option*)malloc(sizeof(Option));
    Option *courtyard = choose_path->options_list[1];
    strcpy(courtyard->response_text, "You step into the wild courtyard, surrounded by towering "
    "hedges, crumbling statues, and at its heart, a weathered fountain. Mist rises from the "
    "overgrown algae, cloaking the scene in a mystical atmosphere.");
    strcpy(courtyard->narrative_text_before, "As you take in the eerie setting "
    "you suddenly sense a presence lurking amidst the overgrown greenery. Emerging "
    "from the shadows are two mighty adversaries.\nCarved from solid granite and brought to "
    "life by ancient sorcery, the Stone Guardian stands as the mighty protector of the "
    "courtyard. \nTaking a stance beside it is the Deadly Nightshade. This malevolent plant "
    "creature lurks among the wild foliage, with deadly vines and toxic flowers.");
    strcpy(courtyard->narrative_text_after, "Emerging victorious from the courtyard, a sense of "
    "accomplishment washes over you. Suddently, a shimmer of light from the fountain catches your "
    "eye. Drawing closer, you discover a hidden compartment within the weathered stone. With trembling "
    "hands, you retrieve the ancient artifact concealed within - a fragment of a runestone etched with "
    "the next words of the riddle.");
    courtyard->num_enemies = 2;

    // The first enemy of the courtyard is a stone guardian:
    courtyard->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *stone_guardian = courtyard->enemies[0];
    strcpy(stone_guardian->name, "Stone Guardian");
    stone_guardian->points[0] = 150; // HP (when this reaches 0 the enemy is defeated)
    stone_guardian->points[1] = 15; // ATK (an attack reduces the player's HP by 15)
    stone_guardian->points[2] = 10; // DEF (blocks 10 ATK)
    
    //Skills
    stone_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_stone_guardian = stone_guardian->skills[0];
    init_evasive_maneuver(evasive_maneuver_stone_guardian);

    stone_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_stone_guardian = stone_guardian->skills[1];
    init_flame_burst(flame_burst_stone_guardian);

    stone_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_stone_guardian = stone_guardian->skills[2];
    init_arcane_blast(arcane_blast_stone_guardian);

    stone_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_stone_guardian = stone_guardian->skills[3];
    init_cutlass_slash(cutlass_slash_stone_guardian);

    // The second enemy of the courtyard is deadly nightshade:
    courtyard->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *deadly_nightshade = courtyard->enemies[1];
    strcpy(deadly_nightshade->name, "Deadly Nightshade");
    deadly_nightshade->points[0] = 100; // HP (when this reaches 0 the enemy is defeated)
    deadly_nightshade->points[1] = 10; // ATK (an attack reduces the player's HP by 10)
    deadly_nightshade->points[2] = 5; // DEF (blocks 5 ATK)

    //Skills
    deadly_nightshade->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_nightshade = deadly_nightshade->skills[0];
    init_shadow_strike(shadow_strike_nightshade);

    deadly_nightshade->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_nightshade = deadly_nightshade->skills[1];
    init_healing_wave(healing_wave_nightshade);

    deadly_nightshade->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_nightshade = deadly_nightshade->skills[2];
    init_vine_bind(vine_bind_nightshade);

    deadly_nightshade->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_nightshade = deadly_nightshade->skills[3];
    init_evasive_maneuver(evasive_maneuver_nightshade);
}

void init_scenario4(Scenario *final_battle){
    // Last Scenario - The Battle for the Gemstones:
    strcpy(final_battle->name, "The Battle for the Gemstones");
    strcpy(final_battle->description, "As you emerge victorious from the towering castle, clutching the "
    "final shard of the riddle, the air crackles with anticipation. The time has come to solve the riddle "
    "that will guide you to the Sacred Gemstones. You can now piece together all the fragments you've gathered "
    "over the last three challenges. And as you do so, the puzzle unfolds before you, revealing the entirety "
    "of the riddle.");

    // The decision is the player's answer to the riddle:
    Decision *solve_riddle = (Decision*)malloc(sizeof(Decision)); // Dynamic memory allocation for the decision struct
    final_battle->decision = solve_riddle;
    solve_riddle->num_options = 1;
    strcpy(solve_riddle->question_text, "Brave adventurer, your path has led you to this critical moment. "
    "Before you lies the final mystery to unravel before claiming the gems. Listen closely:\nIt is the beginning "
    "of eternity,\nthe end of time and space,\nthe beginning of the end,\nand the end of every space.\nWhat is it? (write "
    "your answer in lower case): ");
    
    // If the riddle is solved correctly, then the final battle can commence:
    solve_riddle->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *enter_final_battle = solve_riddle->options_list[0];
    strcpy(enter_final_battle->response_text, "Congratulations! You've successfully solved the riddle! "
    "The answer is indeed the letter e.");
    strcpy(enter_final_battle->narrative_text_before, "In a flash, you find yourself transported to the location "
    "of the Sacred Gemstones. Their radiant glow captivates you, but a dangerous presence lurks nearby. Three adversaries "
    "stand guard, each embodying the essence of the gemstone they protect: time, space, and spirituality.\nThe Guardian of "
    "Time, spectral and adorned with ancient timepieces, disorients its opponents by manipulating time.\nThe Guardian of Space, "
    "enveloped in swirling darkness, commands the environment to its advantage.\nThe Guardian of Spirituality, radiant and ethereal, "
    "draws upon otherworldly powers to weaken its prey.\nPrepare yourself for the final battle, as the fate of the Sacred Gemstones "
    "rests in your hands.");
    strcpy(enter_final_battle->narrative_text_after, "With a final blow, you defeat the three adversaries, their forms disappearing "
    "into smoke. As the last guardian falls, a profound silence descends, broken only by the soft hum of the Sacred Gemstones in "
    "your grasp. The air shimmers with newfound energy as you feel the power coursing through you. Victorious, you hold the key "
    "to unlocking untold potential and shaping the destiny of the world. Then, before you, a final message appears in golden "
    "letters: 'Congratulations, adventurer! You have conquered the Trial of Ascension and emerged with the power of the Sacred Gemstones'.");
    enter_final_battle->num_enemies = 3;

    // The three enemies in this scenario are each associated with a gemstone (time, space and spirituality):
    // The first enemy is associated with time:
    enter_final_battle->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *time_guardian = enter_final_battle->enemies[0];
    strcpy(time_guardian->name, "Guardian of Time");
    time_guardian->points[0] = 300; // HP (when this reaches 0 the enemy is defeated)
    time_guardian->points[1] = 30; // ATK (an attack reduces the player's HP by 20)
    time_guardian->points[2] = 20; // DEF (blocks 15 ATK)

    time_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_time_guardian = time_guardian->skills[0];
    init_evasive_maneuver(evasive_maneuver_time_guardian);

    time_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_time_guardian = time_guardian->skills[1];
    init_flame_burst(flame_burst_time_guardian);

    time_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_time_guardian = time_guardian->skills[2];
    init_healing_wave(healing_wave_time_guardian);

    time_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_time_guardian = time_guardian->skills[3];
    init_cutlass_slash(cutlass_slash_time_guardian);

    // The second enemy is associated with space:
    enter_final_battle->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *space_guardian = enter_final_battle->enemies[1];
    strcpy(space_guardian->name, "Guardian of Space");
    space_guardian->points[0] = 300; // HP (when this reaches 0 the enemy is defeated)
    space_guardian->points[1] = 20; // ATK (an attack reduces the player's HP by 15)
    space_guardian->points[2] = 15; // DEF (blocks 10 ATK)

    //Skills
    space_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_guardian = space_guardian->skills[0];
    init_cutlass_slash(cutlass_slash_guardian);

    space_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *thorny_veil_guardian = space_guardian->skills[1];
    init_thorny_veil(thorny_veil_guardian);

    space_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_guardian = space_guardian->skills[2];
    init_vine_bind(vine_bind_guardian);

    space_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_guardian = space_guardian->skills[3];
    init_shadow_strike(shadow_strike_guardian);

    // The third enemy is associated with spirituality:
    enter_final_battle->enemies[2] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *spirituality_guardian = enter_final_battle->enemies[2];
    strcpy(spirituality_guardian->name, "Guardian of Spirituality");
    spirituality_guardian->points[0] = 300; // HP (when this reaches 0 the enemy is defeated)
    spirituality_guardian->points[1] = 25; // ATK (an attack reduces the player's HP by 10)
    spirituality_guardian->points[2] = 20; // DEF (blocks 5 ATK)
    
    //Skills
    spirituality_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_guardian = spirituality_guardian->skills[0];
    init_healing_wave(healing_wave_guardian);

    spirituality_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_guardian = spirituality_guardian->skills[1];
    init_evasive_maneuver(evasive_maneuver_guardian);

    spirituality_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_guardian = spirituality_guardian->skills[2];
    init_shadow_strike(shadow_strike_guardian);

    spirituality_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_guardian = spirituality_guardian->skills[3];
    init_arcane_blast(arcane_blast_guardian);
}
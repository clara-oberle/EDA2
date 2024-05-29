#include "init_scenarios_files.h"
#include "init_enemy_skills.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void get_skill(const char *skill_name, Skill *skill) {
    // create a copy of the skill name and remove the \n at the end so it can be used in the strcmp function:
    char skill_name_copy[NAME_SIZE];
    strcpy(skill_name_copy, skill_name);
    skill_name_copy[strcspn(skill_name_copy, "\n")] = '\0';
    // initialise the skill with its corresponding function:
    if (strcmp(skill_name_copy, "shadow_strike") == 0){
        init_shadow_strike(skill);
    }else if (strcmp(skill_name_copy, "evasive_maneuver") == 0){
        init_evasive_maneuver(skill);
    }else if (strcmp(skill_name_copy, "flame_burst") == 0){
        init_flame_burst(skill);
    }else if (strcmp(skill_name_copy, "arcane_blast") == 0){
        init_arcane_blast(skill);
    } if (strcmp(skill_name_copy, "cutlass_slash") == 0){
        init_cutlass_slash(skill);
    } if (strcmp(skill_name_copy, "thorny_veil") == 0){
        init_thorny_veil(skill);
    } if (strcmp(skill_name_copy, "vine_bind") == 0){
        init_vine_bind(skill);
    }else if (strcmp(skill_name_copy, "healing_wave") == 0){
        init_healing_wave(skill);
    }
}

void free_scenario(Scenario *scenario) {
    if (scenario == NULL) {
        return;
    }
    
    if (scenario->decision != NULL) {
        for (int i = 0; i < scenario->decision->num_options; i++) {
            Option *option = scenario->decision->options_list[i];
            if (option != NULL) {
                for (int j = 0; j < option->num_enemies; j++) {
                    if (option->enemies[j] != NULL) {
                        for (int k = 0; k < S; k++) {
                            if (option->enemies[j]->skills[k] != NULL) {
                                free(option->enemies[j]->skills[k]);
                            }
                        }
                        free(option->enemies[j]);
                    }
                }
                free(option);
            }
        }
        free(scenario->decision);
    }
    free(scenario);
}


void initialize_scenario1_from_file(Scenario *scenario, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open scenario file");
        exit(EXIT_FAILURE);
    }

    // Read name
    fgets(scenario->name, NAME_SIZE, file);
    scenario->name[strcspn(scenario->name, "\n")] = '\0';

    // Read description
    fgets(scenario->description, DESCRIPTION_SIZE, file);
    scenario->description[strcspn(scenario->description, "\n")] = '\0';

    // Allocate memory for the Decision struct
    Decision *choose_path_race = (Decision *)malloc(sizeof(Decision));
    scenario->decision = choose_path_race;
    if (scenario->decision == NULL) {
        perror("Failed to allocate memory for decision");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read number of options
    fscanf(file, "%d\n", &scenario->decision->num_options);

    // Read question text
    fgets(scenario->decision->question_text, QUESTION_SIZE, file);
    scenario->decision->question_text[strcspn(scenario->decision->question_text, "\n")] = '\0';

    // Read options
    choose_path_race->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *veil_of_obscurity = choose_path_race->options_list[0];

    // Read response text
    fgets(veil_of_obscurity->response_text, RESPONSE_SIZE, file);
    veil_of_obscurity->response_text[strcspn(veil_of_obscurity->response_text, "\n")] = '\0';

    // Read narrative text before
    fgets(veil_of_obscurity->narrative_text_before, NARRATIVE_SIZE, file);
    veil_of_obscurity->narrative_text_before[strcspn(veil_of_obscurity->narrative_text_before, "\n")] = '\0';

    // Read narrative text after
    fgets(veil_of_obscurity->narrative_text_after, NARRATIVE_SIZE, file);
    veil_of_obscurity->narrative_text_after[strcspn(veil_of_obscurity->narrative_text_after, "\n")] = '\0';

    // Read number of enemies
    fscanf(file, "%d\n", &veil_of_obscurity->num_enemies);

    // Read enemies
    veil_of_obscurity->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *shadow_stalker = veil_of_obscurity->enemies[0];

    // Read enemy name
    fgets(shadow_stalker->name, NAME_SIZE, file);
    shadow_stalker->name[strcspn(shadow_stalker->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &shadow_stalker->points[0], &shadow_stalker->points[1], &shadow_stalker->points[2]);
    
    //Skills
    char name[NAME_SIZE];

    //Skill 0
    fgets(name, NAME_SIZE, file);
    shadow_stalker->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike = shadow_stalker->skills[0];
    get_skill(name, shadow_strike);

    //Skill 1
    fgets(name, NAME_SIZE, file);
    shadow_stalker->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver = shadow_stalker->skills[1];
    get_skill(name, evasive_maneuver);
    
    //Skill 2
    fgets(name, NAME_SIZE, file);
    shadow_stalker->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst = shadow_stalker->skills[2];
    get_skill(name, flame_burst);

    //Skill 3
    fgets(name, NAME_SIZE, file);
    shadow_stalker->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast = shadow_stalker->skills[3];   
    get_skill(name, flame_burst); 


    // Read enemies Thorn Strangler
    veil_of_obscurity->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *thorn_strangle = veil_of_obscurity->enemies[1];

    // Read enemy name
    fgets(thorn_strangle->name, NAME_SIZE, file);
    thorn_strangle->name[strcspn(thorn_strangle->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &thorn_strangle->points[0], &thorn_strangle->points[1], &thorn_strangle->points[2]);
    
    //Skills
    //Skill 0
    fgets(name, NAME_SIZE, file);
    thorn_strangle->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash = thorn_strangle->skills[0];
    get_skill(name, cutlass_slash);

    //Skill 1
    fgets(name, NAME_SIZE, file);
    thorn_strangle->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *thorny_veil = thorn_strangle->skills[1];
    get_skill(name, thorny_veil);
    
    //Skill 2
    fgets(name, NAME_SIZE, file);
    thorn_strangle->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind = thorn_strangle->skills[2];
    get_skill(name, vine_bind);

    //Skill 3
    fgets(name, NAME_SIZE, file);
    thorn_strangle->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave = thorn_strangle->skills[3];   
    get_skill(name, healing_wave);    

    //Right path
    choose_path_race->options_list[1] = (Option*)malloc(sizeof(Option));
    Option *gauntlet_of_peril = choose_path_race->options_list[1];

    // Read response text
    fgets(gauntlet_of_peril->response_text, RESPONSE_SIZE, file);
    gauntlet_of_peril->response_text[strcspn(gauntlet_of_peril->response_text, "\n")] = '\0';

    // Read narrative text before
    fgets(gauntlet_of_peril->narrative_text_before, NARRATIVE_SIZE, file);
    gauntlet_of_peril->narrative_text_before[strcspn(gauntlet_of_peril->narrative_text_before, "\n")] = '\0';

    // Read narrative text after
    fgets(gauntlet_of_peril->narrative_text_after, NARRATIVE_SIZE, file);
    gauntlet_of_peril->narrative_text_after[strcspn(gauntlet_of_peril->narrative_text_after, "\n")] = '\0';
    
    // Read number of enemies
    fscanf(file, "%d\n", &gauntlet_of_peril->num_enemies);

    // Read enemies
    gauntlet_of_peril->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *inferno_fiend = gauntlet_of_peril->enemies[0];

    // Read enemy name
    fgets(inferno_fiend->name, NAME_SIZE, file);
    inferno_fiend->name[strcspn(inferno_fiend->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &inferno_fiend->points[0], &inferno_fiend->points[1], &inferno_fiend->points[2]);
    
    //Skills
    //Skill 0
    fgets(name, NAME_SIZE, file);
    inferno_fiend->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_fiend = inferno_fiend->skills[0];
    get_skill(name, shadow_strike_fiend);

    fgets(name, NAME_SIZE, file);
    inferno_fiend->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_fiend = inferno_fiend->skills[1];
    get_skill(name, healing_wave_fiend);

    fgets(name, NAME_SIZE, file);
    inferno_fiend->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_fiend = inferno_fiend->skills[2];
    get_skill(name, vine_bind_fiend);

    fgets(name, NAME_SIZE, file);
    inferno_fiend->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_fiend = inferno_fiend->skills[3];
    get_skill(name, evasive_maneuver_fiend); 
                
    fclose(file);   
}

void initialize_scenario2_from_file(Scenario *scenario, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open scenario file");
        exit(EXIT_FAILURE);
    }

    // Read name
    fgets(scenario->name, NAME_SIZE, file);
    scenario->name[strcspn(scenario->name, "\n")] = '\0';

    // Read description
    fgets(scenario->description, DESCRIPTION_SIZE, file);
    scenario->description[strcspn(scenario->description, "\n")] = '\0';

    // Allocate memory for the Decision struct
    Decision *choose_path_crossroads = (Decision *)malloc(sizeof(Decision));
    scenario->decision = choose_path_crossroads;
    if (scenario->decision == NULL) {
        perror("Failed to allocate memory for decision");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read number of options
    fscanf(file, "%d\n", &scenario->decision->num_options);

    // Read question text
    fgets(scenario->decision->question_text, QUESTION_SIZE, file);
    scenario->decision->question_text[strcspn(scenario->decision->question_text, "\n")] = '\0';

    // Read options
    choose_path_crossroads->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *forgotten_ruins = choose_path_crossroads->options_list[0];

    // Read response text
    fgets(forgotten_ruins->response_text, RESPONSE_SIZE, file);
    forgotten_ruins->response_text[strcspn(forgotten_ruins->response_text, "\n")] = '\0';

    // Read narrative text before
    fgets(forgotten_ruins->narrative_text_before, NARRATIVE_SIZE, file);
    forgotten_ruins->narrative_text_before[strcspn(forgotten_ruins->narrative_text_before, "\n")] = '\0';

    // Read narrative text after
    fgets(forgotten_ruins->narrative_text_after, NARRATIVE_SIZE, file);
    forgotten_ruins->narrative_text_after[strcspn(forgotten_ruins->narrative_text_after, "\n")] = '\0';

    // Read number of enemies
    fscanf(file, "%d\n", &forgotten_ruins->num_enemies);

    // Read enemies
    forgotten_ruins->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *guardian_ruins = forgotten_ruins->enemies[0];

    // Read enemy name
    fgets(guardian_ruins->name, NAME_SIZE, file);
    guardian_ruins->name[strcspn(guardian_ruins->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &guardian_ruins->points[0], &guardian_ruins->points[1], &guardian_ruins->points[2]);
    
    // Skills
    char name[NAME_SIZE];
    
    // Skill 0
    fgets(name, NAME_SIZE, file);
    guardian_ruins->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_guardian = guardian_ruins->skills[0];
    get_skill(name, evasive_maneuver_guardian);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    guardian_ruins->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_guardian = guardian_ruins->skills[1];
    get_skill(name, flame_burst_guardian);
    
    // Skill 2
    fgets(name, NAME_SIZE, file);
    guardian_ruins->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_guardian = guardian_ruins->skills[2];
    get_skill(name, arcane_blast_guardian);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    guardian_ruins->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_guardian = guardian_ruins->skills[3];   
    get_skill(name, cutlass_slash_guardian); 


    // Right path
    choose_path_crossroads->options_list[1] = (Option*)malloc(sizeof(Option));
    Option *stormy_seas = choose_path_crossroads->options_list[1];

    // Read response text
    fgets(stormy_seas->response_text, RESPONSE_SIZE, file);
    stormy_seas->response_text[strcspn(stormy_seas->response_text, "\n")] = '\0';

    // Read narrative text before
    fgets(stormy_seas->narrative_text_before, NARRATIVE_SIZE, file);
    stormy_seas->narrative_text_before[strcspn(stormy_seas->narrative_text_before, "\n")] = '\0';

    // Read narrative text after
    fgets(stormy_seas->narrative_text_after, NARRATIVE_SIZE, file);
    stormy_seas->narrative_text_after[strcspn(stormy_seas->narrative_text_after, "\n")] = '\0';
    
    // Read number of enemies
    fscanf(file, "%d\n", &stormy_seas->num_enemies);

    // Read enemies
    stormy_seas->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *sea_marauders = stormy_seas->enemies[0];

    // Read enemy name
    fgets(sea_marauders->name, NAME_SIZE, file);
    sea_marauders->name[strcspn(sea_marauders->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &sea_marauders->points[0], &sea_marauders->points[1], &sea_marauders->points[2]);
    
    // Skills
    // Skill 0
    fgets(name, NAME_SIZE, file);
    sea_marauders->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_marauder = sea_marauders->skills[0];
    get_skill(name, cutlass_slash_marauder);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    sea_marauders->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *thorny_veil_marauder = sea_marauders->skills[1];
    get_skill(name, thorny_veil_marauder);
    
    // Skill 2
    fgets(name, NAME_SIZE, file);
    sea_marauders->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_marauder = sea_marauders->skills[2];
    get_skill(name, vine_bind_marauder);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    sea_marauders->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_marauder = sea_marauders->skills[3];   
    get_skill(name, healing_wave_marauder);

    // Additional enemy for the sea path
    stormy_seas->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *siren_sorceress = stormy_seas->enemies[1];

    // Read enemy name
    fgets(siren_sorceress->name, NAME_SIZE, file);
    siren_sorceress->name[strcspn(siren_sorceress->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &siren_sorceress->points[0], &siren_sorceress->points[1], &siren_sorceress->points[2]);
    
    // Skills
    // Skill 0
    fgets(name, NAME_SIZE, file);
    siren_sorceress->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_siren = siren_sorceress->skills[0];
    get_skill(name, healing_wave_siren);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    siren_sorceress->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_siren = siren_sorceress->skills[1];
    get_skill(name, evasive_maneuver_siren);
    
    // Skill 2
    fgets(name, NAME_SIZE, file);
    siren_sorceress->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_siren = siren_sorceress->skills[2];
    get_skill(name, shadow_strike_siren);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    siren_sorceress->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_siren = siren_sorceress->skills[3];   
    get_skill(name, arcane_blast_siren); 

    fclose(file);
}

void initialize_scenario3_from_file(Scenario *scenario, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open scenario file");
        exit(EXIT_FAILURE);
    }

    // Read name
    fgets(scenario->name, NAME_SIZE, file);
    scenario->name[strcspn(scenario->name, "\n")] = '\0';

    // Read description
    fgets(scenario->description, DESCRIPTION_SIZE, file);
    scenario->description[strcspn(scenario->description, "\n")] = '\0';

    // Allocate memory for the Decision struct
    Decision *choose_path = (Decision *)malloc(sizeof(Decision));
    scenario->decision = choose_path;
    if (scenario->decision == NULL) {
        perror("Failed to allocate memory for decision");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read number of options
    fscanf(file, "%d\n", &scenario->decision->num_options);

    // Read question text
    fgets(scenario->decision->question_text, QUESTION_SIZE, file);
    scenario->decision->question_text[strcspn(scenario->decision->question_text, "\n")] = '\0';

    // Read options
    choose_path->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *crypt = choose_path->options_list[0];

    // Read response text
    fgets(crypt->response_text, RESPONSE_SIZE, file);
    crypt->response_text[strcspn(crypt->response_text, "\n")] = '\0';

    // Read narrative text before
    fgets(crypt->narrative_text_before, NARRATIVE_SIZE, file);
    crypt->narrative_text_before[strcspn(crypt->narrative_text_before, "\n")] = '\0';

    // Read narrative text after
    fgets(crypt->narrative_text_after, NARRATIVE_SIZE, file);
    crypt->narrative_text_after[strcspn(crypt->narrative_text_after, "\n")] = '\0';

    // Read number of enemies
    fscanf(file, "%d\n", &crypt->num_enemies);

    // Read enemies
    crypt->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *ghoul = crypt->enemies[0];

    // Read enemy name
    fgets(ghoul->name, NAME_SIZE, file);
    ghoul->name[strcspn(ghoul->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &ghoul->points[0], &ghoul->points[1], &ghoul->points[2]);
    
    // Skills
    char name[NAME_SIZE];
    
    // Skill 0
    fgets(name, NAME_SIZE, file);
    ghoul->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_ghoul = ghoul->skills[0];
    get_skill(name, shadow_strike_ghoul);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    ghoul->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_ghoul = ghoul->skills[1];
    get_skill(name, evasive_maneuver_ghoul);
    
    // Skill 2
    fgets(name, NAME_SIZE, file);
    ghoul->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_ghoul = ghoul->skills[2];
    get_skill(name, flame_burst_ghoul);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    ghoul->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_ghoul = ghoul->skills[3];   
    get_skill(name, arcane_blast_ghoul); 


    // Right path
    choose_path->options_list[1] = (Option*)malloc(sizeof(Option));
    Option *courtyard = choose_path->options_list[1];

    // Read response text
    fgets(courtyard->response_text, RESPONSE_SIZE, file);
    courtyard->response_text[strcspn(courtyard->response_text, "\n")] = '\0';

    // Read narrative text before
    fgets(courtyard->narrative_text_before, NARRATIVE_SIZE, file);
    courtyard->narrative_text_before[strcspn(courtyard->narrative_text_before, "\n")] = '\0';

    // Read narrative text after
    fgets(courtyard->narrative_text_after, NARRATIVE_SIZE, file);
    courtyard->narrative_text_after[strcspn(courtyard->narrative_text_after, "\n")] = '\0';
    
    // Read number of enemies
    fscanf(file, "%d\n", &courtyard->num_enemies);

    // Read enemies
    courtyard->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *stone_guardian = courtyard->enemies[0];

    // Read enemy name
    fgets(stone_guardian->name, NAME_SIZE, file);
    stone_guardian->name[strcspn(stone_guardian->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &stone_guardian->points[0], &stone_guardian->points[1], &stone_guardian->points[2]);
    
    // Skills
    // Skill 0
    fgets(name, NAME_SIZE, file);
    stone_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_stone_guardian = stone_guardian->skills[0];
    get_skill(name, evasive_maneuver_stone_guardian);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    stone_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_stone_guardian = stone_guardian->skills[1];
    get_skill(name, flame_burst_stone_guardian);
    
    // Skill 2
    fgets(name, NAME_SIZE, file);
    stone_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_stone_guardian = stone_guardian->skills[2];
    get_skill(name, arcane_blast_stone_guardian);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    stone_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_stone_guardian = stone_guardian->skills[3];   
    get_skill(name, cutlass_slash_stone_guardian); 

    // Second enemy
    courtyard->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *deadly_nightshade = courtyard->enemies[1];

    // Read enemy name
    fgets(deadly_nightshade->name, NAME_SIZE, file);
    deadly_nightshade->name[strcspn(deadly_nightshade->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &deadly_nightshade->points[0], &deadly_nightshade->points[1], &deadly_nightshade->points[2]);
    
    // Skills
    // Skill 0
    fgets(name, NAME_SIZE, file);
    deadly_nightshade->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_nightshade = deadly_nightshade->skills[0];
    get_skill(name, shadow_strike_nightshade);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    deadly_nightshade->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_nightshade = deadly_nightshade->skills[1];
    get_skill(name, healing_wave_nightshade);
    
    // Skill 2
    fgets(name, NAME_SIZE, file);
    deadly_nightshade->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_nightshade = deadly_nightshade->skills[2];
    get_skill(name, vine_bind_nightshade);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    deadly_nightshade->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_nightshade = deadly_nightshade->skills[3];   
    get_skill(name, evasive_maneuver_nightshade); 

    fclose(file);
}

void initialize_scenario4_from_file(Scenario *scenario, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open scenario file");
        exit(EXIT_FAILURE);
    }

    // Read name
    fgets(scenario->name, NAME_SIZE, file);
    scenario->name[strcspn(scenario->name, "\n")] = '\0';

    // Read description
    fgets(scenario->description, DESCRIPTION_SIZE, file);
    scenario->description[strcspn(scenario->description, "\n")] = '\0';

    // Allocate memory for the Decision struct
    Decision *solve_riddle = (Decision *)malloc(sizeof(Decision));
    scenario->decision = solve_riddle;
    if (scenario->decision == NULL) {
        perror("Failed to allocate memory for decision");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read number of options
    fscanf(file, "%d\n", &scenario->decision->num_options);

    // Read question text
    fgets(scenario->decision->question_text, QUESTION_SIZE, file);
    scenario->decision->question_text[strcspn(scenario->decision->question_text, "\n")] = '\0';

    // Read options
    solve_riddle->options_list[0] = (Option*)malloc(sizeof(Option));
    Option *enter_final_battle = solve_riddle->options_list[0];

    // Read response text
    fgets(enter_final_battle->response_text, RESPONSE_SIZE, file);
    enter_final_battle->response_text[strcspn(enter_final_battle->response_text, "\n")] = '\0';

    // Read narrative text before
    fgets(enter_final_battle->narrative_text_before, NARRATIVE_SIZE, file);
    enter_final_battle->narrative_text_before[strcspn(enter_final_battle->narrative_text_before, "\n")] = '\0';

    // Read narrative text after
    fgets(enter_final_battle->narrative_text_after, NARRATIVE_SIZE, file);
    enter_final_battle->narrative_text_after[strcspn(enter_final_battle->narrative_text_after, "\n")] = '\0';

    // Read number of enemies
    fscanf(file, "%d\n", &enter_final_battle->num_enemies);

    // Read enemies
    enter_final_battle->enemies[0] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *time_guardian = enter_final_battle->enemies[0];

    // Read enemy name
    fgets(time_guardian->name, NAME_SIZE, file);
    time_guardian->name[strcspn(time_guardian->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &time_guardian->points[0], &time_guardian->points[1], &time_guardian->points[2]);
    
    // Skills
    char name[NAME_SIZE];
    
    // Skill 0
    fgets(name, NAME_SIZE, file);
    time_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_time_guardian = time_guardian->skills[0];
    get_skill(name, evasive_maneuver_time_guardian);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    time_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *flame_burst_time_guardian = time_guardian->skills[1];
    get_skill(name, flame_burst_time_guardian);
    
    // Skill 2
    fgets(name, NAME_SIZE, file);
    time_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_time_guardian = time_guardian->skills[2];
    get_skill(name, healing_wave_time_guardian);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    time_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_time_guardian = time_guardian->skills[3]; 
    get_skill(name, cutlass_slash_time_guardian); 

    // Second Enemy
    enter_final_battle->enemies[1] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *space_guardian = enter_final_battle->enemies[1];

    // Read enemy name
    fgets(space_guardian->name, NAME_SIZE, file);
    space_guardian->name[strcspn(space_guardian->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &space_guardian->points[0], &space_guardian->points[1], &space_guardian->points[2]);

    // Skill 0
    fgets(name, NAME_SIZE, file);
    space_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *cutlass_slash_space_guardian = space_guardian->skills[0];
    get_skill(name, cutlass_slash_space_guardian);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    space_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *thorny_veil_space_guardian = space_guardian->skills[1];
    get_skill(name, thorny_veil_space_guardian);

    // Skill 2
    fgets(name, NAME_SIZE, file);
    space_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *vine_bind_space_guardian = space_guardian->skills[2];
    get_skill(name, vine_bind_space_guardian);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    space_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_space_guardian = space_guardian->skills[3];   
    get_skill(name, shadow_strike_space_guardian);

    // Third Enemy
    enter_final_battle->enemies[2] = (Enemy*)malloc(sizeof(Enemy));
    Enemy *spirituality_guardian = enter_final_battle->enemies[2];

    // Read enemy name
    fgets(spirituality_guardian->name, NAME_SIZE, file);
    spirituality_guardian->name[strcspn(spirituality_guardian->name, "\n")] = '\0';

    // Read enemy points (HP, ATK, DEF)
    fscanf(file, "%f %f %f\n", &spirituality_guardian->points[0], &spirituality_guardian->points[1], &spirituality_guardian->points[2]);

    // Skill 0
    fgets(name, NAME_SIZE, file);
    spirituality_guardian->skills[0] = (Skill*)malloc(sizeof(Skill));
    Skill *healing_wave_spir_guardian = spirituality_guardian->skills[0];
    get_skill(name, healing_wave_spir_guardian);

    // Skill 1
    fgets(name, NAME_SIZE, file);
    spirituality_guardian->skills[1] = (Skill*)malloc(sizeof(Skill));
    Skill *evasive_maneuver_spir_guardian = spirituality_guardian->skills[1];
    get_skill(name, evasive_maneuver_spir_guardian);

    // Skill 2
    fgets(name, NAME_SIZE, file);
    spirituality_guardian->skills[2] = (Skill*)malloc(sizeof(Skill));
    Skill *shadow_strike_spir_guardian = spirituality_guardian->skills[2];
    get_skill(name, shadow_strike_spir_guardian);

    // Skill 3
    fgets(name, NAME_SIZE, file);
    spirituality_guardian->skills[3] = (Skill*)malloc(sizeof(Skill));
    Skill *arcane_blast_spir_guardian = spirituality_guardian->skills[3];   
    get_skill(name, arcane_blast_spir_guardian);

    fclose(file);
}
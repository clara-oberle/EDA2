#ifndef INIT_SCENARIOS_H
#define INIT_SCENARIOS_H

#include "struct_definitions.h"

#define NAME_SIZE 50
#define DESCRIPTION_SIZE 1024
#define QUESTION_SIZE 512
#define RESPONSE_SIZE 512
#define NARRATIVE_SIZE 512
#define MAX_SKILLS 4

void init_scenario1(Scenario *race_of_shadows);
void init_scenario2(Scenario *crossroads_of_destiny);
void init_scenario3(Scenario *castle);
void init_scenario4(Scenario *final_battle);

void initialize_scenario_from_file(Scenario *scenario, const char *filename);
void free_scenario(Scenario *scenario);
void get_skill(const char *skill_name, Skill *skill);

#endif
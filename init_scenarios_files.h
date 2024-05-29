#ifndef INIT_SCENARIOS_H
#define INIT_SCENARIOS_H

#include "struct_definitions.h"

#define NAME_SIZE 50
#define DESCRIPTION_SIZE 2000
#define QUESTION_SIZE 1000
#define RESPONSE_SIZE 1000
#define NARRATIVE_SIZE 1000
#define MAX_SKILLS 4

void initialize_scenario1_from_file(Scenario *scenario, const char *filename);
void initialize_scenario2_from_file(Scenario *scenario, const char *filename);
void initialize_scenario3_from_file(Scenario *scenario, const char *filename);
void initialize_scenario4_from_file(Scenario *scenario, const char *filename);

void free_scenario(Scenario *scenario);
void get_skill(const char *skill_name, Skill *skill);

#endif
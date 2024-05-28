#ifndef GRAPH_H
#define GRAPH_H

#include "struct_definitions.h"

typedef struct GraphNode {
    char name[N];
    struct GraphNode *next;
} GraphNode;

typedef struct {
    int num_scenarios;
    GraphNode **adj_list;
} Graph;

Graph* create_graph(int num_scenarios);
GraphNode* create_graph_node(const char *scenario_name);
void add_scenario(Graph *graph, const char *scenario_name);
void add_edge(Graph *graph, const char *scenario, const char *destination);
void printGraph(Graph *graph);
void navigate_scenarios(Graph *graph, Scenario *current_scenario);
void printScenariosWithEdgeTo(Graph *graph, const char *target);
void update_current_scenario(GraphNode *destination_scenario, Scenario *current_scenario);
#endif // GRAPH_H


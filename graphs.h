#ifndef GRAPH_H
#define GRAPH_H

#include "struct_definitions.h"

typedef struct GraphNode {
    Scenario *scenario;
    struct GraphNode *next;
} GraphNode;

typedef struct {
    int num_scenarios;
    GraphNode **adj_list;
} Graph;

Graph* create_graph(int num_scenarios);
GraphNode* create_graph_node(Scenario *scenario);
void add_scenario(Graph *graph, Scenario *new_scenario);
void add_edge(Graph *graph, Scenario *scenario, Scenario *destination);
void printGraph(Graph *graph);
void navigate_scenarios(Graph *graph, Scenario **current_scenario);
#endif // GRAPH_H


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
void add_edge(Graph *graph, Scenario *src, Scenario *dest); // Updated to use Scenario pointers
void print_graph(Graph *graph);

#endif // GRAPH_H


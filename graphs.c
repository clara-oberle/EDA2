#include "graphs.h"
#include <stdio.h>
#include <stdlib.h>

Graph* create_graph(int num_scenarios) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->num_scenarios = num_scenarios;
    graph->adj_list = (GraphNode**)malloc(num_scenarios * sizeof(GraphNode*));

    for (int i = 0; i < num_scenarios; i++) {
        graph->adj_list[i] = NULL;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    GraphNode *new_node = (GraphNode*)malloc(sizeof(GraphNode));
    new_node->scenario = graph->adj_list[dest]->scenario;
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;

    new_node = (GraphNode*)malloc(sizeof(GraphNode));
    new_node->scenario = graph->adj_list[src]->scenario;
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

void print_graph(Graph *graph) {
    for (int i = 0; i < graph->num_scenarios; i++) {
        GraphNode *temp = graph->adj_list[i];
        printf("Scenario %d: %s\n", i, temp->scenario->name);
        while (temp) {
            printf(" -> %s\n", temp->scenario->name);
            temp = temp->next;
        }
        printf("\n");
    }
}
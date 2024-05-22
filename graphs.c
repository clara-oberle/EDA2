#include "graphs.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new graph with a specified number of scenarios
Graph* create_graph(int num_scenarios) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Failed to allocate memory for the graph.\n");
        exit(EXIT_FAILURE);
    }
    graph->num_scenarios = num_scenarios;
    graph->adj_list = (GraphNode**)malloc(num_scenarios * sizeof(GraphNode*));
    if (graph->adj_list == NULL) {
        fprintf(stderr, "Failed to allocate memory for the adjacency list.\n");
        free(graph);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_scenarios; i++) {
        graph->adj_list[i] = NULL;
    }

    return graph;
}

// Helper function to add a new node to the adjacency list
void add_node(Graph *graph, Scenario *src, Scenario *dest) {
    GraphNode *new_node = (GraphNode*)malloc(sizeof(GraphNode));
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate memory for a new graph node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->scenario = dest;
    new_node->next = NULL;

    for (int i = 0; i < graph->num_scenarios; i++) {
        if (graph->adj_list[i] != NULL && graph->adj_list[i]->scenario == src) {
            new_node->next = graph->adj_list[i]->next;
            graph->adj_list[i]->next = new_node;
            return;
        }
    }

    for (int i = 0; i < graph->num_scenarios; i++) {
        if (graph->adj_list[i] == NULL) {
            graph->adj_list[i] = (GraphNode*)malloc(sizeof(GraphNode));
            if (graph->adj_list[i] == NULL) {
                fprintf(stderr, "Failed to allocate memory for a new graph node.\n");
                exit(EXIT_FAILURE);
            }
            graph->adj_list[i]->scenario = src;
            graph->adj_list[i]->next = new_node;
            return;
        }
    }
}

// Function to add an edge between two scenarios in the graph
void add_edge(Graph *graph, Scenario *src, Scenario *dest) {
    add_node(graph, src, dest); // Add edge from src to dest
    add_node(graph, dest, src); // Add edge from dest to src (since this is an undirected graph)
}

// Function to print the graph for debugging purposes
void print_graph(Graph *graph) {
    for (int i = 0; i < graph->num_scenarios; i++) {
        GraphNode *temp = graph->adj_list[i];
        if (temp != NULL) {
            printf("Scenario %d: %s\n", i, temp->scenario->name);
            while (temp) {
                printf(" -> %s\n", temp->scenario->name);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}
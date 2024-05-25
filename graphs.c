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

//function that creates a new node
GraphNode* create_graph_node(Scenario *scenario) {
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    newNode->scenario = scenario;
    newNode->next = NULL;
    return newNode;
}

void add_scenario(Graph *graph, Scenario *new_scenario) {
    //if there are no num of scenarios
    if (graph->num_scenarios == 0) {
        fprintf(stderr, "Graph has no scenarios.\n");
        return;
    }

    //to find an empty spot in the adjacency list
    for (int i = 0; i < graph->num_scenarios; i++) {
        if (graph->adj_list[i] == NULL){
            graph->adj_list[i] = create_graph_node(new_scenario);
            return;
        }
    }
    return;
}

void add_edge(Graph *graph, Scenario *scenario, Scenario *destination) {
    if (graph->num_scenarios == 0) {
        fprintf(stderr, "Graph has no scenarios.\n");
        return;
    }

    //to find the source scenario
    GraphNode *source_node = NULL;
    //iterate through the different scenarios
    for (int i = 0; i < graph->num_scenarios; i++) {
        //when we find the adj list element that it's not null and it's the scenarion we are looking for
        if (graph->adj_list[i] != NULL && graph->adj_list[i]->scenario == scenario) {
            //we update the source node
            source_node = graph->adj_list[i];
            break;
        }
    }

    //if the source scenario is not found, print an error message and return
    if (source_node == NULL) {
        fprintf(stderr, "Source scenario not found. Cannot add edge.\n");
        return;
    }

    //create a new node for the destination scenario and add it to the adjacency list of the source scenario
    GraphNode *new_node = create_graph_node(destination);
    //we make the new node point to the same next node as the source node
    new_node->next = source_node->next;
    //we update the source next to the new node
    source_node->next = new_node;
    return;
}

/*
// Helper function to add a new node to the adjacency list
void add_node(Graph *graph, Scenario *src, Scenario *destination) {
    GraphNode *new_node = (GraphNode*)malloc(sizeof(GraphNode));
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate memory for a new graph node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->scenario = destination;
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
}*/

// Function to print the graph for debugging purposes
/*
void printGraph(Graph *graph) {
    //if there are no scenarios
    if (graph->num_scenarios == 0) {
        printf("Graph is empty.\n");
        return;
    }

    printf("You can travel from:\n");
    for (int i = 0; i < graph->num_scenarios; ++i) {
        //print each scenario
        printf("Scenario %d to: ", i + 1);
        //pointer to the current scenario
        GraphNode *current = graph->adj_list[i];
        if (current == NULL) {
            printf("No outgoing edges.\n");
        }else {
            //while there are edges
            while (current != NULL) {
                //print the edges, hence, the scenarios we can travel to
                
                printf("%s, ", current->scenario->name);
                current = current->next;
            }
            printf("\n");
        }
    }

}

*/
void printGraph(Graph *graph) {
    for (int i = 0; i < graph->num_scenarios; i++) {
        GraphNode *node = graph->adj_list[i];
        if (node != NULL) {
            printf("Scenario: %s\n", node->scenario->name);
            printf("Description: %s\n", node->scenario->description);
            printf("Leads to: ");
            GraphNode *temp = node->next;
            while (temp != NULL) {
                printf("%s ", temp->scenario->name);
                temp = temp->next;
            }
            printf("\n\n");
        }
    }
}

void printScenariosWithEdgeTo(Graph *graph, Scenario *target) {
    for (int i = 0; i < graph->num_scenarios; i++) {
        //when we find the adj list element that it's not null and it's the scenarion we are looking for
        if (graph->adj_list[i] != NULL && graph->adj_list[i]->scenario == target) {
            printf("Can travel from scenario %d to:", i+1);
            GraphNode *current = graph->adj_list[i];
            while(current != NULL){
                printf("%s", current->scenario);
                current = current->next;
            }
        }
    }
}

void navigate_scenarios(Graph *graph, Scenario **current_scenario) {
    int current_index = -1;

    // Find the index of the current scenario
    for (int i = 0; i < graph->num_scenarios; i++) {
        if (graph->adj_list[i] != NULL && graph->adj_list[i]->scenario == *current_scenario) {
            current_index = i;
            break;
        }
    }
    //error handeling
    if (current_index == -1) {
        printf("Error: Current scenario not found in the graph.\n");
        return;
    }

    //while loop to print the possible scenarios
    int found = 0; //not found yet
    while (found != 1) {
        //we create a pointer to point at the current scenario
        GraphNode *node = graph->adj_list[current_index];
        if (node == NULL) {
            printf("Error: Scenario not found.\n");
            break;
        }

        printf("Current Scenario: %s\n", node->scenario->name);
        //in case it's the last scenario
        if (current_index == 3) { // Assuming the 4th scenario index is 3
            printf("You have reached the final scenario.\n");
            break;
        }

        printf("Choose your next scenario:\n");
        //create another pointer that points at the next node
        GraphNode *temp = node->next;
        int index = 1;
        while (temp != NULL) {
            printf("%d. %s\n", index, temp->scenario->name);
            temp = temp->next;
            index++;
        }
        //get the users input
        printf("Enter the number of the next scenario: ");
        int choice;
        scanf("%d", &choice);

        //to validate the choice
        while(choice < 1 || choice >= index) {
            printf("Invalid choice. Try again.\n");
            scanf("%d", &choice);
        }

        //move to the chosen scenario
        temp = node->next;
        for (int i = 1; i < choice; i++) {
            temp = temp->next;
        }

        //to find the index of the chosen scenario
        for (int i = 0; i < graph->num_scenarios; i++) {
            if (graph->adj_list[i] != NULL && graph->adj_list[i]->scenario == temp->scenario) {
                current_index = i;
                *current_scenario = temp->scenario;
                found = 1;
                break;
            }
        }
    }
}


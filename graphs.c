#include "graphs.h"
#include "init_scenarios_test.h"
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
GraphNode* create_graph_node(char scenario_name[N]) {
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    strcpy(newNode->name, scenario_name);
    newNode->next = NULL;
    return newNode;
}

void add_scenario(Graph *graph, char scenario_name[N]) {
    //if there are no num of scenarios
    if (graph->num_scenarios == 0) {
        fprintf(stderr, "Graph has no scenarios.\n");
        return;
    }

    //to find an empty spot in the adjacency list
    for (int i = 0; i < graph->num_scenarios; i++) {
        if (graph->adj_list[i] == NULL){
            graph->adj_list[i] = create_graph_node(scenario_name);
            return;
        }
    }
    return;
}

void add_edge(Graph *graph, char scenario[N], char destination[N]) {
    if (graph->num_scenarios == 0) {
        fprintf(stderr, "Graph has no scenarios.\n");
        return;
    }

    //to find the source scenario
    GraphNode *source_node = NULL;
    //iterate through the different scenarios
    for (int i = 0; i < graph->num_scenarios; i++) {
        //when we find the adj list element that it's not null and it's the scenarion we are looking for
        if (graph->adj_list[i] != NULL && strcmp(graph->adj_list[i]->name, scenario) == 0) {
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

void printGraph(Graph *graph) {
    for (int i = 0; i < graph->num_scenarios; i++) {
        GraphNode *node = graph->adj_list[i];
        if (node != NULL) {
            printf("Scenario: %s\n", node->name);
            printf("Leads to: ");
            GraphNode *temp = node->next;
            while (temp != NULL) {
                printf("%s ", temp->name);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

void printScenariosWithEdgeTo(Graph *graph, char target[N]) {
    for (int i = 0; i < graph->num_scenarios; i++) {
        //when we find the adj list element that it's not null and it's the scenarion we are looking for
        if (graph->adj_list[i] != NULL && strcmp(graph->adj_list[i]->name, target) == 0) {
            printf("Can travel from scenario %d to:", i+1);
            GraphNode *current = graph->adj_list[i];
            while(current != NULL){
                printf("%s", current->name);
                current = current->next;
            }
        }
    }
}

void update_current_scenario(GraphNode *destination_scenario, Scenario *current_scenario){
    Scenario *new_scenario = (Scenario*)malloc(sizeof(Scenario));
    current_scenario = new_scenario;
    if(strcmp(destination_scenario->name, "The Race of Shadows") == 0){
        initialize_scenario1_from_file(current_scenario, "race_of_shadows.txt");
    }
    else if(strcmp(destination_scenario->name, "The Crossroads of Destiny") == 0){
        initialize_scenario2_from_file(current_scenario, "the_crossroads_of_destiny.txt");
    }
    else if(strcmp(destination_scenario->name, "Abandoned Castle") == 0){
        initialize_scenario3_from_file(current_scenario, "abandoned_castle.txt");
    }
    else if(strcmp(destination_scenario->name, "The Battle for the Gemstones") == 0){
        initialize_scenario4_from_file(current_scenario, "battle_gemstones.txt");
    }
}


void navigate_scenarios(Graph *graph, Scenario *current_scenario) {
    int current_index = -1;

    // Find the index of the current scenario
    for (int i = 0; i < graph->num_scenarios; i++) {
        if (graph->adj_list[i] != NULL && strcmp(graph->adj_list[i]->name, current_scenario->name) == 0) {
            current_index = i;
            break;
        }
    }
    //error handeling
    if (current_index == -1) {
        printf("Error: Current scenario not found in the graph.\n");
        return;
    }
    
    //we create a pointer to point at the current scenario
    GraphNode *node = graph->adj_list[current_index];
    if (node == NULL) {
        printf("Error: Scenario not found.\n");
    }

    printf("Current Scenario: %s\n", node->name);
    //in case it's the last scenario
    if (current_index == 3) { // Assuming the 4th scenario index is 3
        printf("You have reached the final scenario.\n");
    }

    printf("Choose your next scenario:\n");
    //create another pointer that points at the next node
    GraphNode *temp = node->next;
    int index = 1;
    while (temp != NULL) {
        printf("%d. %s\n", index, temp->name);
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

    update_current_scenario(temp, current_scenario);
}


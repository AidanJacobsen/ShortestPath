#include "files.h"
#include <stdio.h>
#include <stdbool.h>

// Function to generate a graph from a file
bool generateGraphFromFile(const char* filename, struct graph* graph) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    char node1Name[50];
    char node2Name[50];
    int weight;
    bool success = true; // Variable to track success

    while (fscanf(file, "%49s %d %49s", node1Name, &weight, node2Name) == 3) {
        // Check if weight is non-negative
        if (weight < 0) {
            success = false;
            break; // Exit the loop on failure
        }
        
        // Add connections to the graph using the addConnection function
        if (!addConnection(graph, node1Name, weight, node2Name)) {
            // Return false if adding a connection fails
            success = false;
            break; // Exit the loop on failure
        }
    }

    fclose(file);
    return success;
}

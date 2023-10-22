#include <stdio.h>
#include "graph.h"
#include "files.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    struct graph graph;
    graph.head = NULL;
    graph.tail = NULL;

    if (generateGraphFromFile(filename, &graph)) {
        // printf("Graph loaded successfully from %s\n", filename);

        struct node* start = addNode(&graph, argv[2]);
        struct node* end = addNode(&graph, argv[3]);

        calculateShortestPath(&graph, start, end);

        // Access and print the names, connections, and weights of nodes in the graph
        // struct node* currentNode = graph.head;
        // while (currentNode != NULL) {
        //     printf("Node Name: %s, Distance: %d\n", currentNode->name, currentNode->distance);
        //     struct connection* currentConnection = currentNode->connectionHead;
        //     while (currentConnection != NULL) {
        //         printf("Connection: %s - %s (Weight: %d)\n", currentConnection->node1->name, currentConnection->node2->name, currentConnection->weight);
        //         currentConnection = currentConnection->next;
        //     }
        //     currentNode = currentNode->next;
        // }
        printPath(start, end);
    } else {
        printf("Graph File Invalid\n"); // Error message for invalid graph file
    }

    destroyGraph(&graph);

    return 0;
}

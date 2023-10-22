#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

// Define the 'connection' structure with an integer 'weight' field
struct connection {
    struct node* node1;
    struct node* node2;
    int weight;
    struct connection* next;
    struct connection* prev;
};

// Define the 'node' structure with an integer 'distance' field
struct node {
    char name[50];  // Assuming a maximum name length of 49 characters
    struct connection* connectionHead;
    struct connection* connectionTail;
    struct node* next;
    struct node* prev;
    int distance; // New field for distance, initialized to -1
    bool complete; // New boolean field 'complete'
};

// Define the 'graph' structure with head and tail pointers for nodes
struct graph {
    struct node* head;
    struct node* tail;
};

// Function prototypes
struct node* createNode(const char* name);
struct connection* createConnection(struct node* node1, struct node* node2, int weight);
struct node* addNode(struct graph* graph, const char* nodeName);
bool addConnection(struct graph* graph, const char* nodeName1, int weight, const char* nodeName2);
void updateDistances(struct node* node);
struct node* getNextNode(struct graph* graph);
bool calculateShortestPath(struct graph* graph, struct node* start, struct node* end);
struct node* findNextNode(struct node* currentNode);
void printPath(struct node* start, struct node* end);
void destroyNode(struct node* node);
void destroyGraph(struct graph* graph);

#endif

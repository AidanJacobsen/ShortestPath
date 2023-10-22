#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to create a new node with a given name
struct node* createNode(const char* name) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode) {
        strcpy(newNode->name, name);
        newNode->connectionHead = NULL;
        newNode->connectionTail = NULL;
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->distance = -1; // Initialize distance to -1
        newNode->complete = false;
    }
    return newNode;
}

// Function to create a new connection between two nodes with a given weight
struct connection* createConnection(struct node* node1, struct node* node2, int weight) {
    struct connection* newConnection = (struct connection*)malloc(sizeof(struct connection));
    if (newConnection) {
        newConnection->node1 = node1;
        newConnection->node2 = node2;
        newConnection->weight = weight;
        newConnection->next = NULL;
        newConnection->prev = NULL;
    }
    return newConnection;
}

// Function to add a new node to the end of the linked list in the graph and return its pointer
struct node* addNode(struct graph* graph, const char* nodeName) {
    // Check if the node already exists in the graph
    struct node* currentNode = graph->head;
    while (currentNode != NULL) {
        if (strcmp(currentNode->name, nodeName) == 0) {
            return currentNode; // Node already exists, return its pointer
        }
        currentNode = currentNode->next;
    }

    // Create a new node
    struct node* newNode = createNode(nodeName);

    if (newNode) {
        // If the graph is empty, set the new node as the head and tail
        if (graph->head == NULL) {
            graph->head = newNode;
            graph->tail = newNode;
        } else {
            // Otherwise, add the new node to the end of the linked list
            newNode->prev = graph->tail;
            graph->tail->next = newNode;
            graph->tail = newNode;
        }
    }

    return newNode; // Return the pointer to the newly added node
}

// Function to add a connection between two nodes
bool addConnection(struct graph* graph, const char* nodeName1, int weight, const char* nodeName2) {
    // Attempt to add the first node
    struct node* node1 = addNode(graph, nodeName1);

    // Attempt to add the second node
    struct node* node2 = addNode(graph, nodeName2);

    // Check if a connection with different weight already exists
    struct connection* existingConnection = node1->connectionHead;
    while (existingConnection != NULL) {
        if ((existingConnection->node1 == node1 && existingConnection->node2 == node2) ||
            (existingConnection->node1 == node2 && existingConnection->node2 == node1)) {
            if (existingConnection->weight != weight) {
                return false; // Existing connection with different weight
            }
        }
        existingConnection = existingConnection->next;
    }

    // Create a connection for node1
    struct connection* conn1 = createConnection(node1, node2, weight);

    // Create a distinct connection for node2
    struct connection* conn2 = createConnection(node2, node1, weight);

    if (conn1 && conn2) {
        // Add conn1 to node1's connection list
        if (node1->connectionHead == NULL) {
            node1->connectionHead = conn1;
            node1->connectionTail = conn1;
        } else {
            node1->connectionTail->next = conn1;
            conn1->prev = node1->connectionTail;
            node1->connectionTail = conn1;
        }

        // Add conn2 to node2's connection list
        if (node2->connectionHead == NULL) {
            node2->connectionHead = conn2;
            node2->connectionTail = conn2;
        } else {
            node2->connectionTail->next = conn2;
            conn2->prev = node2->connectionTail;
            node2->connectionTail = conn2;
        }
    }

    return true; // Connection added successfully
}

void updateDistances(struct node* node)
{
    struct connection * currentConnection = node->connectionHead;
    while(currentConnection != NULL)
    {
        //Determine the connected Node
        struct node * connectedNode = NULL;
        if(currentConnection->node1 == node)
        {
            connectedNode = currentConnection->node2;
        }
        else
        {
            connectedNode = currentConnection->node1;
        }

        if(connectedNode->distance == -1 || connectedNode->distance > node->distance + currentConnection->weight)
        {
            //update the connectedNode's distance (it can't possibly have already been searched by algorithm limits)
            connectedNode->distance = node->distance + currentConnection->weight;
        }
        currentConnection = currentConnection->next;
    }
    node->complete = true;
}

struct node* getNextNode(struct graph* graph) {
    struct node* currentNode = graph->head;
    struct node* lowestNode = NULL;

    while (currentNode != NULL) {
        if (currentNode->distance != -1 && !currentNode->complete) {
            if (lowestNode == NULL || currentNode->distance < lowestNode->distance) {
                lowestNode = currentNode;
            }
        }
        currentNode = currentNode->next;
    }

    return lowestNode;
}

bool calculateShortestPath(struct graph* graph, struct node* start, struct node* end) {
    // Set the distance of the start node to zero
    end->distance = 0;

    struct node* currentNode = getNextNode(graph);
    while (currentNode != start) {
        if (currentNode == NULL) {
            // Handle the case where there is no valid path to the end node
            return false;
        }

        // Update distances for the current node and its connections
        updateDistances(currentNode);

        // Get the next node to process
        currentNode = getNextNode(graph);
    }

    return true; // A path to the end node has been found
}

struct node* findNextNode(struct node* currentNode)
{
    struct connection* currentConnection = currentNode->connectionHead;
    while(currentConnection != NULL)
    {
        //Determine the connected Node
        struct node * connectedNode = NULL;
        if(currentConnection->node1 == currentNode)
        {
            connectedNode = currentConnection->node2;
        }
        else
        {
            connectedNode = currentConnection->node1;
        }

        if(currentConnection->weight + connectedNode->distance == currentNode->distance)
        {
            return connectedNode;
        }

        currentConnection = currentConnection->next;
    }
    return NULL;
}

void printPath(struct node* start, struct node* end)
{
    printf("ShortestPath (Length=%d): ", start->distance);
    struct node* currentNode = start;
    while(currentNode != end && currentNode != NULL)
    {
        printf("%s->", currentNode->name);
        currentNode = findNextNode(currentNode);
    }
    if(currentNode == end)
    {
        printf("%s", end->name);
    }
    printf("\n");
    return;
}

// Function to free the memory associated with a node
void destroyNode(struct node* node)
{
    // Free connections associated with the node
    struct connection* currentConnection = node->connectionHead;
    while (currentConnection != NULL) {
        struct connection* nextConnection = currentConnection->next;
        free(currentConnection);
        currentConnection = nextConnection;
    }

    // Free the node itself
    free(node);
}

// Function to free a graph, including all nodes and connections
void destroyGraph(struct graph* graph)
{
    struct node* currentNode = graph->head;
    while (currentNode != NULL) {
        struct node* nextNode = currentNode->next;

        // Use the destroyNode function to free the current node and its connections
        destroyNode(currentNode);

        currentNode = nextNode;
    }

    // Do not free the graph structure yet
}
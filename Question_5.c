#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_NODES 10
#define MAX_EDGES 30
#define INF 999999

// Structure to represent a directed edge
typedef struct {
    char u, v;
    int cost;
} Edge;

void reconstructPath(int parent[], char nodes[], int start, int dest) {
    if (dest == start) {
        printf("%c", nodes[start]);
        return;
    }
    if (parent[dest] == -1) {
        printf("Unreachable");
        return;
    }
    reconstructPath(parent, nodes, start, parent[dest]);
    printf(" -> %c", nodes[dest]);
}

int main() {
    // Vertices (Data centers)
    char nodes[MAX_NODES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int numNodes = 10;

    // Directed Edges and Net Transfer Costs based on problem specification:
    // AB6, AD16, BC6, BD6, BJ7, CG-9, DE7, DJ8, EF10, EI-2, FG4, FI2, GH13, IF2, JE3
    Edge edges[MAX_EDGES] = {
        {'A', 'B', 6},
        {'A', 'D', 16},
        {'B', 'C', 6},
        {'B', 'D', 6},
        {'B', 'J', 7},
        {'C', 'G', -9},
        {'D', 'E', 7},
        {'D', 'J', 8},
        {'E', 'F', 10},
        {'E', 'I', -2},
        {'F', 'G', 4},
        {'F', 'I', 2},
        {'G', 'H', 13},
        {'I', 'F', 2},
        {'J', 'E', 3}
    };
    int numEdges = 15;

    printf("=== Task 1: Graph Representation ===\n");
    printf("Total Data Centers (Vertices): %d\n", numNodes);
    printf("Total Directed Routes (Edges): %d\n\n", numEdges);

    // Task 2 & 3: Bellman-Ford Algorithm Implementation
    int sourceIndex = 0; // Starting from Data Center A
    int dist[MAX_NODES];
    int parent[MAX_NODES];

    for (int i = 0; i < numNodes; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[sourceIndex] = 0;

    // Relax all edges V - 1 times
    for (int i = 1; i <= numNodes - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edges[j].u - 'A';
            int v = edges[j].v - 'A';
            int weight = edges[j].cost;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Task 4: Negative-Weight Cycle Detection
    int negativeCycle = 0;
    for (int j = 0; j < numEdges; j++) {
        int u = edges[j].u - 'A';
        int v = edges[j].v - 'A';
        int weight = edges[j].cost;

        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            negativeCycle = 1;
            break;
        }
    }

    if (negativeCycle) {
        printf("Negative-weight cycle detected. Shortest-path results may be undefined.\n\n");
    } else {
        printf("No negative-weight cycle detected.\n\n");
    }

    // Task 5: Display Routing Table Results
    printf("=== Task 5: Routing Table from Source: %c ===\n", nodes[sourceIndex]);
    printf("%-12s %-15s %s\n", "Destination", "Shortest Cost", "Path");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < numNodes; i++) {
        if (i == sourceIndex) continue; // Skip source itself

        printf("%-12c ", nodes[i]);
        if (dist[i] >= INF / 2) {
            printf("%-15s ", "Unreachable");
            printf("No route available\n");
        } else {
            char costStr[20];
            sprintf(costStr, "%d", dist[i]);
            printf("%-15s ", costStr);
            reconstructPath(parent, nodes, sourceIndex, i);
            printf("\n");
        }
    }
    printf("\n");

    // Interactive lookup / validation test option
    char input[50];
    printf("Enter a destination data center to check route (e.g., G) or type 'ALL': ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) > 0 && toupper(input[0]) != 'A') {
            char destChar = toupper(input[0]);
            int destIndex = -1;
            for (int i = 0; i < numNodes; i++) {
                if (nodes[i] == destChar) {
                    destIndex = i;
                    break;
                }
            }

            if (destIndex == -1) {
                printf("Error: Invalid data center name entered. Handled gracefully without crashing.\n");
            } else {
                printf("\nRoute to Destination: %c\n", nodes[destIndex]);
                printf("Cost: %d\n", dist[destIndex]);
                printf("Path: ");
                reconstructPath(parent, nodes, sourceIndex, destIndex);
                printf("\n");
            }
        }
    }

    return 0;
}

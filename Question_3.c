#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 7
#define MAX_EDGES 20

// Structure to represent an edge
typedef struct {
    char u, v;
    int cost;
} Edge;

// Disjoint Set Union (DSU) structures for cycle detection
int parent[MAX_NODES];
int rank[MAX_NODES];

void dsu_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int dsu_find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = dsu_find(parent[i]);
}

int dsu_union(int i, int j) {
    int root_i = dsu_find(i);
    int root_j = dsu_find(j);
    if (root_i != root_j) {
        if (rank[root_i] < rank[root_j])
            parent[root_i] = root_j;
        else if (rank[root_i] > rank[root_j])
            parent[root_j] = root_i;
        else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }
        return 1; // Union successful (no cycle)
    }
    return 0; // Cycle detected
}

// Comparison function to sort edges by cost
int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->cost - e2->cost;
}

int main() {
    // Stations: A=0, B=1, C=2, D=3, E=4, F=5, G=6
    char nodes[MAX_NODES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    // Available connections
    Edge edges[MAX_EDGES] = {
        {'A', 'B', 6},
        {'A', 'D', 12},
        {'B', 'D', 5},
        {'B', 'C', 11},
        {'C', 'D', 17},
        {'C', 'G', 25},
        {'D', 'E', 22},
        {'D', 'F', 15},
        {'E', 'F', 10},
        {'F', 'G', 22}
    };
    int numEdges = 10;

    printf("=== Task 1: Adjacency Matrix Representation ===\n");
    int adjMatrix[MAX_NODES][MAX_NODES] = {0};
    
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].u - 'A';
        int v = edges[i].v - 'A';
        adjMatrix[u][v] = edges[i].cost;
        adjMatrix[v][u] = edges[i].cost; // Undirected graph
    }

    printf("  \t");
    for (int i = 0; i < MAX_NODES; i++) printf("%c\t", nodes[i]);
    printf("\n----------------------------------------------------\n");
    for (int i = 0; i < MAX_NODES; i++) {
        printf("%c\t", nodes[i]);
        for (int j = 0; j < MAX_NODES; j++) {
            printf("%d\t", adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("=== Tasks 2, 3 & 4: Kruskal's Algorithm & Selected MST Connections ===\n");
    // Sort edges by increasing cost
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    dsu_init(MAX_NODES);
    Edge mst[MAX_NODES];
    int mstCount = 0;
    int totalCost = 0;

    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].u - 'A';
        int v = edges[i].v - 'A';

        if (dsu_union(u, v)) {
            mst[mstCount++] = edges[i];
            totalCost += edges[i].cost;
        }
    }

    printf("Selected Connections:\n");
    for (int i = 0; i < mstCount; i++) {
        printf("Station %c — Station %c : %d\n", mst[i].u, mst[i].v, mst[i].cost);
    }
    printf("\nTotal Installation Cost: %d thousand dollars\n", totalCost);

    return 0;
}

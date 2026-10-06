#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NODES 7

// Structure for Queue implementation in BFS
typedef struct {
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_NODES - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

int main() {
    char nodes[MAX_NODES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    // Adjacency matrix initialization with data-transfer times (0 means no direct link)
    int adjMatrix[MAX_NODES][MAX_NODES] = {0};

    // Edges definition: (u, v, cost)
    // AB6, AD12, BD5, BC11, CD17, CG25, DE22, DF15, EF10, FG22
    int edges[10][3] = {
        {0, 1, 6},   // A - B
        {0, 3, 12},  // A - D
        {1, 3, 5},   // B - D
        {1, 2, 11},  // B - C
        {2, 3, 17},  // C - D
        {2, 6, 25},  // C - G
        {3, 4, 22},  // D - E
        {3, 5, 15},  // D - F
        {4, 5, 10},  // E - F
        {5, 6, 22}   // F - G
    };

    for (int i = 0; i < 10; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int cost = edges[i][2];
        adjMatrix[u][v] = cost;
        adjMatrix[v][u] = cost; // Undirected graph
    }

    // Task 1: Gateway Selection & Validation
    char input[50];
    int startIndex = -1;

    printf("Enter starting gateway (e.g., D): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove newline character if present
        input[strcspn(input, "\n")] = 0;
        
        // Convert to uppercase
        char startChar = toupper(input[0]);

        for (int i = 0; i < MAX_NODES; i++) {
            if (nodes[i] == startChar) {
                startIndex = i;
                break;
            }
        }
    }

    if (startIndex == -1) {
        printf("Error: Invalid gateway name entered. Program terminated gracefully.\n");
        return 1;
    }

    printf("\n--- Task 2: BFS Connectivity Analysis starting from Gateway %c ---\n", nodes[startIndex]);
    
    int visited[MAX_NODES] = {0};
    Queue q;
    initQueue(&q);

    visited[startIndex] = 1;
    enqueue(&q, startIndex);

    printf("BFS Traversal Order: ");
    int traversalOrder[MAX_NODES];
    int orderCount = 0;

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        traversalOrder[orderCount++] = current;
        printf("%c ", nodes[current]);

        for (int i = 0; i < MAX_NODES; i++) {
            if (adjMatrix[current][i] > 0 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
    printf("\n\n");

    // Task 3: Communication Analysis (One-hop neighbors of starting gateway)
    printf("--- Task 3: Communication Analysis for Direct (One-Hop) Neighbors ---\n");
    printf("Gateways directly connected to %c:\n", nodes[startIndex]);

    int maxTime = -1;
    char highestGateway = ' ';
    int hasDirectNeighbors = 0;

    for (int i = 0; i < MAX_NODES; i++) {
        if (adjMatrix[startIndex][i] > 0) {
            hasDirectNeighbors = 1;
            int transferTime = adjMatrix[startIndex][i];
            printf(" - Gateway %c with data-transfer time: %d ms\n", nodes[i], transferTime);

            if (transferTime > maxTime) {
                maxTime = transferTime;
                highestGateway = nodes[i];
            }
        }
    }

    if (hasDirectNeighbors) {
        printf("\nDirectly connected gateway with the highest data-transfer time:\n");
        printf("Gateway %c — %d ms\n", highestGateway, maxTime);
    } else {
        printf("No direct connections found.\n");
    }

    return 0;
}

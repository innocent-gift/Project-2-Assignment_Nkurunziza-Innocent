#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct {
    char id;
    int priority;
} Baggage;

void swap(Baggage *a, Baggage *b) {
    Baggage temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Baggage heap[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].priority > heap[largest].priority)
        largest = left;
    if (right < n && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

void buildMaxHeap(Baggage heap[], int n) {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        maxHeapify(heap, n, i);
    }
}

void insertHeap(Baggage heap[], int *n, char id, int priority) {
    if (*n >= MAX_SIZE) return;
    int i = *n;
    heap[i].id = id;
    heap[i].priority = priority;
    (*n)++;

    while (i != 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteById(Baggage heap[], int *n, char targetId) {
    int index = -1;
    for (int i = 0; i < *n; i++) {
        if (heap[i].id == targetId) {
            index = i;
            break;
        }
    }
    if (index == -1) return;

    // Replace with last element
    heap[index] = heap[*n - 1];
    (*n)--;
    maxHeapify(heap, *n, index);
    // Also fix up if necessary
    int i = index;
    while (i != 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void printHeap(Baggage heap[], int n) {
    printf("Heap Structure (ID : Priority):\n");
    for (int i = 0; i < n; i++) {
        printf("[%c : %d] ", heap[i].id, heap[i].priority);
    }
    printf("\n\n");
}

int main() {
    int rawPriorities[] = {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42};
    int n = 11;
    Baggage heap[MAX_SIZE];

    for (int i = 0; i < n; i++) {
        heap[i].id = 'A' + i;
        heap[i].priority = rawPriorities[i];
    }

    printf("=== Task 1: Initial Max-Heap Construction ===\n");
    buildMaxHeap(heap, n);
    printHeap(heap, n);

    printf("=== Task 2: Insertion of Container X (Priority 100) ===\n");
    insertHeap(heap, &n, 'X', 100);
    printHeap(heap, n);

    printf("=== Task 3: Removal of Container X ===\n");
    deleteById(heap, &n, 'X');
    printHeap(heap, n);

    return 0;
}

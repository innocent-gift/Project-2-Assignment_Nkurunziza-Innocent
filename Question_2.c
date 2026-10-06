#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct {
    char id[10];
    char name[30];
    int priority;
} Patient;

void swapPatients(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Patient heap[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].priority > heap[largest].priority)
        largest = left;
    if (right < n && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i) {
        swapPatients(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

void buildMaxHeap(Patient heap[], int n) {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        maxHeapify(heap, n, i);
    }
}

void insertPatient(Patient heap[], int *n, const char *id, const char *name, int priority) {
    if (*n >= MAX_SIZE) return;
    int i = *n;
    strcpy(heap[i].id, id);
    strcpy(heap[i].name, name);
    heap[i].priority = priority;
    (*n)++;

    while (i != 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
        swapPatients(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void removePatientById(Patient heap[], int *n, const char *targetId) {
    int index = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(heap[i].id, targetId) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return;

    heap[index] = heap[*n - 1];
    (*n)--;
    maxHeapify(heap, *n, index);
    
    int i = index;
    while (i != 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
        swapPatients(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    Patient heap[MAX_SIZE] = {
        {"P01", "Amina", 72},
        {"P02", "Daniel", 45},
        {"P03", "Eric", 91},
        {"P04", "Grace", 63},
        {"P05", "Hassan", 88},
        {"P06", "Irene", 54},
        {"P07", "Jean", 76}
    };
    int n = 7;

    printf("=== Task 1: Initial Max-Heap Construction ===\n");
    buildMaxHeap(heap, n);
    for (int i = 0; i < n; i++) {
        printf("[%s - %s : %d] ", heap[i].id, heap[i].name, heap[i].priority);
    }
    printf("\n\n");

    printf("=== Task 2: Treatment Order (Extraction) ===\n");
    // Make a copy for extraction demonstration
    Patient tempHeap[MAX_SIZE];
    memcpy(tempHeap, heap, sizeof(Patient) * n);
    int tempN = n;

    while (tempN > 0) {
        Patient top = tempHeap[0];
        printf("Patient %s (%s) — Priority %d\n", top.id, top.name, top.priority);
        tempHeap[0] = tempHeap[tempN - 1];
        tempN--;
        maxHeapify(tempHeap, tempN, 0);
    }
    printf("\n");

    printf("=== Task 3: New Emergency Patient Kofi (P08) - Priority 98 ===\n");
    insertPatient(heap, &n, "P08", "Kofi", 98);
    for (int i = 0; i < n; i++) {
        printf("[%s - %s : %d] ", heap[i].id, heap[i].name, heap[i].priority);
    }
    printf("\n\n");

    printf("=== Task 4: Patient P08 Cleared from Queue ===\n");
    removePatientById(heap, &n, "P08");
    for (int i = 0; i < n; i++) {
        printf("[%s - %s : %d] ", heap[i].id, heap[i].name, heap[i].priority);
    }
    printf("\n");

    return 0;
}

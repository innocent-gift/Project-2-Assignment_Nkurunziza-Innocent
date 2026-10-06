# Advanced Data Structures and Algorithms — C Implementation Portfolio

This repository contains C implementations for five core computer science problems covering priority queues, graph algorithms, minimum spanning trees, graph traversals, and shortest-path routing with negative edge weights.

---

## Author & Context
* **Author:** Innocent Nkurunziza  
* **Institution:** African Leadership University (ALU), Kigali, Rwanda  
* **Program:** Bachelor of Software Engineering  

---

## Project Structure & Task Summary

### 1. Airport Baggage Handling Priority Queue (`Question_1.c`)
* **Core Concept:** Array-based Max-Heap.
* **Key Operations:** Initial Max-Heap construction from raw priority scores, mapping container IDs (`A`, `B`, `C`, ...), inserting a high-priority container (`X`, priority 100) using upward heapification, and deleting container `X` with proper re-heapification.

### 2. Hospital Emergency Triage Priority System (`Question_2.c`)
* **Core Concept:** Max-Heap Priority Queue with structured records.
* **Key Operations:** Manages patient records containing Patient ID, Name, and Triage Priority Score. Implements heap construction, descending-order patient extraction (treatment order), insertion of a new emergency patient (`P08`, Kofi, priority 98), and subsequent queue clearance with heap property restoration.

### 3. EV Charging Station Power Network (`Question_3.c`)
* **Core Concept:** Minimum Spanning Tree (MST) using Kruskal's Algorithm.
* **Key Operations:** Constructs an undirected weighted adjacency matrix, sorts available underground power connections by increasing installation cost, implements a Disjoint Set Union (DSU) data structure for cycle detection, selects the optimal MST connections, and calculates the total minimum cost.

### 4. IoT Gateway Connectivity Analyzer (`Question_4.c`)
* **Core Concept:** Breadth-First Search (BFS) Graph Traversal.
* **Key Operations:** Accepts and validates starting gateway inputs, implements a queue-based BFS traversal across farm zones, identifies all one-hop directly connected neighbors, and analyzes edge weights to determine the gateway with the highest data-transfer time.

### 5. Cloud Service Data Routing Analyzer (`Question_5.c`)
* **Core Concept:** Bellman-Ford Shortest-Path Algorithm.
* **Key Operations:** Models a weighted directed data-center network supporting negative edge weights (optimization credits), executes Bellman-Ford relaxation loops, checks for reachable negative-weight cycles, reconstructs step-by-step paths, handles unreachable nodes, and outputs a complete routing table.

---

## Compilation & Execution Guide

You can compile and run each program individually using `gcc` in your terminal:

### Question 1: Airport Baggage Priority Queue
```bash
gcc Question_1.c -o q1
./q1

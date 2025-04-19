
/*The algorithm:
Initializes all vertices as unvisited and with no parent (-1)
For each unvisited vertex (to handle disconnected components):

Starts BFS from that vertex
For each adjacent vertex:

If unvisited: marks it visited, enqueues it, and sets its parent
If already visited AND not the parent: cycle detected 
(because we found an edge to an already visited vertex that isn't our parent)*/

#include<stdio.h>
#include "5.Graph_Adj_mat.c"  // Using adjacency matrix for BFS
#include<stdbool.h>

// Function to check if the graph is connected using BFS
bool bfs_is_connected(GRAPH *g) {
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};
    int start = 1;  // Starting from vertex 1

    queue[rear++] = start;
    visited[start] = 1;
    int count = 1;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 1; i <= g->vertex; i++) {
            if (g->adjMatrix[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                count++;
            }
        }
    }
    // If all vertices are visited, the graph is connected
    return count == g->vertex;
}

// Function to detect cycles in the graph using BFS
bool bfs_contains_cycle(GRAPH *g) {
    int queue[MAX], front, rear, visited[MAX], parent[MAX];

    for (int i = 1; i <= g->vertex; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    for (int start = 1; start <= g->vertex; start++) {
        if (!visited[start]) {
            front = rear = 0;
            queue[rear++] = start;
            visited[start] = 1;

            while (front < rear) {
                int current = queue[front++];
                for (int i = 1; i <= g->vertex; i++) {
                    if (g->adjMatrix[current][i]) {
                        if (!visited[i]) {
                            queue[rear++] = i;
                            visited[i] = 1;
                            parent[i] = current;
                        } else if (i != parent[current]) {  // Cycle detected
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    GRAPH g;
    create_adjMatrix(&g);  // Initialize graph

    if (bfs_is_connected(&g)) {
        printf("The graph is connected.\n");
    } else {
        printf("The graph is not connected.\n");
    }

    if (bfs_contains_cycle(&g)) {
        printf("The graph contains a cycle.\n");
    } else {
        printf("The graph does not contain any cycles.\n");
    }

    return 0;
}

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define VERTCOUNT 5  

int minDistance(int dist[], bool sptSet[]);
void dijkstra(int graph[VERTCOUNT][VERTCOUNT], int src);


int main() 
{
    int graph[VERTCOUNT][VERTCOUNT] = {
        {0, 10, 0, 5, 0},
        {0, 0, 1, 2, 0},
        {0, 0, 0, 0, 4},
        {0, 3, 9, 0, 2},
        {7, 0, 6, 0, 0}
    };

    dijkstra(graph, 0);

    return 0;
}

int minDistance(int dist[], bool sptSet[]) 
{
    int min = INT_MAX, minIdx;

    for (int v = 0; v < VERTCOUNT; v++)
    {
        if (!sptSet[v] && dist[v] <= min)
        {
            min = dist[v], minIdx = v;
        }
    }
    return minIdx;
}


void dijkstra(int graph[VERTCOUNT][VERTCOUNT], int src) 
{
    int dist[VERTCOUNT];      // Distance from src to i
    bool sptSet[VERTCOUNT];   // sptSet[i] is true if vertex i is included in shortest path tree

    
    for (int i = 0; i < VERTCOUNT; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
    }
    dist[src] = 0;  // Distance from source to itself is 0

    // Find shortest path for all vertices
    for (int count = 0; count < VERTCOUNT - 1; count++) 
    {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < VERTCOUNT; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < VERTCOUNT; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}
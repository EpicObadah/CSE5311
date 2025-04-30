#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VERTCOUNT 5  
#define EDGECOUNT 8  

struct Edge 
{
    int src;
    int dest;
    int weight;
};

void bellmanFord(struct Edge edges[], int src);

int main() 
{
    struct Edge edges[EDGECOUNT] = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    bellmanFord(edges, 0);

    return 0;
}



void bellmanFord(struct Edge edges[], int src) 
{
    int dist[VERTCOUNT];

    
    for (int i = 0; i < VERTCOUNT; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    
    for (int i = 1; i <= VERTCOUNT - 1; i++) 
    {
        for (int j = 0; j < EDGECOUNT; j++) 
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < EDGECOUNT; j++) 
    {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) 
        {
            printf("Graph has negative-weight cycle\n");
            return;
        }
    }

    printf("Vertex is \t Distance from the Source %d\n", src);
    for (int i = 0; i < VERTCOUNT; i++) 
    {
        if (dist[i] == INT_MAX)
        {
            printf("%d \t\t INF\n", i);
        }
        else
        {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }
}
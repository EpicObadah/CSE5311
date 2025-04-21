#include <stdio.h>
#include <Stdlib.h>

#define MAX_VERT 100
#define MAX_EDGE 100

typedef struct Edge
{
    int src;
    int dest;
    int weight;
} Edge;

typedef struct Graph
{
    int vertCount;
    int edgeCount;
    Edge edges[MAX_EDGE];
} Graph;

int find(int v);
void unionSets(int u,int v);
int compEdges(const void* a, const void* b);
void kruskal(Graph* graph);

int main()
{
    int vertices = 4;
    int edges = 5;
    Graph* graph = malloc(sizeof(Graph));
    graph->vertCount = vertices;
    graph->edgeCount = edges;

    // Define edges: src, dest, weight
    graph->edges[0] = (Edge){0, 1, 10};
    graph->edges[1] = (Edge){0, 2, 6};
    graph->edges[2] = (Edge){0, 3, 5};
    graph->edges[3] = (Edge){1, 3, 15};
    graph->edges[4] = (Edge){2, 3, 4};

    kruskal(graph);

    return 0;
}

int parent[MAX_VERT];
int rank[MAX_VERT];

int find(int v)
{
    if (parent[v] != v)
    {
        parent[v] = find(parent[v]);
    }
    return parent[v];
}

void unionSets(int u,int v)
{
    int rootU = find(u);
    int rootV = find(v);

    if (rootU != rootV)
    {
        if(rank[rootU] < rank[rootV])
        {
            parent[rootU] = rootV;
        }
        else if (rank[rootU] > rank[rootV])
        {
            parent[rootV] = rootU;
        }
        else 
        {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int compEdges(const void* a, const void* b)
{
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

void kruskal(Graph* graph) 
{
    int vertices = graph->vertCount;
    Edge result[MAX_VERT];  
    int resultIdx = 0; 
    int sortIdx = 0; 

    // Sort all edges by weight
    qsort(graph->edges, graph->edgeCount, sizeof(Edge), compEdges);

    // Create parent and rank subsets
    for (int v = 0; v < vertices; ++v) 
    {
        parent[v] = v;
        rank[v] = 0;
    }

    // Pick the smallest edge and add to Minimmum Spanning Tree if no cycle
    while (resultIdx < vertices - 1 && sortIdx < graph->edgeCount)
    {
        Edge nextEdge = graph->edges[sortIdx++];

        int x = find(nextEdge.src);
        int y = find(nextEdge.dest);

        if (x != y) 
        {
            result[resultIdx++] = nextEdge;
            unionSets(x, y);
        }
    }

    // Print the Minimum Spanning Tree
    printf("Edges in Minimum Spanning Tree:\n");
    int totalWeight = 0;
    for (int i = 0; i < resultIdx; ++i)
    {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of Minimum Spanning Tree: %d\n", totalWeight);
}


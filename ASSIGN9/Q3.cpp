#include <iostream>
using namespace std;

struct Node 
{
    int dest, weight;
    Node* next;
};

struct Edge 
{
    int src, dest, weight;
};

class Graph 
{
    int V;
    Node* adjList[20];
    Edge edges[50];
    int edgeCount = 0;
    int parent[20];

public:
    Graph(int v) 
    {
        V = v;
        for(int i = 0; i < V; i++)
        {
            adjList[i] = NULL;
        }
    }

    void addEdge(int src, int dest, int weight) 
    {
        Node* newNode = new Node();
        newNode->dest = dest;
        newNode->weight = weight;
        newNode->next = adjList[src];
        adjList[src] = newNode;

        newNode = new Node();
        newNode->dest = src;
        newNode->weight = weight;
        newNode->next = adjList[dest];
        adjList[dest] = newNode;

        edges[edgeCount++] = {src, dest, weight};
    }

    int find(int i) 
    {
        while(parent[i] != i)
        {
            i = parent[i];
        }
        return i;
    }

    void unionSet(int a, int b) 
    {
        int rootA = find(a);
        int rootB = find(b);
        parent[rootA] = rootB;
    }

    void kruskalMST() 
    {
        for(int i = 0; i < V; i++)
        {
            parent[i] = i;
        }

        // Simple bubble sort for edges by weight
        for(int i = 0; i < edgeCount - 1; i++) 
        {
            for(int j = 0; j < edgeCount - i - 1; j++) 
            {
                if(edges[j].weight > edges[j+1].weight) 
                {
                    Edge temp = edges[j];
                    edges[j] = edges[j+1];
                    edges[j+1] = temp;
                }
            }
        }

        int totalCost = 0;
        cout << "\nEdges in Minimum Spanning Tree:\n";

        for(int i = 0; i < edgeCount; i++) 
        {
            int u = edges[i].src;
            int v = edges[i].dest;

            if(find(u) != find(v)) 
            {
                cout << u << " - " << v << " : " << edges[i].weight << endl;
                totalCost += edges[i].weight;
                unionSet(u, v);
            }
        }

        cout << "Total Minimum Cost = " << totalCost << endl;
    }
};

int main() 
{
    int v, e, src, dest, weight;

    cout << "Enter number of vertices: ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;

    for(int i = 0; i < e; i++) 
    {
        cout << "Enter edge (source destination weight): ";
        cin >> src >> dest >> weight;
        g.addEdge(src, dest, weight);
    }

    g.kruskalMST();
    return 0;
}

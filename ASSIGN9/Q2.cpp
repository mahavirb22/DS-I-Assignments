#include <iostream>
using namespace std;

struct Node 
{
    int vertex;
    int weight;
    Node* next;
};

class Graph 
{
    int V;
    Node* adjList[20];

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
        newNode->vertex = dest;
        newNode->weight = weight;
        newNode->next = adjList[src];
        adjList[src] = newNode;

        newNode = new Node();
        newNode->vertex = src;
        newNode->weight = weight;
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }

    void primMST() 
    {
        int parent[20], key[20];
        bool inMST[20];

        for(int i = 0; i < V; i++) 
        {
            key[i] = 9999;
            inMST[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for(int count = 0; count < V - 1; count++) 
        {
            int min = 9999, u;

            for(int i = 0; i < V; i++) 
            {
                if(!inMST[i] && key[i] < min) 
                {
                    min = key[i];
                    u = i;
                }
            }

            inMST[u] = true;

            Node* temp = adjList[u];
            while(temp != NULL) 
            {
                int v = temp->vertex;
                int w = temp->weight;

                if(!inMST[v] && w < key[v]) 
                {
                    key[v] = w;
                    parent[v] = u;
                }
                temp = temp->next;
            }
        }

        cout << "\nEdges in Minimum Spanning Tree:\n";
        int total = 0;
        for(int i = 1; i < V; i++) 
        {
            cout << parent[i] << " - " << i << "  Weight: " << key[i] << endl;
            total += key[i];
        }

        cout << "Total Minimum Cost = " << total << endl;
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

    g.primMST();

    return 0;
}

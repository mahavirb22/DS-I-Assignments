#include <iostream>
using namespace std;

struct Edge 
{
    int src, dest, weight;
    Edge* next;
};

void addEdge(Edge*& head, int s, int d, int w) 
{
    Edge* newNode = new Edge();
    newNode->src = s;
    newNode->dest = d;
    newNode->weight = w;
    newNode->next = head;
    head = newNode;
}

int findParent(int parent[], int i) 
{
    while (parent[i] != i)
    {
        i = parent[i];
    }
    return i;
}

void unionSet(int parent[], int a, int b) 
{
    int x = findParent(parent, a);
    int y = findParent(parent, b);
    parent[x] = y;
}

void sortEdges(Edge*& head) 
{
    for (Edge* i = head; i != NULL; i = i->next) 
    {
        for (Edge* j = i->next; j != NULL; j = j->next) 
        {
            if (i->weight > j->weight) 
            {
                swap(i->src, j->src);
                swap(i->dest, j->dest);
                swap(i->weight, j->weight);
            }
        }
    }
}

int main() 
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    int graph[20][20];
    cout << "Enter Adjacency Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    Edge* edgeList = NULL;

    // Convert adjacency matrix to edge list (linked list)
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (graph[i][j] != 0)
            {
                addEdge(edgeList, i, j, graph[i][j]);
            }
        }
    }

    sortEdges(edgeList);

    int parent[20];
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    cout << "\nEdges in Minimum Spanning Tree:\n";
    int edgeCount = 0;
    Edge* temp = edgeList;

    while (temp != NULL && edgeCount < n - 1) 
    {
        int u = temp->src;
        int v = temp->dest;

        if (findParent(parent, u) != findParent(parent, v)) 
        {
            cout << u << " - " << v << " : " << temp->weight << endl;
            unionSet(parent, u, v);
            edgeCount++;
        }
        temp = temp->next;
    }

    return 0;
}

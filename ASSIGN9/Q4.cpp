#include <iostream>
using namespace std;

#define INF 9999

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

    void dijkstra(int start, int end) 
    {
        int dist[20];
        bool visited[20];

        for(int i = 0; i < V; i++) 
        {
            dist[i] = INF;
            visited[i] = false;
        }

        dist[start] = 0;

        for(int count = 0; count < V - 1; count++) 
        {
            int min = INF, u;

            for(int i = 0; i < V; i++) 
            {
                if(!visited[i] && dist[i] < min) 
                {
                    min = dist[i];
                    u = i;
                }
            }

            visited[u] = true;

            Node* temp = adjList[u];
            while(temp != NULL) 
            {
                int v = temp->vertex;
                int w = temp->weight;

                if(!visited[v] && dist[u] + w < dist[v]) 
                {
                    dist[v] = dist[u] + w;
                }
                temp = temp->next;
            }
        }

        cout << "\nShortest distance from " << start 
             << " to " << end << " = " << dist[end] << endl;
    }
};

int main() 
{
    int v, e, src, dest, weight, start, end;

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

    cout << "Enter starting node: ";
    cin >> start;

    cout << "Enter destination node: ";
    cin >> end;

    g.dijkstra(start, end);

    return 0;
}

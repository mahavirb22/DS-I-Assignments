#include <iostream>
#include <limits.h>
using namespace std;

#define MAX 10

// Linked List Node to store path
struct Node 
{
    int data;
    Node* next;
};

// Function to add node at end of linked list
void insert(Node* &head, int value) 
{
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode;
    }
    else 
    {
        Node* temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Function to print linked list
void display(Node* head) 
{
    while(head != NULL) 
    {
        cout << head->data << " ";
        head = head->next;
    }
}

// Dijkstra Algorithm
void dijkstra(int graph[MAX][MAX], int n, int src, int dest) 
{
    int dist[MAX], visited[MAX], parent[MAX];

    for(int i = 0; i < n; i++) 
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for(int count = 0; count < n - 1; count++) 
    {
        int min = INT_MAX, u;

        for(int i = 0; i < n; i++)
        {
            if(!visited[i] && dist[i] <= min) 
            {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for(int v = 0; v < n; v++) 
        {
            if(!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
               dist[u] + graph[u][v] < dist[v]) 
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Store path in linked list
    Node* path = NULL;
    int temp = dest;
    while(temp != -1) 
    {
        insert(path, temp);
        temp = parent[temp];
    }

    cout << "\nShortest Distance from " << src << " to " << dest << " = " << dist[dest] << endl;
    cout << "Path (in reverse using linked list): ";
    display(path);
}

int main() 
{
    int graph[MAX][MAX], n, src, dest;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter Adjacency Matrix:\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    cout << "Enter source node: ";
    cin >> src;

    cout << "Enter destination node: ";
    cin >> dest;

    dijkstra(graph, n, src, dest);

    return 0;
}

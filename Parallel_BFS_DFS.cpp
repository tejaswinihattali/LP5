#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include<ctime>
#include <omp.h>

using namespace std;

// Graph class
class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected Graph
    }

    // Sequential BFS
    void sequentialBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        double start_time = omp_get_wtime();

        visited[start] = true;
        q.push(start);

        cout << "\nSequential BFS: ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            //cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        double end_time = omp_get_wtime();

        cout << "\nTime Taken: "<< (end_time - start_time)<< " seconds\n";
    }

    // Parallel BFS using OpenMP
    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        double start_time = omp_get_wtime();

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS: ";

        while (!q.empty()) {

            int node;

            #pragma omp critical
            {
                node = q.front();
                q.pop();
            }

            //cout << node << " ";

            #pragma omp parallel for
            for (int i = 0; i < (int)adj[node].size(); i++) {

                int neighbor = adj[node][i];

                if (!visited[neighbor]) {

                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        double end_time = omp_get_wtime();

        cout << "\nTime Taken: "<< (end_time - start_time)<< " seconds\n";
    }

    // Sequential DFS
    void sequentialDFS(int start) {

        vector<bool> visited(V, false);
        stack<int> st;

        double start_time = omp_get_wtime();

        st.push(start);

        cout << "\nSequential DFS: ";

        while (!st.empty()) {

            int node = st.top();
            st.pop();

            if (!visited[node]) {

                visited[node] = true;
                //cout << node << " ";

                for (int neighbor : adj[node]) {

                    if (!visited[neighbor]) {
                        st.push(neighbor);
                    }
                }
            }
        }

        double end_time = omp_get_wtime();

        cout << "\nTime Taken: "<< (end_time - start_time)<< " seconds\n";
    }

    // Parallel DFS using OpenMP
    void parallelDFS(int start) {

        vector<bool> visited(V, false);
        stack<int> st;

        double start_time = omp_get_wtime();

        st.push(start);

        cout << "\nParallel DFS: ";

        while (!st.empty()) {

            int node;

            #pragma omp critical
            {
                node = st.top();
                st.pop();
            }

            if (!visited[node]) {

                visited[node] = true;

                //cout << node << " ";

                #pragma omp parallel for
                for (int i = 0; i < (int)adj[node].size(); i++) {

                    int neighbor = adj[node][i];

                    if (!visited[neighbor]) {

                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                st.push(neighbor);
                            }
                        }
                    }
                }
            }
        }

        double end_time = omp_get_wtime();

        cout << "\nTime Taken: "<< (end_time - start_time)<< " seconds\n";
    }
};

int main() {

    srand(time(0));

    int vertices = 100000;
    int edges = 300000;

    Graph g(vertices);

    // Random graph generation
    for (int i = 0; i < edges; i++) {

        int u = rand() % vertices;
        int v = rand() % vertices;

        if (u != v) {
            g.addEdge(u, v);
        }
    }
    cout << "Vertices: " << vertices << endl;
    cout << "Edges: " << edges << endl;

    int start = 0;

    g.sequentialBFS(start);
    g.parallelBFS(start);

    g.sequentialDFS(start);
    g.parallelDFS(start);

    return 0;
}
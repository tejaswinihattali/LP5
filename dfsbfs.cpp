#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

class Graph
{
    int vertices;
    vector<vector<int>> adj;

public:
    Graph(int v)
    {
        vertices = v;
        adj.resize(v);
    }

    // Add edge in undirected graph
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ================= SEQUENTIAL DFS =================
    void sequentialDFS(int start)
    {
        vector<int> visited(vertices, 0);

        cout << "\nSequential DFS Traversal: ";
        dfsUtil(start, visited);
        cout << endl;
    }

    void dfsUtil(int node, vector<int>& visited)
    {
        visited[node] = 1;

        cout << node << " ";

        for (int nbr : adj[node])
        {
            if (!visited[nbr])
            {
                dfsUtil(nbr, visited);
            }
        }
    }

    // ================= PARALLEL DFS =================
    void parallelDFS(int start)
    {
        vector<int> visited(vertices, 0);

        cout << "\nParallel DFS Traversal: ";

        #pragma omp parallel
        {
            #pragma omp single
            {
                parallelDFSUtil(start, visited);
            }
        }

        cout << endl;
    }

    void parallelDFSUtil(int node, vector<int>& visited)
    {
        bool alreadyVisited = false;

        #pragma omp critical
        {
            if (visited[node])
            {
                alreadyVisited = true;
            }
            else
            {
                visited[node] = 1;
                cout << node << " ";
            }
        }

        if (alreadyVisited)
            return;

        for (int nbr : adj[node])
        {
            #pragma omp task
            parallelDFSUtil(nbr, visited);
        }

        #pragma omp taskwait
    }

    // ================= SEQUENTIAL BFS =================
    void sequentialBFS(int start)
    {
        vector<int> visited(vertices, 0);
        queue<int> q;

        q.push(start);
        visited[start] = 1;

        cout << "\nSequential BFS Traversal: ";

        while (!q.empty())
        {
            int front = q.front();
            q.pop();

            cout << front << " ";

            for (int nbr : adj[front])
            {
                if (!visited[nbr])
                {
                    visited[nbr] = 1;
                    q.push(nbr);
                }
            }
        }

        cout << endl;
    }

    // ================= PARALLEL BFS =================
    void parallelBFS(int start)
    {
        vector<int> visited(vertices, 0);

        vector<int> currentLevel;
        currentLevel.push_back(start);

        visited[start] = 1;

        cout << "\nParallel BFS Traversal: ";

        while (!currentLevel.empty())
        {
            vector<int> nextLevel;

            #pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); i++)
            {
                int node = currentLevel[i];

                #pragma omp critical
                {
                    cout << node << " ";
                }

                for (int nbr : adj[node])
                {
                    #pragma omp critical
                    {
                        if (!visited[nbr])
                        {
                            visited[nbr] = 1;
                            nextLevel.push_back(nbr);
                        }
                    }
                }
            }

            currentLevel = nextLevel;
        }

        cout << endl;
    }
};

int main()
{
    // Smaller graph for smooth execution
    int v = 10;

    Graph g(v);

    // Creating graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 7);
    g.addEdge(4, 7);
    g.addEdge(5, 8);
    g.addEdge(6, 9);

    double start, end;

    // ================= PARALLEL DFS =================
    start = omp_get_wtime();

    g.parallelDFS(0);

    end = omp_get_wtime();

    cout << "Time taken by Parallel DFS: "
         << end - start << " seconds\n";

    // ================= PARALLEL BFS =================
    start = omp_get_wtime();

    g.parallelBFS(0);

    end = omp_get_wtime();

    cout << "Time taken by Parallel BFS: "
         << end - start << " seconds\n";

    // ================= SEQUENTIAL DFS =================
    start = omp_get_wtime();

    g.sequentialDFS(0);

    end = omp_get_wtime();

    cout << "Time taken by Sequential DFS: "
         << end - start << " seconds\n";

    // ================= SEQUENTIAL BFS =================
    start = omp_get_wtime();

    g.sequentialBFS(0);

    end = omp_get_wtime();

    cout << "Time taken by Sequential BFS: "
         << end - start << " seconds\n";

    return 0;
}

// #include <bits/stdc++.h>
// #include <omp.h>

// using namespace std;

// class Graph
// {
//     int vertices;
//     vector<vector<int>> adj;

// public:
//     Graph(int v)
//     {
//         vertices = v;
//         adj.resize(v);
//     }

//     // Add edge
//     void addEdge(int u, int v)
//     {
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     // ================= SEQUENTIAL DFS =================
//     void sequentialDFS(int start)
//     {
//         vector<int> visited(vertices, 0);

//         cout << "\nSequential DFS Traversal: ";
//         dfsUtil(start, visited);
//         cout << endl;
//     }

//     void dfsUtil(int node, vector<int>& visited)
//     {
//         visited[node] = 1;

//         cout << node << " ";

//         for (int nbr : adj[node])
//         {
//             if (!visited[nbr])
//             {
//                 dfsUtil(nbr, visited);
//             }
//         }
//     }

//     // ================= PARALLEL DFS =================
//     void parallelDFS(int start)
//     {
//         vector<int> visited(vertices, 0);

//         cout << "\nParallel DFS Traversal: ";

//         #pragma omp parallel
//         {
//             #pragma omp single
//             {
//                 parallelDFSUtil(start, visited);
//             }
//         }

//         cout << endl;
//     }

//     void parallelDFSUtil(int node, vector<int>& visited)
//     {
//         bool alreadyVisited = false;

//         #pragma omp critical
//         {
//             if (visited[node])
//             {
//                 alreadyVisited = true;
//             }
//             else
//             {
//                 visited[node] = 1;
//                 cout << node << " ";
//             }
//         }

//         if (alreadyVisited)
//             return;

//         for (int nbr : adj[node])
//         {
//             #pragma omp task
//             parallelDFSUtil(nbr, visited);
//         }

//         #pragma omp taskwait
//     }

//     // ================= SEQUENTIAL BFS =================
//     void sequentialBFS(int start)
//     {
//         vector<int> visited(vertices, 0);
//         queue<int> q;

//         q.push(start);
//         visited[start] = 1;

//         cout << "\nSequential BFS Traversal: ";

//         while (!q.empty())
//         {
//             int front = q.front();
//             q.pop();

//             cout << front << " ";

//             for (int nbr : adj[front])
//             {
//                 if (!visited[nbr])
//                 {
//                     visited[nbr] = 1;
//                     q.push(nbr);
//                 }
//             }
//         }

//         cout << endl;
//     }

//     // ================= PARALLEL BFS =================
//     void parallelBFS(int start)
//     {
//         vector<int> visited(vertices, 0);

//         vector<int> currentLevel;
//         currentLevel.push_back(start);

//         visited[start] = 1;

//         cout << "\nParallel BFS Traversal: ";

//         while (!currentLevel.empty())
//         {
//             vector<int> nextLevel;

//             #pragma omp parallel for
//             for (int i = 0; i < currentLevel.size(); i++)
//             {
//                 int node = currentLevel[i];

//                 #pragma omp critical
//                 {
//                     cout << node << " ";
//                 }

//                 for (int nbr : adj[node])
//                 {
//                     #pragma omp critical
//                     {
//                         if (!visited[nbr])
//                         {
//                             visited[nbr] = 1;
//                             nextLevel.push_back(nbr);
//                         }
//                     }
//                 }
//             }

//             currentLevel = nextLevel;
//         }

//         cout << endl;
//     }
// };

// int main()
// {
//     int v = 10;

//     Graph g(v);

//     // Create graph
//     g.addEdge(0, 1);
//     g.addEdge(0, 2);
//     g.addEdge(1, 3);
//     g.addEdge(1, 4);
//     g.addEdge(2, 5);
//     g.addEdge(2, 6);
//     g.addEdge(3, 7);
//     g.addEdge(4, 7);
//     g.addEdge(5, 8);
//     g.addEdge(6, 9);

//     double start, end;

//     // Parallel DFS
//     start = omp_get_wtime();

//     g.parallelDFS(0);

//     end = omp_get_wtime();

//     cout << "Time taken by Parallel DFS: "
//          << end - start << " seconds\n";

//     // Parallel BFS
//     start = omp_get_wtime();

//     g.parallelBFS(0);

//     end = omp_get_wtime();

//     cout << "Time taken by Parallel BFS: "
//          << end - start << " seconds\n";

//     // Sequential DFS
//     start = omp_get_wtime();

//     g.sequentialDFS(0);

//     end = omp_get_wtime();

//     cout << "Time taken by Sequential DFS: "
//          << end - start << " seconds\n";

//     // Sequential BFS
//     start = omp_get_wtime();

//     g.sequentialBFS(0);

//     end = omp_get_wtime();

//     cout << "Time taken by Sequential BFS: "
//          << end - start << " seconds\n";

//     return 0;
// }
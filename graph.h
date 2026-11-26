
/*
*  autor: Gerardo Silva Esqueda
*  fecha: 23/11/2026
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int edgesList;
    int edgesMat;
    int nodes;
    int rows;
    int cols;
    vector<int> *adjList;
    int *adjMatrix;

    string printPath(int start, int goal, const vector<int> &parent) {
        stack<int> path;
        int current = goal;

        while (current != -1) {
            path.push(current);
            if (current == start) {
                break;
            }
            current = parent[current];
        }

        if (path.empty() || path.top() != start) {
            return "";
        }

        stringstream aux;
        while (!path.empty()) {
            aux << " " << path.top();
            path.pop();
        }
        return aux.str();
    }

public:
    Graph() {
        edgesList = 0;
        edgesMat = 0;
        nodes = 0;
        rows = 0;
        cols = 0;
        adjList = NULL;
        adjMatrix = NULL;
    }

    Graph(int n) {
        edgesList = 0;
        edgesMat = 0;
        nodes = n;
        rows = 0;
        cols = 0;
        adjList = new vector<int>[nodes];
        adjMatrix = NULL;
    }

    ~Graph() {
        delete[] adjList;
        delete[] adjMatrix;
    }

    void addEdgeAdjList(int u, int v) {
        if (u < 0 || v < 0 || u >= nodes || v >= nodes || adjList == NULL) {
            return;
        }

        bool exists = false;
        for (int i = 0; i < (int)adjList[u].size(); i++) {
            if (adjList[u][i] == v) {
                exists = true;
            }
        }
        if (!exists) {
            adjList[u].push_back(v);
            edgesList++;
        }

        if (u != v) {
            exists = false;
            for (int i = 0; i < (int)adjList[v].size(); i++) {
                if (adjList[v][i] == u) {
                    exists = true;
                }
            }
            if (!exists) {
                adjList[v].push_back(u);
            }
        }
    }

    void addEdgeAdjMatrix(int u, int v) {
        if (u < 0 || v < 0 || u >= rows || v >= cols || adjMatrix == NULL) {
            return;
        }

        if (adjMatrix[u * cols + v] == 0) {
            edgesMat++;
        }
        adjMatrix[u * cols + v] = 1;
        if (v < rows && u < cols) {
            adjMatrix[v * cols + u] = 1;
        }
    }

    void loadGraphList(string input, int n) {
        delete[] adjList;
        nodes = n;
        edgesList = 0;
        adjList = new vector<int>[nodes];

        stringstream aux(input);
        char open, comma, close;
        int u, v;
        while (aux >> open >> u >> comma >> v >> close) {
            addEdgeAdjList(u, v);
        }

        for (int i = 0; i < nodes; i++) {
            sort(adjList[i].begin(), adjList[i].end());
        }
    }

    void loadGraphMat(string input, int r, int c) {
        delete[] adjMatrix;
        rows = r;
        cols = c;
        edgesMat = 0;
        adjMatrix = new int[rows * cols]();

        stringstream aux(input);
        char open, comma, close;
        int u, v;
        while (aux >> open >> u >> comma >> v >> close) {
            addEdgeAdjMatrix(u, v);
        }
    }

    string printAdjList() {
        stringstream aux;
        for (int i = 0; i < nodes; i++) {
            aux << "vertex " << i << " : ";
            for (int j = 0; j < (int)adjList[i].size(); j++) {
                aux << adjList[i][j] << " ";
            }
        }
        return aux.str();
    }

    string printAdjMat() {
        stringstream aux;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                aux << adjMatrix[i * cols + j] << " ";
            }
        }
        return aux.str();
    }

    string printAdjMat_clean() {
        stringstream aux;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                aux << adjMatrix[i * cols + j];
                if (j + 1 < cols) {
                    aux << " ";
                }
            }
            if (i + 1 < rows) {
                aux << "\n";
            }
        }
        return aux.str();
    }

    string DFS(int start, int goal) {
        if (start < 0 || goal < 0 || start >= nodes || goal >= nodes) {
            return "visited: path:";
        }

        vector<int> visited(nodes, 0);
        vector<int> parent(nodes, -1);
        stack<int> pending;
        stringstream aux;
        aux << "visited:";
        pending.push(start);

        while (!pending.empty()) {
            int current = pending.top();
            pending.pop();

            if (visited[current]) {
                continue;
            }
            visited[current] = 1;
            aux << " " << current;

            if (current == goal) {
                break;
            }

            for (int i = 0; i < (int)adjList[current].size(); i++) {
                int neighbor = adjList[current][i];
                if (!visited[neighbor]) {
                    parent[neighbor] = current;
                    pending.push(neighbor);
                }
            }
        }

        aux << " path:";
        if (visited[goal]) {
            aux << printPath(start, goal, parent);
        }
        return aux.str();
    }

    string BFS(int start, int goal) {
        if (start < 0 || goal < 0 || start >= nodes || goal >= nodes) {
            return "visited: path:";
        }

        vector<int> visited(nodes, 0);
        vector<int> parent(nodes, -1);
        queue<int> pending;
        stringstream aux;
        aux << "visited:";
        visited[start] = 1;
        pending.push(start);

        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();
            aux << " " << current;

            if (current == goal) {
                break;
            }

            for (int i = 0; i < (int)adjList[current].size(); i++) {
                int neighbor = adjList[current][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    parent[neighbor] = current;
                    pending.push(neighbor);
                }
            }
        }

        aux << " path:";

        if (visited[goal]) {
            aux << printPath(start, goal, parent);
        }
        return aux.str();
    }
};

#endif

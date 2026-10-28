#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>
#include <algorithm>
#include <iomanip>

#define INF 1000000000

using namespace std;

// for dealing with edge
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        if (weight != other.weight) return weight < other.weight;
        return u < other.u;
    }
};
// for kruskal find-set disjoint-set
struct DisjointSet {
    vector<int> parent;
    DisjointSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_j] = root_i;
    }
};

//breath search
bool BFS(Graph* graph, char option, int vertex)
{
    if (!graph || vertex < 0 || vertex >= graph->getSize()) return false;

    
    ofstream* fout = graph->getOfstream();
    if (!fout) return false;

    vector<bool> visited(graph->getSize(), false);//is it visited?
    queue<int> q;//after vistied insert-> until empthy

    visited[vertex] = true;
    q.push(vertex);

    *fout << "========BFS========" << endl;
    if (option == 'O') *fout << "Directed Graph BFS" << endl;
    else *fout << "Undirected Graph BFS" << endl;
    *fout << "Start: " << vertex << endl;

    bool first = true;
    while (!q.empty())//end situatiin
    {
        int curr = q.front();// reset search node
        q.pop();//delete search node-> before remember

        if (!first) *fout << " -> ";
        *fout << curr;
        first = false;

        map<int, int> neighbors;//connected edge
        if (option == 'O') graph->getAdjacentEdgesDirect(curr, &neighbors);
        else graph->getAdjacentEdges(curr, &neighbors);

        for (auto const& iter : neighbors) {
            int next_v = iter.first;
            if (!visited[next_v]) {
                visited[next_v] = true;
                q.push(next_v);//insert after visited
            }
        }
    }
    *fout << endl << "===================" << endl << endl;
    return true;
}
//similar to bfs, not queue, just use stack
bool DFS(Graph* graph, char option, int vertex)
{
    if (!graph || vertex < 0 || vertex >= graph->getSize()) return false;
    ofstream* fout = graph->getOfstream();

    vector<bool> visited(graph->getSize(), false);
    stack<int> s;//until empty

    s.push(vertex);

    *fout << "========DFS========" << endl;
    if (option == 'O') *fout << "Directed Graph DFS" << endl;
    else *fout << "Undirected Graph DFS" << endl;
    *fout << "Start: " << vertex << endl;

    bool first = true;
    while (!s.empty())//end situation 
    {
        int curr = s.top();//reallocate
        s.pop();

        if (visited[curr]) continue;//visited after realloacate
        visited[curr] = true;

        if (!first) *fout << " -> ";
        *fout << curr;
        first = false;

        map<int, int> neighbors;
        if (option == 'O') graph->getAdjacentEdgesDirect(curr, &neighbors);
        else graph->getAdjacentEdges(curr, &neighbors);

        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            int next_v = it->first;
            if (!visited[next_v]) {
                s.push(next_v);// insert data struct
            }
        }
    }
    *fout << endl << "===================" << endl << endl;
    return true;
}
//just edge for min heap
bool Kruskal(Graph* graph)
{
    if (!graph) return false;
    ofstream* fout = graph->getOfstream();
    int size = graph->getSize();

    vector<Edge> edges;
    for (int i = 0; i < size; i++) {
        map<int, int> neighbors;
        graph->getAdjacentEdges(i, &neighbors);
        for (auto const& iter : neighbors) {
            if (i < iter.first) {
                edges.push_back({ i, iter.first, iter.second });
            }
        }
    }

    sort(edges.begin(), edges.end());

    DisjointSet ds(size);//before declare
    vector<Edge> mst;
    int cost = 0;
    //find -> is it diffrent parent?-> unite
    for (const auto& e : edges) {
        if (ds.find(e.u) != ds.find(e.v)) {
            ds.unite(e.u, e.v);//unite-> not consisering vertex num.
            mst.push_back(e);//visited edge
            cost += e.weight;//after select new cost.
        }
    }

    if (size > 1 && mst.size() < size - 1) return false;

    *fout << "========KRUSKAL========" << endl;

    vector<map<int, int>> mstAdj(size);
    for (const auto& e : mst) {
        mstAdj[e.u][e.v] = e.weight;// insert array until all edge allocated
        mstAdj[e.v][e.u] = e.weight;
    }

    for (int i = 0; i < size; i++) {
        *fout << "[" << i << "]";
        for (auto const& iter : mstAdj[i])//iterator for print 
        {
            *fout << " " << iter.first << "(" << iter.second << ")";//print for log.txt
        }
        *fout << endl;
    }

    *fout << "Cost: " << cost << endl;// min cost
    *fout << "=======================" << endl << endl;
    return true;
}
//for min A to B, not negetive edge
bool Dijkstra(Graph* graph, char option, int vertex)
{
    if (!graph || vertex < 0 || vertex >= graph->getSize()) return false;// negetive edge, no vertex is in here graph--> error code
    ofstream* fout = graph->getOfstream();
    int size = graph->getSize();//repeat vertex-1// for connect all vertex

    for (int i = 0; i < size; i++) {
        map<int, int> neighbors;
        if (option == 'O') graph->getAdjacentEdgesDirect(i, &neighbors);
        else graph->getAdjacentEdges(i, &neighbors);
        for (auto const& iter : neighbors) {
            if (iter.second < 0) return false;
        }
    }

    vector<int> dist(size, INF);
    vector<int> parent(size, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[vertex] = 0;
    pq.push({ 0, vertex });

    while (!pq.empty()) // until min heap disappear
    {
        int d = pq.top().first;//new distance
        int curr = pq.top().second;//current node
        pq.pop();

        if (d > dist[curr]) continue;//if minimum cost? drop min heap index-> decrease num of min heap

        map<int, int> neighbors;
        if (option == 'O') graph->getAdjacentEdgesDirect(curr, &neighbors);
        else graph->getAdjacentEdges(curr, &neighbors);
        //reallocate dist array
        for (auto const& iter : neighbors) {
            int next_v = iter.first;
            int weight = iter.second;
            if (dist[curr] + weight < dist[next_v])//curr dist should be allocated + weight should be alocated. then comapre which is cheaper 
            {
                dist[next_v] = dist[curr] + weight;// new dist, --> could change until repeat vertex-1 repeat
                parent[next_v] = curr;//new parent
                pq.push({ dist[next_v], next_v });
            }
        }
    }
    //print part
    *fout << "========DIJKSTRA========" << endl;
    if (option == 'O') *fout << "Directed Graph Dijkstra" << endl;
    else *fout << "Undirected Graph Dijkstra" << endl;
    *fout << "Start: " << vertex << endl;

    for (int i = 0; i < size; i++) {
        if (i == vertex) {
            *fout << "[" << i << "] " << i << " (0)" << endl;
        }
        else if (dist[i] == INF) {
            *fout << "[" << i << "] x" << endl;
        }
        else {
            *fout << "[" << i << "] ";
            vector<int> path;
            int temp = i;
            while (temp != -1) {
                path.push_back(temp);
                temp = parent[temp];
            }
            for (int k = path.size() - 1; k >= 0; k--) {
                *fout << path[k];
                if (k > 0) *fout << " -> ";
            }
            *fout << " (" << dist[i] << ")" << endl;
        }
    }
    *fout << "========================" << endl << endl;
    return true;
}
//dikstra plus negetive edge
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex)
{
    if (!graph || s_vertex >= graph->getSize() || e_vertex >= graph->getSize()) return false;
    ofstream* fout = graph->getOfstream();
    int size = graph->getSize();//for using repeat vertex num in threee for loop

    vector<int> dist(size, INF);
    vector<int> parent(size, -1);
    dist[s_vertex] = 0;

    vector<Edge> edges;
    for (int i = 0; i < size; i++)// allocate edge that exist
    {
        map<int, int> neighbors;
        if (option == 'O') graph->getAdjacentEdgesDirect(i, &neighbors);
        else graph->getAdjacentEdges(i, &neighbors);
        for (auto const& iter : neighbors) {
            edges.push_back({ i, iter.first, iter.second });
        }
    }

    for (int i = 0; i < size - 1; i++)//repeat vertex-1 because when 1 repaet 1 edged could occur
    {
        for (const auto& e : edges)//repaet all enge then compare existed distance 
        {
            if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.weight;//new short path
                parent[e.v] = e.u;//reallocate connect realation
            }
        }
    }

    for (const auto& e : edges)
    {
        if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
            return false;
        }
    }
    //print
    *fout << "========BELLMANFORD========" << endl;
    if (option == 'O') *fout << "Directed Graph Bellman-Ford" << endl;
    else *fout << "Undirected Graph Bellman-Ford" << endl;

    if (dist[e_vertex] == INF) {
        *fout << "x" << endl;
    }
    else {
        vector<int> path;
        int temp = e_vertex;
        while (temp != -1) {
            path.push_back(temp);
            temp = parent[temp];
        }
        for (int k = path.size() - 1; k >= 0; k--) {
            *fout << path[k];
            if (k > 0) *fout << " -> ";
        }
        *fout << endl << "Cost: " << dist[e_vertex] << endl;
    }
    *fout << "===========================" << endl << endl;
    return true;
}
// all A to B that can occur so, no starting point but not having length, just two dimension array
bool FLOYD(Graph* graph, char option)
{
    if (!graph) return false;
    ofstream* fout = graph->getOfstream();
    int size = graph->getSize();

    vector<vector<int>> dist(size, vector<int>(size, INF));//two dimension array for length + shorttest path 

    for (int i = 0; i < size; i++) {
        dist[i][i] = 0;
        map<int, int> neighbors;
        if (option == 'O') graph->getAdjacentEdgesDirect(i, &neighbors);
        else graph->getAdjacentEdges(i, &neighbors);

        for (auto const& iter : neighbors) {
            if (iter.second < dist[i][iter.first]) {
                dist[i][iter.first] = iter.second;
            }
        }
    }
    //compare with fixed stopping area k, after 1 k reapeat k path must be shorttest path
    for (int k = 0; k < size; k++) 
    {
        for (int i = 0; i < size; i++)// i and j can be switched 
        {
            for (int j = 0; j < size; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF)// two dist , must be allocated before 
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];// new shortest path + length
                    }
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (dist[i][i] < 0) return false;
    }
    //print area
    *fout << "========FLOYD========" << endl;
    if (option == 'O') *fout << "Directed Graph Floyd" << endl;
    else *fout << "Undirected Graph Floyd" << endl;

    *fout << "\t";
    for (int i = 0; i < size; i++) *fout << "[" << i << "]" << (i == size - 1 ? "" : "\t");
    *fout << endl;

    for (int i = 0; i < size; i++) {
        *fout << "[" << i << "]\t";
        for (int j = 0; j < size; j++) {
            if (dist[i][j] == INF) *fout << "x";
            else *fout << dist[i][j];
            if (j < size - 1) *fout << "\t";
        }
        *fout << endl;
    }
    *fout << "=====================" << endl << endl;
    return true;
}
// after floyd, find centrality by using mathamtical calculation
bool Centrality(Graph* graph) {
    if (!graph) return false;
    ofstream* fout = graph->getOfstream();
    int size = graph->getSize();

    vector<vector<int>> dist(size, vector<int>(size, INF));

    for (int i = 0; i < size; i++) {
        dist[i][i] = 0;
        map<int, int> neighbors;
        graph->getAdjacentEdges(i, &neighbors);
        for (auto const& iter : neighbors) {
            if (iter.second < dist[i][iter.first]) {
                dist[i][iter.first] = iter.second;
            }
        }
    }
    // doing floyd
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (dist[i][i] < 0) return false;
    }
    // calculate part
    vector<pair<double, int>> values(size);
    double maxVal = -1.0;

    for (int i = 0; i < size; i++) {
        double sum = 0;
        bool disconnected = false;
        for (int j = 0; j < size; j++) {
            if (i == j) continue;
            if (dist[i][j] == INF) {
                disconnected = true;
                break;
            }
            sum += dist[i][j];//all shortest path cost
        }

        if (disconnected || sum == 0) {
            values[i] = { -1.0, (int)sum };
        }
        else {
            values[i] = { (double)(size - 1) / sum, (int)sum };// first part== calculated value, second part--> minimum path
            if (values[i].first > maxVal) maxVal = values[i].first;
        }
    }
    //print part
    *fout << "========CENTRALITY========" << endl;
    for (int i = 0; i < size; i++) {
        *fout << "[" << i << "] ";
        if (values[i].first < 0) {
            *fout << "x" << endl;
        }
        else {
            *fout << (size - 1) << "/" << values[i].second;
            if (abs(values[i].first - maxVal) < 1e-9) *fout << " <- Most Central";
            *fout << endl;
        }
    }
    *fout << "==========================" << endl << endl;

    return true;
}
#include "ListGraph.h"
#include <iostream>
#include <utility>

using namespace std;


ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
    m_List = new map<int, int>[size];
    kw_graph = nullptr; 
}


ListGraph::~ListGraph()
{
    if (m_List) {
        delete[] m_List;
    }
   
}


//for ubdirected graph, for return edge
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
    if (vertex < 0 || vertex >= m_Size) return;

 
    // insert connection information in map,(current-> next)
    for (auto const& iter : m_List[vertex]) {
        m->insert({ iter.first, iter.second });
    }

   
     // insert connection information in map,(current<- next)
    for (int i = 0; i < m_Size; i++) {
        if (i == vertex) continue;

      
        // find vertex in i
        auto it = m_List[i].find(vertex);
        if (it != m_List[i].end()) {
           
            // for und directed, allocate i-> next, next->i too.
            m->insert({ i, it->second });
        }
    }
}


//directed for edge
void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
    if (vertex < 0 || vertex >= m_Size) return;

    //copy m_List[vertex] 
    for (auto const& iter : m_List[vertex]) {
        m->insert({ iter.first, iter.second });
    }
}

// adding edge
void ListGraph::insertEdge(int from, int to, int weight)
{
    if (from < 0 || from >= m_Size || to < 0 || to >= m_Size) return;

   
    // if edge already allocated, drop edge,allocate to map[key]
    m_List[from][to] = weight;
}

// print graph
bool ListGraph::printGraph(ofstream* fout)
{
   
    if (!fout || !fout->is_open()) return false;

    for (int i = 0; i < m_Size; i++) {
        *fout << "[" << i << "]";
        if (m_List[i].empty()) *fout << " ->"; // vertex without outgoing edges

        // already sorting in map, so just print
        for (auto const& iter : m_List[i]) {
            
            // print arriving part, and  weight
            *fout << " -> (" << iter.first << "," << iter.second << ")";
        }
        *fout << endl;
    }
    return true;
}
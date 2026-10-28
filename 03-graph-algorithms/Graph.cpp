#include "Graph.h"

Graph::Graph(bool type, int size)
{
    m_Type = type;
    m_Size = size;
    m_pFout = nullptr; 
}

Graph::~Graph()
{
   
}

bool Graph::getType() { return m_Type; }
int Graph::getSize() { return m_Size; }

// for print log,txt
void Graph::setOfstream(ofstream* fout) {
    m_pFout = fout;
}

ofstream* Graph::getOfstream() {
    return m_pFout;
}
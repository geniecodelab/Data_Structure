#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
    //allocate two dimension array
    m_Mat = new int* [size];
    for (int i = 0; i < size; i++) {
        m_Mat[i] = new int[size];
        // initialize
        for (int j = 0; j < size; j++) {
            m_Mat[i][j] = 0;
        }
    }
}

MatrixGraph::~MatrixGraph()
{
    if (m_Mat) {
        for (int i = 0; i < m_Size; i++) {
            delete[] m_Mat[i];
        }
        delete[] m_Mat;
    }
}

// gaining undirected 
void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
    if (vertex < 0 || vertex >= m_Size) return;

    for (int i = 0; i < m_Size; i++) {
        if (i == vertex) continue; //considering self repeat

        // current -> next or next-> current
        if (m_Mat[vertex][i] != 0) {
            m->insert({ i, m_Mat[vertex][i] });
        }
        else if (m_Mat[i][vertex] != 0) {
            m->insert({ i, m_Mat[i][vertex] });
        }
    }
}

// for directed graph
void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
    if (vertex < 0 || vertex >= m_Size) return;

    for (int i = 0; i < m_Size; i++) {
        if (m_Mat[vertex][i] != 0) {
            m->insert({ i, m_Mat[vertex][i] });
        }
    }
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
    if (from < 0 || from >= m_Size || to < 0 || to >= m_Size) return;

    m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream* fout)
{
    if (!fout || !fout->is_open()) return false;

    //print header
    *fout << "\t";
    for (int i = 0; i < m_Size; i++) {
        *fout << "[" << i << "]";
        if (i < m_Size - 1) *fout << "\t";
    }
    *fout << endl;

    //print in matrix
    for (int i = 0; i < m_Size; i++) {
        *fout << "[" << i << "]\t";
        for (int j = 0; j < m_Size; j++) {
            *fout << m_Mat[i][j];
            if (j < m_Size - 1) *fout << "\t";
        }
        *fout << endl;
    }

    return true;
}
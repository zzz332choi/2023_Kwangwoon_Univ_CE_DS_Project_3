#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
    m_Mat = new int* [size];

    for(int i= 0; i< size; i++) {
        m_Mat[i] = new int [size];
        memset(m_Mat[i], 0, sizeof(int) * size);        
    }

   // fill(&m_Mat[0][0], &m_Mat[size-1][size-1] + 1, 0); // init
}

MatrixGraph::~MatrixGraph()
{
    for(int i=0; i < getSize(); i++) delete[] m_Mat[i];
    delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	
    for (int i = 0; i < this->getSize(); i++) {
        if (m_Mat[vertex - 1][i] || m_Mat[i][vertex - 1]) { // If the weight is non-zero
            if (m_Mat[vertex - 1][i]) m->insert({ i + 1, m_Mat[vertex - 1][i] });
            else m->insert({ i + 1, m_Mat[i][vertex - 1] });
        }
    }
}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
    for (int i = 0; i < this->getSize(); i++) {
        if (m_Mat[vertex - 1][i]) { // If the weight is non-zero
            m->insert({ i + 1, m_Mat[vertex - 1][i] });
        }
    }
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream *fout)	
{
	if(!m_Mat) return false;

    *fout << "========PRINT========" << endl;

    *fout << "\t   ";

    for(int i = 1; i <= getSize(); i++) *fout << '[' << i << "] ";

    *fout << endl;

    for(int i = 1; i <= getSize(); i++) {
        *fout << '[' << i << "]  " ;

        // Output in left-hand alignment
        for(int j = 0; j < getSize(); j++) {
            fout->width(4);
            *fout << m_Mat[i - 1][j];
        }

        *fout << endl;
    }

    *fout << "=====================" << endl << endl;

    return true;
}

vector<int>* MatrixGraph::get_kw_graph()
{
    return nullptr;
}

bool MatrixGraph::set_kw_graph()
{
    return false;
}

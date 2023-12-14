#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_List = new map<int, int> [size];
}

ListGraph::~ListGraph()	
{
	if(m_List) delete[] m_List;
    if (kw_graph) delete[] kw_graph;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
    // find in & out edge
    for (int i = 0; i < this->getSize(); i++) {
        if (i != vertex - 1) {
            if (m_List[i].find(vertex) != m_List[i].end()) { // found
                m->insert({ i+1, m_List[i].find(vertex)->second});
            }
        }
        else { // i == vertex - 1
            for (auto it = m_List[vertex - 1].begin(); it != m_List[vertex - 1].end(); it++) {
                m->insert({ it->first, it->second });
            }
        }
    }

}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
    // find out edge
    for (auto it = m_List[vertex - 1].begin(); it != m_List[vertex - 1].end(); it++) {
        m->insert({ it->first, it->second });
    }
}

void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
    m_List[from - 1].insert({ to, weight });
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
	if(!m_List) return false;

    *fout << "========PRINT========" << endl;

    for(int i = 0; i < getSize(); i++) {
        *fout << '[' << i + 1 << ']';

        for(auto iter = m_List[i].begin(); iter != m_List[i].end(); iter++)
            *fout << " -> (" << iter->first << ',' << iter->second << ')'; 

        *fout << endl;
    }

    *fout << "=====================" << endl << endl;

    return true;
}

vector<int>* ListGraph::get_kw_graph()
{
    return kw_graph;
}

bool ListGraph::set_kw_graph()
{
    if (!m_List) return false;

    // allocation
    kw_graph = new vector<int>[this->getSize() + 1];

    // find in & out edge
    for (int i = 1; i <= this->getSize(); i++) {
        for (int j = 1; j <= this->getSize(); j++) {
            if (m_List[i - 1].find(j) != m_List[i - 1].end()) { // found
                if (find(kw_graph[i].begin(), kw_graph[i].end(), j) == kw_graph[i].end()) { // not found
                    kw_graph[i].push_back(j);
                }
                if (find(kw_graph[j].begin(), kw_graph[j].end(), i) == kw_graph[j].end()) { // not found
                    kw_graph[j].push_back(i);
                }
            }
        }
    }

    return true;
}

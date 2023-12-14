#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

bool BFS(Graph* graph, char option, int vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if(vertex > graph->getSize() || vertex <= 0) return false; 

    queue <int> q;
    vector <int> v;
    bool* visited = new bool [graph->getSize()];
    memset(visited, false, sizeof(bool) * graph->getSize()); // init

    map<int, int>* m = new map<int, int>[graph->getSize()];

    if (option == 'Y') { // directed
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdgesDirect(i, m + (i - 1));
        }
    }
    else if (option == 'N') { // undirected
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdges(i, m + (i - 1));
        }
    }

    else { // Invalid option
        delete[] m;
        delete[] visited;
        return false;
    }

    q.push(vertex);
    visited[vertex - 1] = 1;
    v.push_back(vertex);

    while (!q.empty()) {
        int num = q.front();
        q.pop();

        for (auto iter = m[num - 1].begin(); iter != m[num - 1].end(); iter++) {
            if (!visited[iter->first - 1]) { // Nodes not yet visited
                visited[iter->first - 1] = true;
                v.push_back(iter->first);
                q.push(iter->first);
            }
        }
    }

    *fout << "======== BFS ========" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph BFS result" << endl;
    *fout << "startvertex: " << vertex << endl;

    for (int i = 0; i < v.size(); i++) {
        *fout << v[i];
        if (i != v.size() - 1) *fout << " -> ";
    }

    *fout << endl << "=====================" << endl << endl;

    delete[] m;
    delete[] visited;

    return true;
}

bool DFS(Graph* graph, char option, int vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if (vertex > graph->getSize() || vertex <= 0) return false;

    stack <int> sta;
    vector <int> v;
    bool* visited = new bool[graph->getSize()];
    memset(visited, false, sizeof(bool) * graph->getSize()); // init

    map<int, int>* m = new map<int, int>[graph->getSize()];

    if (option == 'Y') { // directed
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdgesDirect(i, m + (i - 1));
        }
    }
    else if (option == 'N') { // undirected
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdges(i, m + (i - 1));
        }
    }

    else { // Invalid option
        delete[] m;
        delete[] visited;
        return false;
    }

    sta.push(vertex);
    visited[vertex - 1] = 1;
    v.push_back(vertex);

    while (!sta.empty()) {
        int num = sta.top();
        sta.pop();

        for (auto iter = m[num - 1].begin(); iter != m[num - 1].end(); iter++) {
            if (!visited[iter->first - 1]) { // Nodes not yet visited
                visited[iter->first - 1] = true;
                sta.push(num);
                sta.push(iter->first);
                v.push_back(iter->first);
                break;
            }
        }
    }

    *fout << "======== DFS ========" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph DFS result" << endl;
    *fout << "startvertex: " << vertex << endl;

    for (int i = 0; i < v.size(); i++) {
        *fout << v[i];
        if (i != v.size() - 1) *fout << " -> ";
    }

    *fout << endl << "=====================" << endl << endl;

    delete[] m;
    delete[] visited;

    return true;
 }

bool Kruskal(Graph* graph, ofstream* fout)
{

    if (!graph->getSize()) return false;

    vector <W> v;

    map<int, int>* m = new map<int, int>[graph->getSize()];

    for (int i = 1; i <= graph->getSize(); i++) {
        graph->getAdjacentEdges(i, m + (i - 1));
        for (auto it = m[i - 1].begin(); it != m[i - 1].end(); it++) {
            W a;
            a.w = it->second;
            a.s = i;
            a.e = it->first; //, it->first };
            if(it->second) v.push_back(a);
        }
    }
    
    // sort
    quicksort(v, 0, v.size() - 1);
     
    int* parent = new int[(graph->getSize() + 1)];
    memset(parent, -1, sizeof(int) * ((graph->getSize() + 1))); // initialization

    int cost = 0;

    //for(int i=0; i<v.size(); i++) cout << v[i].w << ' ' << v[i].s << ' ' << v[i].e << endl;

    map<int, int>* sol = new map<int, int>[graph->getSize()];
 
    int edges = 0;// , prev_edges = 0;
    int cnt = 0;

    // for (int i = 0; i < graph->getSize(); i++) {
    //     for (auto it = m[i].begin(); it != m[i].end(); it++) {
    //         if (it->second < 0) { // Negative Weight Found
    //             // deallocation
    //             delete[] parent;
    //             delete[] sol;
    //             delete[] m;
    //             return false;
    //         }
    //     }
    // }

    while (edges < v.size() && cnt < graph->getSize() - 1) {
        W e = v[edges++];

        int S = e.s; // start
        int E = e.e; // end
        
        // find set?
        int p = collapsingfind(parent, S);
        int q = collapsingfind(parent, E);

        if (p != q) { // Cycle not formed
            weightedunion(parent, p, q); // union
            sol[S - 1].insert({ E, e.w });
            sol[E - 1].insert({ S, e.w });
            cost += e.w;
            cnt++;
        }

        //edges++;

        //if (!check(parent)) break; // found mst
        //if (edges == graph->getSize()) break;
        //if (cnt == graph->getSize() - 1) break;
    }

    // If no MST has been created
    //if (check(parent)) { // fault
    if (cnt < graph->getSize() - 1) { // fault
        delete[] parent;
        delete[] m;
        delete[] sol;

        return false;
    }

    *fout << "======= Kruskal =======" << endl;

    for (int i = 0; i < graph->getSize(); i++) {
        *fout << '[' << i + 1 << "]     ";

        for (auto it = sol[i].begin(); it != sol[i].end(); it++) {
            *fout << it->first << '(' << it->second << ')';
        }

        *fout << endl;
    }


    *fout << "cost: " << cost << endl;
    *fout << "=====================" << endl << endl;

    delete[] parent;
    delete[] m;
    delete[] sol;

    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if (vertex > graph->getSize() || vertex <= 0) return false;
   
    map<int, int>* m = new map<int, int>[graph->getSize()];
    vector <int> *v = new vector<int>[graph->getSize()]; // save path
    // vector is not empty = the node visited

    int* dist = new int[graph->getSize()];

    // initialization
    // memset(dist, inf, sizeof(int) * graph->getSize()); 
    // infinite := 1,000,000,000 (1Billion)
    for (int i = 0; i < graph->getSize(); i++) dist[i] = inf;
    
    dist[vertex - 1] = 0; // self

    if (option == 'Y') { // directed
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdgesDirect(i, m + (i - 1));
        }
    }
    else if (option == 'N') { // undirected
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdges(i, m + (i - 1));
        }
    }

    else { // Invalid option
        delete[] dist;
        delete[] v;
        delete[] m;
        //delete[] visited;
        return false;
    }


    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it = m[i].begin(); it != m[i].end(); it++) {
            if (it->second < 0) { // Negative Weight Found
                // deallocation
                delete[] dist;
                delete[] v;
                delete[] m;
                return false;
            }
        }
    }

    // initialize
    for (auto it = m[vertex - 1].begin(); it != m[vertex - 1].end(); it++) {
        dist[it->first - 1] = it->second;
        //v[it->second - 1].push_back(vertex);
    }
    
    int* prev = new int[graph->getSize()];
    memset(prev, -1, sizeof(int) * graph->getSize());

    v[vertex - 1].push_back(vertex);

    for (int i = 0; i < graph->getSize() - 1; i++) {
        // deterine n-1 paths from vertex

        int u = -1;

        // get small node
		int min = inf;
		
		for (int j = 0; j < graph->getSize(); j++) {
			if (dist[j] < min && v[j].empty()) {
				min = dist[j];
				u = j;
			}
		}

        if (u < 0) break; // no more path


        if (prev[u] == -1) {
            prev[u] = vertex;
            v[u].push_back(vertex);
        }
        else for (int j = 0; j < v[prev[u] - 1].size(); j++) { // save the path
            v[u].push_back(v[prev[u] - 1][j]);
        }

        v[u].push_back(u + 1);

        for (int j = 0; j < graph->getSize(); j++) { // Update for non-visited nodes
            if (v[j].empty()) {
                if (m[u].find(j + 1) != m[u].end()) {
                    if (dist[u] + m[u].find(j + 1)->second < dist[j]) {
                        dist[j] = dist[u] + m[u].find(j + 1)->second;
                        prev[j] = u + 1;

                        //if (m[u].find(j + 1)->second < 0) { // Negative Weight Found
                        //    flag = true; 
                        //    break;
                        //}
                    }
                }
            }
        }
    }

    *fout << "======= Dijkstra =======" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph Dijkstra result" << endl;
    *fout << "startvertex: " << vertex << endl;

    for (int i = 0; i < graph->getSize(); i++) {
        if (i == vertex - 1) continue; // exception start vertex

        *fout << '[' << i + 1 << "] ";

        if (v[i].empty()) *fout << 'x' << endl;
        else {
            for (int j = 0; j < v[i].size(); j++) {
                *fout << v[i][j];
                
                if (j != v[i].size() - 1) *fout << " -> ";
                else *fout << " (" << dist[i] << ')' << endl;
            }
        }

    }

    *fout << "=====================" << endl << endl;

    // deallocation
    delete[] prev;
    delete[] dist;
    delete[] v;
    delete[] m;
   //delete[] visited;

    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if (s_vertex > graph->getSize() || s_vertex <= 0) return false;
    else if (e_vertex > graph->getSize() || e_vertex <= 0) return false;

    map<int, int>* m = new map<int, int>[graph->getSize()];
    //vector <int>* v = new vector<int>[graph->getSize()]; // save path
    // vector is not empty = the node visited

    int* dist = new int[graph->getSize()];
    int* prev = new int[graph->getSize()];

    // initialization
    // memset(dist, inf, sizeof(int) * graph->getSize()); 
    // infinite := 1,000,000,000 (1Billion)
    for (int i = 0; i < graph->getSize(); i++) {
        dist[i] = inf;
        prev[i] = -1;
    }

    dist[s_vertex - 1] = 0; // self
    prev[s_vertex - 1] = 0;

    if (option == 'Y') { // directed
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdgesDirect(i, m + (i - 1));
        }
    }
    else if (option == 'N') { // undirected
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdges(i, m + (i - 1));
        }
    }

    else { // Invalid option
        delete[] dist;
       // delete[] v;
        delete[] m;
        delete[] prev;
        //delete[] visited;
        return false;
    }

    vector <W> edges;

    // Add for all edges
    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it = m[i].begin(); it != m[i].end(); it++) {
            W a;
            a.w = it->second;
            a.s = i + 1;
            a.e = it->first; //, it->first };
            //if(it->second) v.push_back(a);
            edges.push_back(a);
        }
    }

    for (auto it = m[s_vertex - 1].begin(); it != m[s_vertex - 1].end(); it++) {
        dist[it->first - 1] = it->second;
        prev[it->first - 1] = s_vertex;
    }

   // bool flag = 0; // negative cycle

    for (int i = 0; i <= graph->getSize(); i++) {
        for (int j = 0; j < edges.size(); j++) {
            int s = edges[j].s;
            int e = edges[j].e;
            int w = edges[j].w;

            if (dist[s - 1] == inf) continue; // If there is no incoming edge
            if (dist[e - 1] > dist[s - 1] + w) {
                dist[e - 1] = dist[s - 1] + w;
                prev[e - 1] = s;
	
				// negative cycle
                if (i == graph->getSize()) {
                    delete[] dist;
                    delete[] m;
                    delete[] prev;
                    return false;
                }
            }
        }
    }

    stack <int> sta;
    sta.push(e_vertex);

    int pos = e_vertex;

    while (pos != s_vertex && pos >= 0) {
        pos = prev[pos - 1];
        sta.push(pos);
    }

    *fout << "======= Bellman-Ford =======" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph Bellman-Ford result" << endl;
    if (pos < 0) *fout << "x" << endl;


    else {
        while (!sta.empty()) {
            *fout << sta.top();
            sta.pop();

            if (!sta.empty()) *fout << " -> ";
            else *fout << endl;
        }

        *fout << "cost: " << dist[e_vertex - 1] << endl;
    }
   
    *fout << "=====================" << endl << endl;

    delete[] dist;
    delete[] m;
    delete[] prev;
    return true;
}

bool FLOYD(Graph* graph, char option, ofstream* fout)
{
    map<int, int>* m = new map<int, int>[graph->getSize()];
    
    if (option == 'Y') { // directed
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdgesDirect(i, m + (i - 1));
        }
    }
    else if (option == 'N') { // undirected
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdges(i, m + (i - 1));
        }
    }

    else {
        delete[] m;
        return false;
    }

    int** table = new int* [graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++) {
        table[i] = new int[graph->getSize()];
        for (int j = 0; j < graph->getSize(); j++) {
            if (i != j) table[i][j] = inf;
            else table[i][j] = 0;
        }
        for (auto it = m[i].begin(); it != m[i].end(); it++) {
            table[i][it->first - 1] = it->second;
        }
    }

    for (int k = 0; k < graph->getSize(); k++)
        for (int i = 0; i < graph->getSize(); i++)
            for (int j = 0; j < graph->getSize(); j++)
                if (table[i][k] != inf && table[k][j] != inf)
                    table[i][j] = min(table[i][j], table[i][k] + table[k][j]);

    // negative cycle
    for (int i = 0; i < graph->getSize(); i++) {
        if (table[i][i] < 0) {
            for (int j = 0; j < graph->getSize(); j++) delete[] table[j];
            delete[] table;
            delete[] m;
            return false;
        }
    }


    *fout << "======= FLOYD =======" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph FLOYD result" << endl;

    *fout << "\t   ";

    for (int i = 1; i <= graph->getSize(); i++) *fout << '[' << i << "] ";

    *fout << endl;

    for (int i = 1; i <= graph->getSize(); i++) {
        *fout << '[' << i << "]  ";

        // Output in left-hand alignment
        for (int j = 0; j < graph->getSize(); j++) {
            fout->width(4);
            if (table[i - 1][j] == inf) *fout << 'x';
            else *fout << table[i - 1][j];
        }

        *fout << endl;
    }


    *fout << "=====================" << endl << endl;

    //deallocation
    for (int i = 0; i < graph->getSize(); i++) {
        delete[] table[i];
    }

    delete[] m;
    delete[] table;

    return true;
}



int collapsingfind(int* parent, int i)
{
    // Find the root of the tree containing element i.
    // Use the collapsing rule to collapse all nodes from i to the root.
    int r = i;
    for (; parent[r] >= 0; r = parent[r]); // find root
    while (i != r) { // collapse
        int s = parent[i];
        parent[i] = r;
        i = s;
    }
    return r;
}

void weightedunion(int* parent, int i, int j)
{
    // union sets with roots i and j, i != j, using the weighting rule
    // parent[i] = -count[i] and parent[j] = -count[j]
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]) { // i has fewer nodes
        parent[i] = j;
        parent[j] = temp;
    }
    else { // j has fewer nodes (or i and j have the same number of nodes)
        parent[j] = i;
        parent[i] = temp;    
    }
}

int simplefind(int* parent, int i)
{
    while (parent[i] >= 0) i = parent[i];
    return i;
}

void simpleunion(int* parent, int i, int j)
{
    parent[i] = j;
}

void quicksort(vector<W>& arr, int low, int high) // quick sort
{
    if (low < high) {
        if (high - low + 1 <= 6) // segment_size is 6
            insertionsort(arr, low, high);

        else {
            int i = low;
            int j = high + 1;
            W pivot = arr[low];
            do {
                do i++;  while (arr[i].w < pivot.w);
                do j--;  while (arr[j].w > pivot.w);
                if (i < j) swap(arr[i], arr[j]);
            } while (i < j);
            swap(arr[low], arr[j]);

            quicksort(arr, low, j - 1);
            quicksort(arr, j + 1, high);
        }
    }
}

void insertionsort(vector<W>& arr, int low, int high) // insertion sort
{
    for (int i = low + 1; i <= high; i++) {
        int j = i - 1;
        W key = arr[i];

        while (j >= low && key.w < arr[j].w) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int init(int s, int e, int c, int* arr) // Building a Segment Tree
{
    if (s == e) return arr[c] = 1;
    int mid = (s + e) / 2;

    return arr[c] = init(s, mid, c * 2, arr) + init(mid + 1, e, c * 2 + 1, arr);
}

int sum(int s, int e, int c, int left, int right, int* arr) // Estimate the sum of intervals
{
    if (left > e || right < s) return 0;
    if (left <= s && e <= right) return arr[c];
    int mid = (s + e) / 2;

    return sum(s, mid, c * 2, left, right, arr) + sum(mid + 1, e, c * 2 + 1, left, right, arr);
}

void update(int s, int e, int c, int index, int dif, int* arr) // Update interval sum
{
    if (index < s || index > e) return;

    arr[c] += dif;
    if (s == e) return;
    int mid = (s + e) / 2;
    update(s, mid, c * 2, index, dif, arr);
    update(mid + 1, e, c * 2 + 1, index, dif, arr);
}

bool check(bool* arr, int size) // Make sure you have visited all nodes
{
    int cnt = 0;
    for (int i = 1; i <= size; i++) if(arr[i]) cnt++;
    return cnt != size;
}

bool KWANGWOON(Graph* graph, int vertex, ofstream* fout) { // kwangwoon search 

    if (graph->getType()) return false; // If the type of graph is matrix
    if (!graph->set_kw_graph()) return false; 

    if(graph->getSize() < 1) return false;

    vector<int>* kw_graph = graph->get_kw_graph(); // allocate

    for (int i = 1; i <= graph->getSize(); i++) { // sort
        sort(kw_graph[i].begin(), kw_graph[i].end());
    }

    pair<int, int>* p = new pair<int, int>[graph->getSize() + 1];

    int** tree = new int*[graph->getSize() + 1];
    for (int i = 1; i <= graph->getSize(); i++) {
        tree[i] = new int[kw_graph[i].size() * 4];
        memset(tree[i], 0, sizeof(int) * kw_graph[i].size() * 4);
        p[i] = { 0, kw_graph[i].size() - 1 };
        if(kw_graph[i].size()) init(0, kw_graph[i].size() - 1, 1, tree[i]);
    }

    bool* visited = new bool[graph->getSize() + 1];
    memset(visited, false, graph->getSize() + 1);
    visited[1] = true;
    
    int prev = 1;

    vector <int> v; // Save the order of visited nodes
    v.push_back(prev);

    //while (check(visited, graph->getSize())) 
    for(int k=0; k<graph->getSize(); k++) {
        for (int i = 1; i <= graph->getSize(); i++) {
            if(!visited[i]) {
                auto it = find(kw_graph[i].begin(), kw_graph[i].end(), prev);
                // newnew
                if (it != kw_graph[i].end()) {
                    update(0, kw_graph[i].size() - 1, 1, it - kw_graph[i].begin(), -1, tree[i]);

                    while (sum(0, kw_graph[i].size() - 1, 1, p[i].second, p[i].second, tree[i]) == 0 && p[i].first <= p[i].second) p[i].second--;
                    while (sum(0, kw_graph[i].size() - 1, 1, p[i].first, p[i].first, tree[i]) == 0 && p[i].first <= p[i].second) p[i].first++;

                }
                //if (it != kw_graph[i].end()) kw_graph[i].erase(it);
                //delete[] tree[i];
                //tree[i] = new int[kw_graph[i].size() * 4];
                //memset(tree[i], 0, sizeof(int) * kw_graph[i].size() * 4);
                //if(kw_graph[i].size()) init(0, kw_graph[i].size() - 1, 1, tree[i]);
            }
        }

        if (tree[prev][1] == 0) break; // Abnormal termination

        if (tree[prev][1] % 2) // Number of nodes that can go is odd
        {
            prev = kw_graph[prev][p[prev].second];
        }//prev = kw_graph[prev][kw_graph[prev].size() - 1];
        
        else // Number of nodes that can go is even
        {
            prev = kw_graph[prev][p[prev].first];
        }//prev = kw_graph[prev][0];

        if(visited[prev]) break;
        
        v.push_back(prev);
        visited[prev] = true;
    }

    if (v.empty()) { // Abnormal termination
        for (int i = 1; i <= graph->getSize(); i++) if (tree[i]) delete[] tree[i];
        delete[] tree;
        delete[] visited;
        delete[] p;
        return false;
    }

    *fout << "======= KWANGWOON =======" << endl;
    *fout << "startvertex: 1" << endl;

    for (int i = 0; i < v.size(); i++) {
        *fout << v[i];
        if (i != v.size() - 1) *fout << " -> ";
        else *fout << endl;
    }

    *fout << "=========================" << endl << endl;
    for (int i = 1; i <= graph->getSize(); i++) if(tree[i]) delete[] tree[i];
    delete[] tree;
    delete[] visited;
    delete[] p;
    return true;
}
#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#define inf 1000000000 //1Billion
#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, char option, int vertex, ofstream* fout);
bool DFS(Graph* graph, char option,  int vertex, ofstream* fout);     
bool KWANGWOON(Graph* graph, int vertex, ofstream* fout);  
bool Kruskal(Graph* graph, ofstream* fout);
bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout);    //Dijkstra
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout); //Bellman - Ford
bool FLOYD(Graph* graph, char option, ofstream* fout);   //FLoyd

// my
int collapsingfind(int* parent, int i); // find method
void weightedunion(int* parent, int i, int j); // union method

int simplefind(int* parent, int i);
void simpleunion(int* parent, int i, int j);

bool check(bool* arr, int size);

struct W {
    int w = 0, s = 0, e = 0; // weight, start, end
};

void quicksort(vector<W>& arr, int low, int high);
void insertionsort(vector<W>& arr, int low, int high);

int init(int s, int e, int c, int* arr);
int sum(int s, int e, int c, int left, int right, int* arr);
void update(int s, int e, int c, int index, int dif, int* arr);
#endif

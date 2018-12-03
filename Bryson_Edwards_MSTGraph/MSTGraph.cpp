// MSTGraph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include "llist.h"
#include "Edge.h"
#include "Graph.h"
#include <iostream>
#include <string>

using namespace std;
Graph* Prim(Graph* G, int* D, int s);
void AddEdgetoMST(Graph* G, int from, int to, int weight);
int minVertex(Graph* G, int* D);
int main()
{
	// Variable List
	int holder;
	int j = 0;
	int DIMENSIONS;
	ifstream input("Text.txt");
	if (!input.is_open())
	{cerr << "Unable to open file"; return(1);}

	
	input >> DIMENSIONS;
	int *key = new int[DIMENSIONS];
	Graph* graph = new Graph(DIMENSIONS);


	// Input Data
	for (int i = 0; input >> holder && i < DIMENSIONS; i++)
	{
		if (i >= j) // Read Diagonally 
		{
			if (holder != 0)
			{
				graph->setEdge(i, j, holder);
				graph->setEdge(j, i, holder);
			}
		}
		if (i == DIMENSIONS-1) {j++; i = -1;}
	}
	
	// Print for base graph
	cout << "Number of vertices are " << graph->n() << endl;
	cout << "Number of edges are " << graph->e() << endl;
	graph->print(false);

	// Print for new graphs made after Prim's algorithm
	Prim(graph, key, 0)->print(true, "MST0"); 
	Prim(graph, key, 2)->print(true, "MST2");
	Prim(graph, key, 4)->print(true, "MST4");
	system("pause");
    return 0;
}

Graph* Prim(Graph* G, int* D, int s) { // Prim’s MST algorithm
	cout << "Begin MST starting at " << s << endl;
	G->reInitMark();
	Graph* MSTGraph = new Graph(6);
	int V[6]; // Store closest vertex
	int i, w;
	for (int i = 0; i<G->n(); i++) // Initialize
		D[i] = INFINITY;
	D[s] = 0;
	for (i = 0; i<G->n(); i++) 
	{ 
		// Process the vertices
		int v = minVertex(G, D);
		G->setMark(v, 1);
		if (v != s)
		{
			AddEdgetoMST(MSTGraph, V[v], v, G->weight(V[v], v));
			AddEdgetoMST(MSTGraph, v, V[v], G->weight(V[v], v));
			cout << "From " << V[v] << " to " << v << endl;
		}
			 // Add edge to MST
		if (D[v] == INFINITY) return MSTGraph; // Unreachable vertices
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
		{
			if (D[w] > G->weight(v, w)) 
			{
				D[w] = G->weight(v, w); // Update distance
				V[w] = v; // Where it came from
			}
		}
	}
	cout << "End of MST " << endl << endl;
	return MSTGraph; // return a graph for easy .print() use
}

void AddEdgetoMST(Graph* G, int from, int to, int weight)
{
	G->setEdge(from, to, weight);
}

int minVertex(Graph* G, int* D)
{ // Find min cost vertex
	int i, v = -1;
	// Initialize v to some unvisited vertex
	for (i = 0; i<G->n(); i++)
		if (G->getMark(i) == 0) { v = i; break; }
	for (i++; i<G->n(); i++) // Now find smallest D value
		if ((G->getMark(i) == 0) && (D[i] < D[v]))
			v = i;
	return v;
}


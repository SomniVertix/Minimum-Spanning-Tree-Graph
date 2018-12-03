#ifndef GRAPH_HPP
#define	GRAPH_HPP

#include "GraphADT.h"

using namespace std;
class Graph: public GraphADT {
private:
	LList<Edge>** vertex; // List headers
	int numVertex, numEdge; // Number of vertices, edges
	int *mark; // Pointer to mark array
public:
	Graph(int numVert)
	{
		Init(numVert);
	}
	~Graph() { // Destructor
		delete[] mark; // Return dynamically allocated memory
		for (int i = 0; i<numVertex; i++) delete[] vertex[i];
		delete[] vertex;
	}
	void Init(int n) {
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[n]; // Initialize mark array
		for (i = 0; i<numVertex; i++) mark[i] = 0;
		// Create and initialize adjacency lists
		vertex = (LList<Edge>**) new LList<Edge>*[numVertex];
		for (i = 0; i<numVertex; i++)
			vertex[i] = new LList<Edge>();
	}


	int n() { return numVertex; } // Number of vertices
	int e() { return numEdge; } // Number of edges

	int first(int v) { 
		if (vertex[v]->length() == 0)
			return numVertex; // No neighbor
		vertex[v]->moveToStart();
		Edge it = vertex[v]->getValue();
		return it.vertex();
	}

	// Get v’s next neighbor after w
	int next(int v, int w) {
		Edge it;
		if (isEdge(v, w)) {
			if ((vertex[v]->currPos() + 1) < vertex[v]->length()) {
				vertex[v]->next();
				it = vertex[v]->getValue();
				return it.vertex();
			}
		}
		return n(); // No neighbor
	}

	void setEdge(int i, int j, int weight) {
		Assert(weight>0, "May not set weight to 0");
		Edge currEdge(j, weight);
		if (isEdge(i, j)) { // Edge already exists in graph
			vertex[i]->remove();
			vertex[i]->insert(currEdge);
		}
		else 
		{ // Keep neighbors sorted by vertex index
			numEdge++;
			for (vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next()) 
			{
				Edge temp = vertex[i]->getValue();
				if (temp.vertex() > j) break;
			}
		vertex[i]->insert(currEdge);
		}
	}

	void delEdge(int i, int j) { // Delete edge (i, j)
		if (isEdge(i, j)) {
			vertex[i]->remove();
			numEdge--;
		}
	}
	bool isEdge(int i, int j) { 
		//Edge it;
		for (vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next()) { // Check whole list
			Edge temp = vertex[i]->getValue();
			if (temp.vertex() == j) return true;
		}
		return false;
	}
	int weight(int i, int j) { // Return weight of (i, j)
		Edge curr;
		if (isEdge(i, j)) {
			curr = vertex[i]->getValue();
			return curr.weight();
		}
		else return 0;
	}
	int getMark(int v) { return mark[v]; }
	void setMark(int v, int val) { mark[v] = val; }
	bool reInitMark() 
	{
		for (int i = 0; i < numVertex; i++)
		{
			mark[i] = 0;
		}
		return true;
	}
	void print(bool isPassedToFile, string filename = "")
	{	
		ofstream MSTOutput;
		if (isPassedToFile) // If information is going to be passed to a file, then create the file with filename
		{
			MSTOutput.open(filename + ".txt");
			if (!MSTOutput.is_open())
			{
				cerr << "Unable to open file";
				system("pause");
			}
			MSTOutput << numVertex <<  endl;
		}

		cout << numVertex  << endl;

		for (int i = 0; i < n(); i++)
		{
			for (int j = 0; j < n(); j++)
			{
				if (isEdge(i, j))
				{
					cout << weight(i, j); // Print the weight
					if (isPassedToFile)
						MSTOutput << weight(i, j);
				}
				else
				{
					cout << "0"; // Print non-existent edges as 0
					if (isPassedToFile)
						MSTOutput << "0";
				}
				cout << " "; // Print spacing between each collumn
				if (isPassedToFile)
					MSTOutput << " ";
			}
			// Format for 5 collumns
			cout << endl; 
			if (isPassedToFile)
				MSTOutput << endl;
		}
		cout << endl << endl;
		if (isPassedToFile)
			MSTOutput << endl << endl;
		MSTOutput.close();
	}
};
#endif	/* GRAPH_HPP */



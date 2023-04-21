#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char *argv[])
{
    cout << "Filename of graph to load: ";

    // TODO: next five code snippets
    // Snippet 1: read filename and open file
    string filename;
    cin >> filename;

    ifstream inputFile(filename);

    if (!inputFile)
    {
        cout << "Error opening file: " << filename << endl;
        return 1;
    }

    // Snippet 2: get number graph size
    int numVertices, numEdges;
    inputFile >> numVertices, numEdges;

    // Snippet 3: create graph
    Graph graph;
    for (int i = 0; i < numVertices; i++)
        graph.insertVertex(i);

    // Snippet 4: read edges
    for (int i = 0; i < numEdges; i++)
    {
        int l1, l2;
        float weight;
        inputFile >> l1 >> l2 >> weight;
        graph.insertEdge(l1, l2, weight);
    }

    // Snippet 5: read start and end of path
    int startVertex, endVertex;
    inputFile >> startVertex >> endVertex;

    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;

    vector<Vertex *> path;

    // TODO: call shortest path on your graph for the sstart and end verices and save result to path
    path = graph.shortestPath(startVertex, endVertex);
    for (auto i : path)
    { // this is a for-each loop
        cout << i->label << " ";
    }
    // cout endline at very end
    cout << endl;
    return 0;
}

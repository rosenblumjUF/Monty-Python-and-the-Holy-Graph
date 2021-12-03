#include "Graph.h"

Graph::Graph()
{

}

void Graph::insertEdge(string from, string to)
{

}

vector<string> Graph::getAdjacent(string vertex)
{
    return graph[vertex];
}

int Graph::getDegree(string vertex)
{
    return graph[vertex].size();
}

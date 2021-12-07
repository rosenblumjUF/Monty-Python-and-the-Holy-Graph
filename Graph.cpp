#include "Graph.h"

Graph::Graph()
{

}

void Graph::insertEdge(string from, string to)
{

}

vector<string> Graph::getAdjacent(string vertex)
{
    vector<string> neighbors;
    for(int i = 0; i < graph[vertex].size(); i++)
    {
        neighbors.push_back(graph[vertex].at(i).first);
    }
    return neighbors;
}

int Graph::getDegree(string vertex)
{
    return graph[vertex].size();
}

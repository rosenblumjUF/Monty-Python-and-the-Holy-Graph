#include "Graph.h"

Graph::Graph()
{

}

void Graph::insertEdges()
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

int Graph::BFS(string sourceID, string destID, Graph g) {
    return 0;
}

int Graph::Bidirectional(string sourceID, string destID, Graph g) {
    return 0;
}

void Graph::printMovies(vector<string>) {

}

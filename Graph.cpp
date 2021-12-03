#include "Graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using std::string;
using std::pair;
using std::vector;
using std::map;
using std::cout;
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
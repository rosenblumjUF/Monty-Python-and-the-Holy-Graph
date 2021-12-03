#include <iostream>
#include <vector>
#include <string>
#include <map>
using std::string;
using std::pair;
using std::vector;
using std::map;
using std::cout;



#pragma once


class Graph {
    private:
    //Graph as an adjacency list - data member, e.g. Vector, Set, Vector of Vectors, Maps, Lists, etc.
    map<string, vector<pair<string, int>>> graph;

    public:
    void insertEdge(int from, int to, int weight);
    vector<int> getAdjacent(int vertex);
    int getIndegree(int vertex);
    int getOutdegree(int vertex);
};




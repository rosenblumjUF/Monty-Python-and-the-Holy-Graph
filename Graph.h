#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Graph {
    private:
    //Graph as an adjacency list - data member, e.g. Vector, Set, Vector of Vectors, Maps, Lists, etc.
    map<string, vector<string>> graph;

    public:
    Graph();
    void insertEdge(string from, string to);
    vector<string> getAdjacent(string vertex);
    int getDegree(string vertex);

};




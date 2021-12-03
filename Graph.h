#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
using std::string;
using std::pair;
using std::vector;
using std::map;
using std::cout;



class Graph {
    private:
    //Graph as an adjacency list - data member, e.g. Vector, Set, Vector of Vectors, Maps, Lists, etc.
    map<string, vector<pair<string, int>>> graph;

    public:
    Graph();
    void insertEdge(string from, string to);
    vector<int> getAdjacent(string vertex);
    int getDegree(string vertex);

};




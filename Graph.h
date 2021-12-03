#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Graph {
    private:

    // Graph as an adjacency list - data member, e.g. Vector, Set, Vector of Vectors, Maps, Lists, etc.
    // Key is IMDb identifier, value is a vector of pairs where:
    //      first = IMDb identifier of an adjacent actor
    //      second = a vector of movies (using IMDb identifier of movie) that the adjacent actor and key actor are in together
    unordered_map<string, vector<pair<string, vector<string>>>> graph;

    // Unordered maps used to translate IMDb identifier to name of actor or movie
    //      key = IMDb identifier of actor/movie
    //      value = name/title of actor/movie
    unordered_map<string, string> actors;
    unordered_map<string, string> movies;

    // Number of vertices and edges
    int vertices;
    int edges;

    public:
    Graph();
    void insertEdge(string from, string to);
    vector<string> getAdjacent(string vertex);
    int getDegree(string vertex);

};




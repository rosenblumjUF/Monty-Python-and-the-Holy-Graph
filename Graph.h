#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <chrono>

using namespace std;

class Graph {
    private:

    // Graph as an adjacency list - data member, e.g. Vector, Set, Vector of Vectors, Maps, Lists, etc.
    // Key is IMDb identifier, value is a vector of pairs where:
    //      first = IMDb identifier of an adjacent actor
    //      second = a vector of movies (using IMDb identifier of movie) that the adjacent actor and key actor are in together
    unordered_map<string, vector<string>> graph;

    // Unordered maps used to translate IMDb identifier to name of actor or movie
    //      key = IMDb identifier of actor/movie
    //      value = name/title of actor/movie
    unordered_multimap<string, string> actors; // <actor name, id>
    unordered_multimap<string, string> movies; // <id, movie names>
    map<pair<string, string>, vector<string>> adjMovies; //movies connecting each pair

    // Number of vertices and edges
    int vertices = 0;

    void bidirectionalBFS(queue<pair<string,int>>& q, unordered_set<string>& visited, unordered_map<string,string>& previous);
    string findActor(const string& ID);
    string findMovie(const string& ID);
    void BFS(const string& sourceID, const string& destID);
    void bidirectional(const string& sourceID, const string& destID);
    bool checkOverlap(const unordered_set<string>& sourceVisited, const unordered_set<string>& destVisited,
                      const unordered_map<string,string>& sourcePrev, const unordered_map<string,string>& destPrev,
                      const string& sourceID, const string& destID, chrono::time_point<chrono::high_resolution_clock> startTime);
    void printResults(const vector<string>& path, int sep);
    void readData();
    bool isUniqueName(const string& name);



    public:
    Graph();
    void getResults(string src, string dest);
    bool doesActorExist(const string& actor);
    string checkDuplicate(const string& name);
};




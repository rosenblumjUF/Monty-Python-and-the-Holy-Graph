#include "Graph.h"

Graph::Graph()
{

}

void Graph::insertEdges()
{
    ifstream inFile("test2");
    string lineFromFile;
    getline(inFile, lineFromFile); //to account for header in file
    string currMovie = "tt0000009";
    vector<string> adjActors;
    string newMovie;
    string actor;
    while(getline(inFile, lineFromFile))
    {
        istringstream stream(lineFromFile);
        getline(stream, newMovie, ',');
        getline(stream, actor);
        if(newMovie == currMovie)
            adjActors.push_back(actor);
        else
        {
            for(int i = 0; i < adjActors.size(); i++)
            {
                string currVertex = adjActors[i];
                for(int j = 0; j < adjActors.size(); j++)
                {
                    if(i != j)
                    {
                        graph[currVertex].push_back(adjActors[j]);
                        adjMovies[make_pair(currVertex, adjActors[j])].push_back(currMovie);
                    }
                }
            }
            currMovie = newMovie;
            adjActors.clear();
            adjActors.push_back(actor);
        }

    }

    for(int i = 0; i < adjActors.size(); i++)
    {
        string currVertex = adjActors[i];
        for(int j = 0; j < adjActors.size(); j++)
        {
            if(i != j)
            {
                graph[currVertex].push_back(adjActors[j]);
                adjMovies[make_pair(currVertex, adjActors[j])].push_back(currMovie);
            }
        }
    }

}

vector<string> Graph::getAdjacent(string vertex)
{
    return graph[vertex];
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

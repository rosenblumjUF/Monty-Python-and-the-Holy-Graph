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
    vector<string> actors;
    while(getline(inFile, lineFromFile))
    {
        istringstream stream(lineFromFile);
        string newMovie;
        string actor;
        getline(stream, newMovie, ',');
        getline(stream, actor);
        if(newMovie == currMovie)
            actors.push_back(actor);
        else
        {
            for(int i = 0; i < actors.size(); i++)
            {
                string currVertex = actors[i];
                for(int j = 0; j < actors.size(); j++)
                {
                    if(i != j)
                    {
                        graph[currVertex].push_back(actors[j]);
                        adjMovies[currVertex].first = actors[j];
                        adjMovies[currVertex].second.push_back(currMovie);
                    }
                }
            }
            currMovie = newMovie;
            actors.clear();
            actors.push_back(actor);
        }

    }


    for(auto it = adjMovies.begin();  it != adjMovies.end(); it++)
    {
        cout << it->first << ", ";
        cout << it->second.first << endl;
        for (int i = 0; i < it->second.second.size(); i++)
        {
            cout << it->second.second[i] << endl;
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

#include "Graph.h"

Graph::Graph()
{
    ifstream inFile("titles.csv");
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
                        edges++;
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
                edges++;
            }
        }
    }

    readData();

}

void Graph::insertEdges()
{


}

vector<string> Graph::getAdjacent(string vertex)
{
    vector<string> adjVertices;
    for (auto it = adjMovies.begin(); it != adjMovies.end(); it++)
    {
        if (it->first.first == vertex)
            adjVertices.push_back(it->first.second);

    }

//    return graph[vertex];
    return adjVertices;
}

int Graph::getDegree(string vertex)
{
    vector<string> adjVertices = getAdjacent(vertex);
    return adjVertices.size();
}

int Graph::BFS(string sourceID, string destID)
{
    queue<string> q; //vertices to be visited
    set<string> visited; //stores visited vertices
    map<string, int> dist; //stores distance to each visited vertex
    map<string, string> pred; //stores predecessor for each vertex visited
    int degreesOfSep = -1;
    vector<string> moviesOnPath; //stores all movies/edges on path from source to dest
    //initialize:
    q.push(sourceID);
    visited.insert(sourceID);
    dist[sourceID] = 0;
    pred[sourceID] = "";

    //BFS:
    while(!q.empty())
    {
        string u = q.front();
        q.pop();
        vector<string> neighbors = graph[u];
        for(string n : neighbors)
        {
            if(visited.count(n) == 0)
            {
                visited.insert(n);
                dist[n] = dist[u] + 1;
                pred[n] = u;
                q.push(n);

                if(n == destID)//stop BFS, destination has been reached
                {
                    degreesOfSep = dist[n];
                    /*while(n != "")
                    {
                        for(string m : adjMovies[make_pair(pred[n], n)])
                        {
                            moviesOnPath.push_back(m);
                        }
                        n = pred[n];
                    }
                    printMovies(moviesOnPath);*/
                    return degreesOfSep;
                }
            }
        }
    }
    return degreesOfSep;
}

int Graph::Bidirectional(string sourceID, string destID) {

    if (sourceID == destID)
    {
        ////**** WHAT DO I PRINT HERE???
        return 0;
    }

    unordered_set<string> sourceVisited;
    unordered_set<string> destVisited;

    unordered_map<string,string> sourcePrev; // key = node, value = previous node
    unordered_map<string,string> destPrev; // key = node, value = previous node

    queue<string> sourceQueue;
    sourceQueue.push(sourceID);

    queue<string> destQueue;
    destQueue.push(destID);

    vector<string> path;

    bool firstIteration = true;
    while (!sourceQueue.empty() && !destQueue.empty())
    {
        BidirectionalBFS(sourceQueue,sourceVisited,sourcePrev);
        BidirectionalBFS(destQueue,destVisited,destPrev);

        if (firstIteration && destVisited.find(sourceID) != destVisited.end())
        {
            path.emplace_back(sourceID);
            path.emplace_back(destID);

            for (int i = 0; i < path.size(); ++i)
            {
                cout << FindActor(path[i]) << "->";
            }

            return 1;
        }


        for (auto iter = sourceVisited.begin(); iter != sourceVisited.end(); ++iter)
        {
            if (destVisited.find(*iter) != destVisited.end())
            {
                string currID = *iter;
                path.emplace_back(currID);
                //    if (intersect == ID)
                //    {
                //        return path;
                //    }

                while (currID != sourceID)
                {
                    currID = sourcePrev[currID];
                    path.emplace(path.begin(),currID);

                }

                currID = *iter;
                while (currID != destID)
                {
                    currID = destPrev[currID];
                    path.emplace_back(currID);
                }



                for (int i = 0; i < path.size(); ++i)
                {
                    cout << FindActor(path[i]) << "->";
                }

                return path.size() - 1;
            }
        }

        firstIteration = false;
    }


    return -1;
}

void Graph::BidirectionalBFS(queue<string>& q, unordered_set<string>& visited, unordered_map<string,string>& previous)
{
    string currID = q.front();
    vector<string> children = graph[currID];

    for (int i = 0; i < children.size(); ++i)
    {
        if (visited.find(children[i]) == visited.end())
        {
            previous[children[i]] = currID;
            visited.insert(children[i]);
            q.push(children[i]);
        }
    }

    q.pop();
}

string Graph::FindActor(string ID)
{
    for (auto iter = actors.begin(); iter != actors.end(); ++iter)
    {
        if ((*iter).second == ID)
        {
            return (*iter).first;
        }
    }
    return "";
}

void Graph::printMovies(vector<string> moviePath) {
    cout << "MOVIE SUGGESTIONS:" << endl;

    for (int i = 0; i < moviePath.size(); i++) {
        cout << moviePath[i] << endl;
    }
}

void Graph::readData()
{
    //Reads data from movies.csv and store it in the movies map
    ifstream inFile("movies.csv");
    string lineFromFile;
    getline(inFile, lineFromFile); //to account for header in file
    string movieID;
    string movieTitle;

    while(getline(inFile, lineFromFile))
    {
        istringstream stream(lineFromFile);
        getline(stream, movieID, ',');
        getline(stream, movieTitle);
        movies[movieID] = movieTitle;
    }

    inFile.close();

    //Reads data from names.csv and store it in the actors map
    inFile.open("names.csv");
    getline(inFile, lineFromFile); //to account for header in file
    string actorID;
    string actorName;

    while(getline(inFile, lineFromFile))
    {
        istringstream stream(lineFromFile);
        getline(stream, actorID, ',');
        getline(stream, actorName);
        actors[actorName] = actorID;
        vertices++;
    }

}

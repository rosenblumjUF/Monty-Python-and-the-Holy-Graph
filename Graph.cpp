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

void Graph::BFS(const string& sourceID, const string& destID)
{
    //Source: based on algorithms given in class and from https://www.geeksforgeeks.org/shortest-path-unweighted-graph/
    //start time here
    auto startTime = chrono::high_resolution_clock::now();

    queue<string> q; //vertices to be visited
    set<string> visited; //stores visited vertices
    map<string, int> dist; //stores distance to each visited vertex
    map<string, string> pred; //stores predecessor for each vertex visited
    int degreesOfSep = -1;
    vector<string> actorsOnPath; //stores all actors on path from source to dest
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
                    while(n != "") //add actors of path to vector
                    {
                        actorsOnPath.insert(actorsOnPath.begin(), n);
                        n = pred[n];
                    }
                    //time stop here
                    auto endTime = chrono::high_resolution_clock::now();

                    double time = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

                    cout << "~Using BFS Shortest Path~" << endl;
                    cout << "Time taken to complete search: " << time << " microseconds" << endl;
                    printResults(actorsOnPath, degreesOfSep);
                    return;
                }
            }
        }
    }
}

void Graph::bidirectional(const string& sourceID, const string& destID) {

    // Source for Bidirectional stuff: https://www.geeksforgeeks.org/bidirectional-search/

    auto startTime = chrono::high_resolution_clock::now();

    unordered_set<string> sourceVisited;
    unordered_set<string> destVisited;

    unordered_map<string,string> sourcePrev; // key = actor, value = previous actor
    unordered_map<string,string> destPrev; // key = actor, value = previous actor

    queue<pair<string,int>> sourceQueue;
    sourceQueue.push(make_pair(sourceID,0));

    queue<pair<string,int>> destQueue;
    destQueue.push(make_pair(destID,0));

    sourceVisited.insert(sourceID);
    destVisited.insert(destID);

    while (!sourceQueue.empty() && !destQueue.empty())
    {
        bidirectionalBFS(sourceQueue, sourceVisited, sourcePrev);
        if (checkOverlap(sourceVisited, destVisited, sourcePrev, destPrev, sourceID, destID, startTime))
        {
            return;
        }
        bidirectionalBFS(destQueue, destVisited, destPrev);

        if (checkOverlap(sourceVisited, destVisited, sourcePrev, destPrev, sourceID, destID, startTime))
        {
            return;
        }

    }

    vector<string> path;
    printResults(path,-1);
    return;
}

bool Graph::checkOverlap(const unordered_set<string>& sourceVisited, const unordered_set<string>& destVisited,
        const unordered_map<string,string>& sourcePrev, const unordered_map<string,string>& destPrev,
        const string& sourceID, const string& destID, chrono::time_point<chrono::high_resolution_clock> startTime)
{
    vector<string> path;

    for (auto iter = sourceVisited.begin(); iter != sourceVisited.end(); ++iter)
    {
        if (destVisited.find(*iter) != destVisited.end())
        {
            string currID = *iter;
            path.emplace_back(currID);

            while (currID != sourceID)
            {
                currID = sourcePrev.at(currID);
                path.emplace(path.begin(),currID);
            }

            currID = *iter;
            while (currID != destID)
            {
                currID = destPrev.at(currID);
                path.emplace_back(currID);
            }

            auto endTime = chrono::high_resolution_clock::now();

            double time = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

            cout << "~Using Bidirectional Shortest Path~" << endl;
            cout << "Time taken to complete search: " << time << " microseconds" << endl;
            printResults(path,path.size() - 1);

            return true;
        }
    }
    return false;
}

void Graph::bidirectionalBFS(queue<pair<string,int>>& q, unordered_set<string>& visited, unordered_map<string,string>& previous)
{
    int level = q.front().second;
    while (q.front().second == level)
    {
        string currID = q.front().first;
        vector<string> children = graph[currID];

        for (int i = 0; i < children.size(); ++i)
        {
            if (visited.find(children[i]) == visited.end())
            {
                previous[children[i]] = currID;
                visited.insert(children[i]);
                q.push(make_pair(children[i],level + 1));
            }
        }

        q.pop();
    }

}

string Graph::findActor(const string& ID)
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

string Graph::findMovie(const string &ID)
{
    for (auto iter = movies.begin(); iter != movies.end(); ++iter)
    {
        if ((*iter).second == ID)
        {
            return (*iter).first;
        }
    }
    return "";

}

void Graph::printResults(const vector<string>& path, int sep)
{
    if(sep != -1)
    {
        cout << "Degrees of Separation: " << sep << endl;
        cout << "Path from actor 1 to actor 2: " << endl;
        for(int i = 0; i < path.size() - 1; i++)
        {
            cout << "\t" << findActor(path[i]) << " -> " << findActor(path[i + 1]) << endl;
            cout << "\t\tCollaborations: " << endl;
            for(string mov : adjMovies[make_pair(path[i], path[i + 1])])
            {
                cout << "\t\t~ \"" << findMovie(mov) << "\"" << endl;
            }
        }
    }
    else
    {
        cout << "These two actors are not connected, please input two new actors." << endl;
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
//        movies[movieID] = movieTitle;
        movies.insert(make_pair(movieTitle,movieID));
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

        actors.insert(make_pair(actorName,actorID));
        vertices++;
    }

}

void Graph::getResults(string src, string dest)
{
    cout << "--------------------------------------------------" << endl;
    BFS(src, dest);
    cout << "--------------------------------------------------" << endl;
    bidirectional(src, dest);
    cout << "--------------------------------------------------" << endl;
}

bool Graph::doesActorExist(const string& actor)
{
    if (actors.find(actor) != actors.end())
    {
        return true;
    }
    return false;
}

bool Graph::isUniqueName(const string& name)
{
    auto iter = actors.equal_range(name);
    if (++iter.first != iter.second)
    {
        return false;
    }
    return true;
}

string Graph::checkDuplicate(const string& name)
{
    if (isUniqueName(name))
    {
        return actors.find(name)->second;
    }
    else
    {
        cout << "Multiple actors have the name " << name << ". Please type the number corresponding to your selection:" << endl;

        auto iteratorPair = actors.equal_range(name);
        auto iter = iteratorPair.first;
        auto endIter = iteratorPair.second;

        int i = 1;
        for (i; iter != endIter; ++iter,++i)
        {
            cout << i << ". " << iter->first << ", https://www.imdb.com/name/" << iter->second << endl;
        }

        string selectionString = "";


        int selection = 0;
        while (selection == 0)
        {
            getline(cin,selectionString);
            try
            {
                selection = stoi(selectionString);
                if (selection < 1 || selection >= i)
                {
                    selection = 0;
                    throw invalid_argument("");
                }
            }
            catch(invalid_argument& e)
            {
                cout << "Please type a valid number." << endl;
            }
        }

        for (int i = 0; i < selection - 1; ++i)
        {
            ++iteratorPair.first;
        }

        return iteratorPair.first->second;
    }
}


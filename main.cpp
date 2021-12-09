#include "Graph.h"

int main()
{
    Graph g;
    string actor1;
    string actor2;
    cout << "Welcome to Monty Python and the Holy Graph!" << endl;
    cout << "To begin, ";
    while(true)
    {
        cout << "please input a name for actor 1, or type \"exit\" to end the program" << endl;
        cin >> actor1;
        if(!g.doesActorExist(actor1));
        {
            cout << "The actor " << actor1 << ", does not exist in the IMDb database";
        }
        cout << "please input name for actor 2, or type \"exit\" to end the program" << endl;
        cin >> actor2;
        if(!g.doesActorExist(actor2))
        {
            cout << "The actor " << actor2 << ", does not exist in the IMDb database";
        }
        if(actor1 == "exit" || actor2 == "exit")
            break;
        else if(actor1 == actor2)
        {
            cout << "Actor 1 and actor 2 cannot be the same, please try again." << endl;
            continue;
        }
        else
        {
            g.getResults(actor1, actor2);
        }

    }




    return 0;
};


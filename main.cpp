//Course info : COMP 4475 FA - Topics Artificial Intelligence
//Assignment 1 - Part 2 (Search Algorithm)
//Student : Mahsa Fazli - 1271287


#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    vector<char> locations = {'A', 'B', 'C', 'D', 'E', 'F'};

    map<char, vector<char>> graph; //creates a map called graph that will connect one location to a list of its neighbors.
    //this way:
    graph['A'] = {'B', 'C'};
    graph['B'] = {'A', 'D'};
    graph['C'] = {'A', 'D', 'E'};
    graph['D'] = {'B', 'C', 'F'};
    graph['E'] = {'C', 'F'};
    graph['F'] = {'D', 'E'};

    char start = 'A';
    char goal = 'F';

    queue<char> q; //This creates the BFS waiting line called q. being in waiting line means that BFS has discovered but hasn't explored yet (its neighbors aren't checked yet)
    vector<char> visited; //This list remembers places we've already discovered
    map<char, char> parent; //Creates a map called parent where one character connects to another character.First char → key, e.g. 'B' , Second char → value, e.g. 'A' , means B's parent is A.

    q.push(start);
    visited.push_back(start); //adds the value (named start, it can be 'B" for example) to the back of visited vector
                             
    while (!q.empty())
    {
        char current = q.front(); //q.front() looks at the front of the waiting line and store it in a variable called current
        q.pop();

        cout << "Visiting: " << current << endl;

        // Stop when we reach the goal
        if (current == goal)
        {
            break;
        }

        for (char neighbor : graph[current]) //creates a temporary variable called neighbor and says "For each neighbor in the list of neighbors of current...
        {
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) //find(start, end, thing_to_find) here means search "visited vector" from beginning to end for neighbor
            {                                                                  //== visited.end() means it was NOT found.Because find() works like this:
                                                                                //If it finds the item, it returns the item's position.If it doesn't find it, it returns visited.end()
                                                                                  //so this line asks Did find() reach the end without finding it?” → If yes, the condition is true so the {} can be executed
                visited.push_back(neighbor);
                q.push(neighbor);

                // Remember where this neighbor came from
                parent[neighbor] = current;
            }
        }
    }

    // Build the path backwards from F to A
    vector<char> path;

    char current = goal; //this is different than the other current variable. is inside the while loop and means the location BFS is  
                         //currently exploring.When it becomes F, we break out of that loop, and that current stops existing.
                         //this is a new current starting at F, specifically so we can trace the path backward
    while (current != start)
    {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(start);

    // Reverse it so it goes A to F
    reverse(path.begin(), path.end());

    cout << "\nPath found: ";

    for (char location : path)
    {
        cout << location << " ";
    }

    cout << endl;

    return 0;
}
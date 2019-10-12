#include <string> //for strings
#include <iostream> //always include this
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <climits>
#include "Graph.hpp"

using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

/*Establish a single edge from retail1 to retail2. Create an edge with distance equal to
distance and v equal to the address of the vertex with name retail2. Then push back the
edge to the Edges vector of the vertex with name retail1.
*/
void Graph::addEdge(std::string retail1, std::string retail2, int distance)
{
    //if first and second vertex is found, then link them up yee
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == retail1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j].name == retail2)
                {
                    Edge e;
                    e.v = &vertices[j];
                    e.distance = distance;
                    vertices[i].Edges.push_back(e);
                }
            }
        }
    }
}

void Graph::addVertex(string retailName)
{
    bool found = false;

    //search to see if new addition is already in the graph
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == retailName)
        {
            found = true;
            cout << vertices[i].name << " already exists" << endl; //might wanna remove this later
        }
    }
    if (!found)
    {
        vertex v;
        v.name = retailName;
        v.visited = false;
        v.distance_from_start = INT_MAX;
        v.parent = NULL;
        vertices.push_back(v);
    }
}

void Graph::printBFT()
{
    setAllVerticesUnvisited();
    for (int i = 0; i < vertices.size(); i++)
    {
        BFT_traversal(&vertices[i]);
    }

}

void Graph::BFT_traversal(vertex* v)
{

    if (v->visited == false)
    {
        //use stl queue to keep track of vertices to be visited
        v->visited = true;
        cout << v->name << " " << endl;
    }

    queue<vertex*> q;

    //enqueue the starting vertex
    q.push(v);

    //need another vertex pointer
    vertex *n;

    while (!q.empty())
    {
        //q dequeue
        n = q.front();
        q.pop();

        for (int i = 0; i < n->Edges.size(); i++)
        {
            if (n->Edges[i].v->visited == false)
            {
                n->Edges[i].v->visited = true;
                q.push(n->Edges[i].v);
                cout << n->Edges[i].v->name << endl;
            }
        }

    }
    cout << endl;
}

void Graph::printDFT()
{
    setAllVerticesUnvisited();
    for(int i = 0; i < vertices.size(); i++)
    {
        DFT_traversal(&vertices[i]);
    }

}

void Graph::DFT_traversal(vertex *v)
{
    if (v->visited == false)
    {
        v -> visited = true;
        cout << v -> name << endl;
    }

    for (int i = 0; i < v->Edges.size(); i++)
    {
        if ( v->Edges[i].v -> visited == false)
        {
            DFT_traversal(v -> Edges[i].v);
        }
    }
}

void Graph::displayEdges()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].name << endl; //name of vertex

        for (int j = 0; j < vertices[i].Edges.size(); j++)
        {
            cout << "-->";
            cout << vertices[i].Edges[j].v -> name ;//name of edge
            cout << " (" << vertices[i].Edges[j].distance << " miles)" << endl;
        }
        cout << endl;
    }
}

void Graph::setAllVerticesUnvisited()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
}

//stars must be before class name
vertex * Graph::findVertex(std::string name)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == name)
            return &vertices[i];
    }
    return NULL;
}

//this will likely be used for the file reading
//returns number of things that it has split the string into
int split (string str, char c, string array[], int size)
{
    if (str.length() == 0)
    {
         return 0;
     }
    string word = "";
    int count = 0;
    str = str + c;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            if (word.length() == 0)
                continue;
            array[count++] = word;
            word = "";
        }
        else
        {
            word = word + str[i];
        }
    }
    return count;
}

void Graph::readFile(string filename)
{
    ifstream data(filename);
    string line;
    string tempArray[30];
    int num;
    string retail, connectedretail;
    int distance;
    string firstLine[30];

    bool first = true;

    if(data.is_open() == false)
    {
        data.close();
        cout << "Failed to open the file." << endl;
    }
    else
    {
        while(getline(data,line))
        {
            //fill tempArray
            num = split(line, ',', tempArray, 30);

            if (first == true)
            {
                first = false;//only want this if stuff to run once

                //populate the firstLine array so I can always retrieve that info
                for (int i = 0; i < num; i++)
                {
                    firstLine[i] = tempArray[i];

                    //first word is 'cities', so don't store that
                    if (i != 0)
                    {
                        //cout << firstLine[i] << endl;
                        addVertex(firstLine[i]);
                    }
                }
            }
            else
            {
                retail = tempArray[0];
                cout << "... Reading in " << retail << " ";
                for (int j = 1; j < num; j++)
                {
                    connectedretail = firstLine[j];
                    distance = stoi(tempArray[j]);

                    if (distance > 0)
                    {
                        //cout << " ... Reading in " << retail << " -- " << connectedretail << " -- " << distance << endl;
                        cout << " -- "  << connectedretail << " -> " << distance;
                        addEdge(retail, connectedretail, distance);
                    }

                }
                cout << endl;
            }
        }
    }
}

void Graph::choosingShortestPath2(int sa_d, int sb_d, int ab_d, int ba_d)
{
    int total = 0;
    //c1 is start
    //d1 = c1 to c2
    //d2 = c1 to c3
    //d3 = c2 to c3
    // int sa_d = sa->distance_from_start;
    // int sb_d = sb->distance_from_start;
    // int ab_d = ab->distance_from_start;
    // int ba_d = ba->distance_from_start;
    //cout << sa_d << " " << sb_d << " " << ab_d << " " << ba_d << endl;

    if(sa_d < sb_d) //path is S to A to B
    {
        total += printShortestPath(Start_to_A);
        total += printShortestPath(A_to_B);
        cout << "Total distance: " << total << endl;
    }
    else if (sa_d > sb_d) //path is S to B to A
    {
        total += printShortestPath(Start_to_B);
        total += printShortestPath(B_to_A);
        cout << "Total distance: " << total << endl;
        //print Start_to_B using for loops?
        //print A_to_B in reverse using for loops?
        // cout << "Total distance: " << e2 + e3 << endl;
        // cout << "Inefficient path would have total distance " << e1 + e3 << endl;
    }
    else //d1 = d2
    {

        cout << "Order of which retail location to visit first does not matter" << endl;
        total += printShortestPath(Start_to_A);
        total += printShortestPath(A_to_B);
        cout << "Total distance: " << total << endl;
        // cout << "Total distance: " << e1 + e3 << endl;
    }
}


vertex* Graph::shortestPath(string start, string end)
{
  vertex *vStart = findVertex(start);
  vertex * vEnd = findVertex(end);
  for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].distance_from_start = INT_MAX;
    vertices[i].visited = false;
    vertices[i].parent = NULL;
  }

  //set our starting vertex to zero and visited
  vertex *temp;
  temp = vStart;
  temp->distance_from_start = 0;
  temp->visited = true;

  queue<vertex*>q;

  q.push(temp);
  while(!q.empty()){
    vertex *temp2 = q.front();
    //temp2->visited = true;
    q.pop();
    for(int j = 0; j < temp2->Edges.size(); j++)
    {
      if(temp2->Edges[j].v->visited == false)
      {
        //cout << temp2->Edges[j].v->name << endl;
        int alt = temp2->distance_from_start + temp2->Edges[j].distance;
        // cout << "Alt is :" << alt << endl;
        // cout << "Distance from start " << temp2->Edges[j].v->distance_from_start << endl;
        if(alt < temp2->Edges[j].v->distance_from_start)
        {
            temp2->Edges[j].v->parent = temp2;
            temp2->Edges[j].v->distance_from_start = alt;
            q.push(temp2->Edges[j].v);
        }
        // cout << "Distance from start after comparison" << temp2->Edges[j].v->distance_from_start << endl;

        // cout << endl;
      }
      //cout << temp2->Edges[j].v->name<<" distance_from_start: " << temp2->Edges[j].v->distance_from_start << endl;
    }
  }
  return vEnd;
}

int Graph::printShortestPath(vector<vertex> storage)
{
    cout << "Shortest distance from " << storage[0].name << " to " << storage[storage.size()-1].name << " is: ";
    cout << storage[storage.size()-1].distance_from_start << endl;
    cout << "Path: ";

    for (int i = 0; i < storage.size(); i++)
    {
        cout << storage[i].name;
        if (i != storage.size()-1)
            cout << " --> ";
    }
    cout << endl;
    return storage[storage.size()-1].distance_from_start;
}

void Graph::SA_storePath(vertex * end)
{
    //cout << "Start to A: ";
    vector<vertex> storage;
    vertex* temp = end;

    while(temp != NULL)
    {
        storage.push_back(*temp);
        temp = temp->parent;
    }
    for (int i = storage.size()-1 ; i >= 0; i--)
    {
        Start_to_A.push_back(storage[i]);
        //cout << storage[i].name << endl;
    }
}

void Graph::SB_storePath(vertex * end)
{
    ///cout << "Start to B: ";
    vector<vertex> storage;
    vertex* temp = end;

    while(temp != NULL)
    {
        storage.push_back(*temp);
        temp = temp->parent;
    }
    for (int i = storage.size()-1 ; i >= 0; i--)
    {
        Start_to_B.push_back(storage[i]);
        //cout << storage[i].name << endl;
    }
}

void Graph::AB_storePath(vertex * end)
{
    //cout << "A to B: ";
    vector<vertex> storage;
    vertex* temp = end;

    while(temp != NULL)
    {
        storage.push_back(*temp);
        temp = temp->parent;
    }
    for (int i = storage.size()-1 ; i >= 0; i--)
    {
        A_to_B.push_back(storage[i]);
        //cout << storage[i].name << endl;
    }
}

void Graph::BA_storePath(vertex * end)
{
    //cout << "B to A: ";
    vector<vertex> storage;
    vertex* temp = end;

    while(temp != NULL)
    {
        storage.push_back(*temp);
        temp = temp->parent;
    }
    for (int i = storage.size()-1 ; i >= 0; i--)
    {
        B_to_A.push_back(storage[i]);
        //cout << storage[i].name << endl;
    }
}


void Graph::printPath(vertex* path)
{
    vertex * temp = path;
    while (temp != NULL)
    {
        cout << temp->name << "----" ;
        temp = temp->parent;
    }

}

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <list>
#include <queue>
using namespace std;

struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

struct Edge
{
    vertex *v;
    int distance;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    std::string name;
    bool visited;
    std::vector<Edge> Edges; //stores edges to adjacent vertices
    int distance_from_start;
    vertex* parent;
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addVertex(std::string retailName);
    void addEdge(std::string retail1, std::string retail2, int distance);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();

    //print
    int printShortestPath(vector<vertex> storage);

    void readFile(string filename);
    void choosingShortestPath2(int sa_d, int sb_d, int ab_d, int ba_d);
    //vertex* dijkstra(string, string);
    vertex* shortestPath(string one, string two);
    bool is_empty();

    void SA_storePath(vertex * end);
    void SB_storePath(vertex * end);
    void AB_storePath(vertex * end);
    void BA_storePath(vertex * end);

    //new
    vector<vertex> Start_to_A;
    vector<vertex> Start_to_B;
    vector<vertex> A_to_B;
    vector<vertex> B_to_A;

    void printPath(vertex * path);

  private:
    std::vector<vertex> vertices; //stores vertices
    //priority_queue< vertex*, vector<vertex*>, comparator > minHeap;
    vertex *findVertex(std::string name);
    void BFT_traversal(vertex *v);
    void DFT_traversal(vertex *v);

    list <vertex> visitedList;


};

#endif // GRAPH_HPP

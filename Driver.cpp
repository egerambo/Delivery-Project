#include <string> //for strings
#include <iostream> //always include this
#include <cctype> //isdigit
#include <sstream>
#include <fstream>
#include "Graph.hpp"
using namespace std;

//makes sure that the user input is just digits, returns 0 otherwise
string inputCheck(string x)
{
    if (x == "")
        {
            return "0";
        }
    for (int i = 0; i < x.length(); i++)
    {
        if (isdigit(x[i]) == false)
        {
            return "0";
        }
    }
    return x;
}

void displayMenu()
{
    cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << " 1. Read file" << endl;
    cout << " 2. Display retail locations and connections" << endl;
    cout << " 3. Deliver to 1 location" << endl;
    cout << " 4. Deliver to 2 locations" << endl;
    cout << " 5. Quit" << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}



int main(int argc, char const *argv[]) {
    Graph g;
    string choice = "";
    string c1, c2, c3;
    vertex* sa;
    vertex* sb;
    vertex* ab;
    vertex* ba;
    vertex* path;
    int sa_d, sb_d, ab_d, ba_d;

    while (choice != "5")
    {
        displayMenu();
        getline(cin, choice);
        choice = inputCheck(choice);
        switch (stoi(choice))
        {
            case 1://read file
                cout << "Enter filename: " ;
                getline(cin, c1);
                g.readFile(c1);
                break;
            case 2://Display retail locations and connections
                g.displayEdges();
                break;
            case 3://Deliver to 1 location
                g.Start_to_A.clear();
                cout << "Enter start location: " ;
                getline(cin, c1);
                cout << "Enter end retail location: " ;
                getline(cin, c2);

                path = g.shortestPath(c1,c2);
                //g.printPath(path);
                g.SA_storePath(path);
                g.printShortestPath(g.Start_to_A);


                break;
            case 4://deliver to 2 locations
                g.Start_to_A.clear();
                g.Start_to_B.clear();
                g.A_to_B.clear();
                g.B_to_A.clear();

                cout << "Enter start location: " ;
                getline(cin, c1);
                cout << "Enter end retail location 1: " ;
                getline(cin, c2);
                cout << "Enter end retail location 2: " ;
                getline(cin, c3);

                sa = g.shortestPath(c1,c2);
                g.SA_storePath(sa);
                sa_d = sa->distance_from_start;
                //g.printShortestPath(g.Start_to_A);
                //cout << endl;

                sb = g.shortestPath(c1,c3);
                g.SB_storePath(sb);
                //g.printShortestPath(g.Start_to_B);
                sb_d = sb->distance_from_start;
                //cout << endl;

                ab = g.shortestPath(c2,c3);
                g.AB_storePath(ab);
                //g.printShortestPath(g.A_to_B);
                ab_d = ab->distance_from_start;
                //cout << endl;

                ba = g.shortestPath(c3,c2);
                g.BA_storePath(ba);
                //g.printShortestPath(g.B_to_A);
                ba_d = ba->distance_from_start;

                cout << endl;
                g.choosingShortestPath2(sa_d, sb_d, ab_d, ba_d);

                break;
            case 5://quit
                cout << "Good bye!" << endl;
                break;
            default:
                cout << "Invalid Input" << endl;
                break;
        }
    }
    return 0;
}

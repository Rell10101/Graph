

#include <iostream>
//#include "LinkedList.h"
#include "Graph.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    try {


        Graph<int> g(5);

        g.InsertVertex(2);
        g.InsertVertex(4);
        g.InsertVertex(5);
        g.InsertVertex(14);
        g.InsertVertex(15);
        g.InsertVertex(20);

        g.InsertEdge(2, 4, 24);
        g.InsertEdge(2, 5, 25);
        g.InsertEdge(4, 14, 414);
        g.InsertEdge(4, 15, 415);
        g.InsertEdge(5, 20, 50);

        vector<int> v1;
        v1 = g.GetNeighbors(2);

        // перебор в цикле
        for (int n : v1)
            std::cout << n << "\t";
        std::cout << std::endl;


        vector<int> v3 = g.DepthFirstSearch(2);
        for (int item : v3) {
            cout << item << " ";
        }
        std::cout << std::endl;

        vector<int> v4 = g.BreadthFirstSearch(2);
        for (int item : v4) {
            cout << item << " ";
        }
        std::cout << std::endl;

        cout << "\nДейкстра\n";
        vector<int> v5 = g.dijkstra(2);
        for (int item : v5) {
            cout << item << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        // копирование значений из старой матрицы смежности в новую 
        /*for (int i = 0; i < g.maxGraphSize; i++)
        {
            for (int j = 0; j < g.maxGraphSize; j++)
            {
                cout << g.edge[i][j] << " ";
            }
            cout << endl;
        }*/

        
        
    }
    catch (invalid_argument const& ex) {
        cout << ex.what();
    }
}


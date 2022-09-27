#include "Map.cpp"

int main()
{   
    // graph edges array.
    edge edges[] =
    {
        // (x, y) -> edge from x to y
        {0,1},{0,2},{1,4},{2,3},{3,1},{4,3}
    };

    // Number of vertices in the graph
    int N = 6;   

    // Calculation of number of edges
    int n = sizeof(edges)/sizeof(edges[0]);

    // Constructing map
    Map test(edges, n, N);

    // Print adjacency list representation of graph
    cout<<"Printing Map (start_vertex, end_vertex):"<<endl;
    for (int i = 0; i < N; i++)
    {
        // display adjacent territories of territory i
        printNeighbours(test.head[i], i);
    }
    return 0;
}
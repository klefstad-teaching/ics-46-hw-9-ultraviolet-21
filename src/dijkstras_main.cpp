#include "dijkstras.h"

using namespace std;

int main() {
    Graph G;
    file_to_graph("largest.txt", G);
    cout << "done " << endl;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    vector<int> path = extract_shortest_path(distances, previous, 12);
    print_path(path, 0);
}

//fix shortest path
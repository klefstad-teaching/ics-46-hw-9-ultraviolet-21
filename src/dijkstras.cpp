#include <iostream>
#include <iostream>
#include <queue>
#include <vector>


#include "dijkstras.h"

using namespace std;

bool compareByWeight(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second; //inverted for min heap 
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF); 
    vector<bool> visited(G.numVertices, false);

    previous.assign(G.numVertices, -1); //use assign instead of resize
    
    distances[source] = 0;
    previous[source] = -1; //source has no previous value

    priority_queue<pair<int, int>> pq; // pair<vertex, weight> 
    pq.push({source, 0});

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        for (Edge e: G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distances[u] + weight < distances[v] ) {
                distances[v] = distances[u] + weight;
                previous [v] = u;
                pq.push({v, distances[v]});
            }
        }

    }
    return distances;
    
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    stack<int> st;
    for (int v = destination; v > 0; v = previous[v]) {
        st.push(v);
    }
    while (!st.empty()) {
        path.push_back(st.top());
        st.pop();
    }
    return path;
}

//void print_path(const vector<int>& v, int total) - why total?

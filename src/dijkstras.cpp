#include <iostream>
#include <iostream>
#include <queue>
#include <vector>


#include "dijkstras.h"

using namespace std;

struct Node{
	int vertex;
	int weight;
    Node(int v, int w) : vertex(v), weight(w) {} //remove this if it causes errors
    bool operator<(const Node& other) const{
		return weight < other.weight;
	}
	bool operator>(const Node& other) const{
		return weight > other.weight;
	}
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF); 
    vector<bool> visited(G.numVertices, false);

    previous.assign(G.numVertices, -1);
    
    distances[source] = 0;
    previous[source] = -1; //source has no previous value

    priority_queue<Node, vector<Node>, greater<Node>> pq;
	pq.push(Node(source, 0));

    while (!pq.empty()) {
        int u = pq.top().vertex;
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
	vector<int> stack(1, destination);
	while(previous[destination] != -1){
		destination = previous[destination];
		stack.push_back(destination);
	}
	while(stack.size()){
		path.push_back(stack[stack.size()-1]);
		stack.pop_back();
	}
	return path;
}

void print_path(const vector<int>& v, int total) {
    for (auto vertex: v) {
        cout << vertex << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
#ifndef DELIVERYGRAPH_H
#define DELIVERYGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int destination;
    int weight;

    Edge(int d, int w) : destination(d), weight(w) {}
};

class DeliveryGraph {
private:
    int numNodes;
    vector<vector<Edge>> adjacencyList;
    map<int, string> nodeNames;

public:
    DeliveryGraph(int n) : numNodes(n), adjacencyList(n) {}

    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].push_back(Edge(destination, weight));
        adjacencyList[destination].push_back(Edge(source, weight));
    }

    void setNodeName(int node, string name) {
        nodeNames[node] = name;
    }

    string getNodeName(int node) {
        if (nodeNames.find(node) != nodeNames.end()) {
            return nodeNames[node];
        }
      return string("Node ") + to_string(node);

    }

    vector<int> dijkstra(int source, int destination) {
        vector<int> distance(numNodes, INF);
        vector<int> parent(numNodes, -1);
        vector<bool> visited(numNodes, false);

        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> pq;

        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (const Edge& edge : adjacencyList[u]) {
                int v = edge.destination;
                int weight = edge.weight;

                if (!visited[v] && distance[u] != INF &&
                    distance[u] + weight < distance[v]) {

                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    pq.push({distance[v], v});
                }
            }
        }

        vector<int> path;
        if (distance[destination] == INF) {
            return path;
        }

        int current = destination;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());
        return path;
    }

    void displayPath(int source, int destination) {
        vector<int> path = dijkstra(source, destination);

        if (path.empty()) {
            cout << "No path found from " << getNodeName(source)
                 << " to " << getNodeName(destination) << endl;
            return;
        }

        cout << "Shortest Delivery Path:\n";
        cout << "========================\n";

        int totalDistance = 0;

        for (size_t i = 0; i < path.size(); i++) {
            cout << getNodeName(path[i]);

            if (i < path.size() - 1) {
                for (const Edge& edge : adjacencyList[path[i]]) {
                    if (edge.destination == path[i + 1]) {
                        totalDistance += edge.weight;
                        cout << " --(" << edge.weight << " km)--> ";
                        break;
                    }
                }
            }
        }

        cout << endl;
        cout << "Total Distance: " << totalDistance << " km" << endl;
    }
};

#endif

/*
 Name: Jay K. Roy
 Email: jroy4@crimson.ua.edu
 Course Section: Fall 2024 CS 201
 Homework #: 4
 To Compile: g++ -Wall -std=c++20 GraphDemo.cpp -o graph
 To Run: ./graph input1.txt or input2.txt
*/

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Vertex {
public:
    bool visited;
    int distance;
    int previous;
    int finish;
    list<int> adj;
};

class Graph {
public:
    Graph(int V, int E, std::pair<int, int> *edges) {
        _V = V;
        _E = E;
        vertices = new Vertex[_V];
        for (int i = 0; i < _V; i++) {
            vertices[i].visited = false;
            vertices[i].distance = numeric_limits<int>::max();
            vertices[i].previous = -1;
            vertices[i].finish = -1;
        }
        for (int i = 0; i < _E; i++) {
            addEdge(edges[i].first, edges[i].second);
        }
    }

    virtual ~Graph() {
        for (int i=0; i<_V; ++i) {
            auto adj = vertices[i].adj;
            adj.clear(); // clear list
        }

        delete[] vertices; // delete array of vertices
    }

    int V() {
        return _V;
    }

    int E() {
        return _E;
    }

    void addEdge(int u, int v) {
        vertices[u].adj.push_back(v);
    }

    list<int> getEdges(int u) {
        return vertices[u].adj;
    }

    int degree(int u) {
        return vertices[u].adj.size();
    }

    // Breadth-First Search implementation
    void bfs(int s) {
        // Reset vertex states
        for (int i = 0; i < _V; i++) {
            vertices[i].visited = false;
            vertices[i].distance = numeric_limits<int>::max();
            vertices[i].previous = -1;
        }

        // Mark source vertex and initialize its properties
        vertices[s].visited = true;
        vertices[s].distance = 0;
        vertices[s].previous = -1;

        // Create a queue for BFS
        queue<int> Q;
        Q.push(s);

        // BFS traversal
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            // Explore adjacent vertices
            for (int v : vertices[u].adj) {
                if (!vertices[v].visited) {
                    vertices[v].visited = true;
                    vertices[v].distance = vertices[u].distance + 1;
                    vertices[v].previous = u;
                    Q.push(v);
                }
            }
        }
    }

    // Depth-First Search implementation
    void dfs() {
        int time = 0;

        // Reset all vertices
        for (int i = 0; i < _V; i++) {
            vertices[i].visited = false;
            vertices[i].previous = -1;
            vertices[i].finish = -1;
        }

        // Perform DFS for each unvisited vertex
        for (int i = 0; i < _V; i++) {
            if (!vertices[i].visited) {
                dfs_visit(i, time);
            }
        }
    }

    void dfs_visit(int u, int& time) {
        // Mark vertex as visited and set discovery time
        vertices[u].visited = true;
        time++;
        vertices[u].distance = time;  // discovery time
        
        cout << u << " ";  // Print vertex when discovered

        // Explore adjacent vertices
        for (int v : vertices[u].adj) {
            if (!vertices[v].visited) {
                vertices[v].previous = u;
                dfs_visit(v, time);
            }
        }

        // Set finish time
        time++;
        vertices[u].finish = time;
    }

    void print_path(int s, int v) {
        if (v == s)
           cout << s;
        else if (vertices[v].previous == -1)
           cout << "not connected";
        else {
           print_path(s,vertices[v].previous);
           cout << "->" << v;
        }
    }

    string toString() {
        stringbuf buffer;
        ostream os(&buffer);
        os << "Vertices = " << _V << ", Edges = " << _E << endl;
        for (int i = 0; i < _V; ++i) {
            os << i << "(" << degree(i) << "): ";
            for (const auto& l : vertices[i].adj) 
                os << l << " ";
            os << endl;
        }

        return buffer.str();
    }
private:
    int _V; // no. of vertices
    int _E; // no. of edges
    Vertex *vertices; // array of vertices
};

#endif
// Driver program to test the Graph class
// To compile: g++ -Wall -std=c++20 GraphDemo.cpp
// To run: ./a.out input1.txt
//         ./a.out input2.txt

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include "Graph.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	// check for correct command-line arguments
	if (argc != 2) {
	   cout << "Usage: " << argv[0] << " <filename>" << endl;
	   exit(-1);
	}

	string line;
	ifstream infile(argv[1]);
	// check if file can be opened for reading
	if (!infile.is_open()) {
	   cout << "Unable to open file: " << argv[1] << endl;
	   exit(-1);
	}

	getline(infile, line); // read # of vertices
	int V = stoi(line);
	getline(infile, line); // read # of edges
	int E = stoi(line);

	int i = 0;
	pair<int, int> *edges = new pair<int, int>[E];
	// read each line and create an array of edges
	while (getline(infile, line)) {
		size_t pos = line.find(' ', 0);
		string u = line.substr(0, pos);
		string v = line.substr(pos+1,line.length());
		edges[i++] = make_pair(stol(u),stol(v));
	}

	// check if number of edges read match E
	if (E != i) {
		cout << "No. of edges do not match, exiting" << endl;
		exit(-1);
	}

	// create a graph G = (V, E)
	Graph G(V, E, edges);
	// display G as an array of vertices
	cout << G.toString();

	// read source vertex for BFS
	int src;
	cout << "Enter source vertex: ";
	cin >> src;
	cout << "Results from BFS:\n";
	// test BFS
	G.bfs(src);
	for (int i = 0; i < V; ++i) {
		if (i != src) {
		   cout << src << " to " << i << ": ";
		   G.print_path(src, i);
		   cout << endl;
		}
	}

	// test DFS
	cout << "Results from DFS:\n";
	G.dfs();
	cout << endl;


	return 0;
}


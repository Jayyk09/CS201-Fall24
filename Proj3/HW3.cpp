/* 
Name: Jay Kumar Roy
Email: jroy4@crimson.ua.edu
Course Section: Fall 2024 CS 201
Homework #: 3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

// Data structure to store movie information
struct Movie {
  string name;
  vector<string> actors;
};

// Function to read movies from file
vector<Movie> readMoviesFromFile(const string &filename) {
  vector<Movie> movies;
  ifstream file(filename);
  string line;

  while (getline(file, line)) {
    Movie movie;
    stringstream ss(line);
    string item;

    // Extract movie name
    getline(ss, movie.name, '/');

    // Extract actors
    while (getline(ss, item, '/')) {
      movie.actors.push_back(item);
    }

    movies.push_back(movie);
  }

  return movies;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <movie_file> <search_query_file>"
         << endl;
    return 1;
  }

  string movieFileName = argv[1];
  string searchQueryFileName = argv[2];

  // Read movies from file
  vector<Movie> movies = readMoviesFromFile(movieFileName);

  // Create an unordered map for efficient searching
  unordered_map<string, vector<string>> movieActors;
  unordered_map<string, vector<string>> actorMovies;

  //calculate the time taken
  auto start = chrono::high_resolution_clock::now();

  // Populate the maps
  for (const auto &movie : movies) {
    for (const auto &actor : movie.actors) {
      movieActors[movie.name].push_back(actor);
      actorMovies[actor].push_back(movie.name);
    }
  }

  auto end = chrono::high_resolution_clock::now();
  double elapsed = chrono::duration<double, std::milli>(end - start).count();  //in microseonds

  // Read search queries from file
  ifstream searchQueryFile(searchQueryFileName);
  string query;

  //time taken to search the data structure

  auto start2 = chrono::high_resolution_clock::now();

  while (getline(searchQueryFile, query)) {
    cout << "Search Query: " << query << endl;

    // Search for movie
    if (movieActors.find(query) != movieActors.end()) {
      for (const auto &actor : movieActors[query]) {
        cout << actor << endl;
      }
    }
    // Search for actor
    else if (actorMovies.find(query) != actorMovies.end()) {
      for (const auto &movie : actorMovies[query]) {
        cout << movie << endl;
      }
    }
    // Not found
    else {
      cout << "Not Found" << endl;
    }

    cout << endl;
  }

  auto end2 = chrono::high_resolution_clock::now();
  double elapsed2 = chrono::duration<double, std::milli>(end2 - start2).count();

  cout << "Time taken to build the data structure: " << elapsed << endl;
  cout << "Time taken to search: " << elapsed2 << endl;

  double total_time = elapsed + elapsed2;

  cout << "Total time taken: " << total_time << endl;

  cout << elapsed << " " << elapsed2 << " " << total_time << endl << endl;



  // print the number of movies and actors
  cout << "Number of movies: " << movies.size() << endl;
  cout << "Number of actors: " << actorMovies.size() << endl;

  return 0;
}
/*
Name: Jay K Roy
Email: jroy4@crimson.ua.edu
Course Section: Fall 2024 CS 201
Homework #: 1
To Compile: g++ -std=c++17 -o tokenizeProgram parsetext.cpp
To Run:  ./tokenizeProgram yourinputfile.txt
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <locale>
#include <map>
#include <unordered_map>

using namespace std;

bool compare(const pair<string, int>& val1, const pair<string, int>& val2) {
    if (val1.second != val2.second)
        return val1.second > val2.second; 
    return val1.first < val2.first;
}

// merge function to merge two subarrays
void merge(vector<pair<string, int>>& vec, int left, int med, int right) {
    int n1 = med - left + 1;
    int n2 = right - med;

    vector<pair<string, int>> Left(n1);
    vector<pair<string, int>> Right(n2);



    for (int i = 0; i <n1; i++)
        Left[i] = vec[left + i];
    for (int i = 0; i <n2; i++)
        Right[i] = vec[med + 1 + i];



    int i= 0;
    int j = 0;
    int k = left;


    while (i < n1 && j < n2) {
        if (compare(Left[i], Right[j])) {
            vec[k] = Left[i];
            i++;
        } else {
            vec[k] = Right[j];
            j++;
        }
        k++;
   }


    while (i < n1) {
        vec[k] = Left[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = Right[j];
        j++;
        k++;
    }
}

// recursive merge sort function
void mergeSort(vector<pair<string,int>> & res, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(res, left, mid);
        mergeSort(res, mid + 1, right);

        merge(res, left, mid, right);
    }
}


vector<string> parseText(string filename)
{
    ifstream file(filename);
    string word;
    vector<string> words;
    while (file >> word)
    {
        words.push_back(word);
    }
    return words;
}

int main(int argc, char* argv[])
{
    //take filename from terminal
    string filename = argv[1];
    vector<string> words = parseText(filename);
    unordered_map<string, int> wordCount;
    for (auto word : words)
    {
        wordCount[word]++;
    }

    auto timestart = std::chrono::high_resolution_clock::now();

   vector<pair<string, int>> pair(wordCount.begin(), wordCount.end());
    mergeSort(pair, 0, pair.size() - 1);

    auto timeend = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeend - timestart);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    for (auto p : pair)
    {
        cout << p.first << " " << p.second << endl;
    }

    cout << "running time: " << duration.count() << " microseconds" << endl;
    cout << "word count: "<< pair.size()<< " word" <<endl;

    return 0;

}
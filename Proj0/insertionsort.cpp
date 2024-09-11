/*
 Name: Jay K Roy
 Email: jroy4@crimson.ua.edu
 Course Section: Fall 2024 CS 201
 Homework #: 0
*/


#include <iostream>
#include <vector>
using namespace std;

template< class RandomIt >
constexpr void insertionsort ( RandomIt first, RandomIt last ) {
    //loop through the array starting from the second element
    for (auto i = first + 1; i != last; ++i) {  
        //key is the current element and j is the element before key
        auto key = *i;
        auto j = i - 1;

        //compare key with the elements before it and move them to the right
        while (j >= first && *j > key) {
            *(j + 1) = *j;
            --j;
        }

        //insert key in the right position
        *(j + 1) = key;
        }
}

int main() {
    vector<int> v = {5, 4, 3, 2, 1};

    insertionsort(v.begin(), v.end());

    // Output the sorted array
    cout << "Sorted array: ";
    for(auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }

    cout << endl;

    return 0;
}
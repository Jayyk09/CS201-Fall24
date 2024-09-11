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

constexpr void mergesort ( RandomIt first, RandomIt last, RandomIt tempstart ) {
    if (first == last) return;
    if (first + 1 == last) return;

    // Find the middle of the array
    auto mid = first + (last - first) / 2;

    // Recursively sort the two halves
    mergesort(first, mid, tempstart); // sort the left half
    mergesort(mid, last, tempstart); // sort the right half

    // Merge the two halves
    auto i = first;
    auto j = mid;
    auto k = tempstart;

    // Merge the two halves
    while (i < mid && j < last) {
        if (*i < *j) {
            *k = *i;
            ++i;
        } else {
            *k = *j;
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements from the left half
    while (i < mid) {
        *k = *i;
        ++i;
        ++k;
    }

    // Copy the remaining elements from the right half
    while (j < last) {
        *k = *j;
        ++j;
        ++k;
    }

    // Copy the sorted elements back to the original array
    for (auto i = first; i != last; ++i) {
        *i = *tempstart;
        ++tempstart;
    }
}

int main() {
    vector<int> v = {5, 4, 3, 2, 1};
    vector<int> temp(v.size());

    mergesort(v.begin(), v.end(), temp.begin());

    // Output the sorted array
    cout << "Sorted array: ";
    for(auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }

    cout << endl;

    return 0;
}

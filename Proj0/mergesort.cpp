template< class RandomIt >

constexpr void mergesort ( RandomIt first, RandomIt last, RandomIt tempstart ) {
    if (first == last) return;
    if (first + 1 == last) return;
    auto mid = first + (last - first) / 2;
    mergesort(first, mid, tempstart);
    mergesort(mid, last, tempstart);
    auto i = first;
    auto j = mid;
    auto k = tempstart;
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
    while (i < mid) {
        *k = *i;
        ++i;
        ++k;
    }
    while (j < last) {
        *k = *j;
        ++j;
        ++k;
    }
    for (auto i = first; i != last; ++i) {
        *i = *tempstart;
        ++tempstart;
    }
}

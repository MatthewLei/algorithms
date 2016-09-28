/** quick sort is a divide-and-conqure sorting algorithm with time
    complexity of O(n^2) for worst case and O(nlogn) on average.
    This implementation uses indices to keep track of the pivot (piv)
    and the divider (div) witin an array.

    In an ascending sort, everything left of the divider is < the pivot,
    and everything right of the divider is >= the pivot.
    There are multiple ways of determining the pivot,
    which is the index to be compared with, but we will be simply 
    choosing the pivot that is the right-most value in the array.
    Better ways of determining pivot would be to take three values
    within the range and choose the middle value.

    The pivot is compared with all the values within the array, and
    when iterator (i) value is (in ascending sort) < the pivot,
    a swap occurs with div + 1 and div increments by one.
    Divider starts at left-most value.
    This is a recursive implementation (which could be parallelized).

    start: [ 6 ] [ 2 ] [ 7 ] [ 4 ] [ 1 ] [ 9 ] [ 8 ] [ 5 ] [ 3 ]
             |^                                              *
	   div+i                                            piv

    6 > 3, correct, because 6 is >= the divider

           [ 6 ] [ 2 ] [ 7 ] [ 4 ] [ 1 ] [ 9 ] [ 8 ] [ 5 ] [ 3 ]
             |     ^                                         *
	    div    i                                        piv

    2 < 3, swap div and i because 2 < piv, div + 1

           [ 2 ] [ 6 ] [ 7 ] [ 4 ] [ 1 ] [ 9 ] [ 8 ] [ 5 ] [ 3 ]
                   |^                                        *
     ...
           [ 2 ] [ 6 ] [ 7 ] [ 4 ] [ 1 ] [ 9 ] [ 8 ] [ 5 ] [ 3 ]
                   |                 ^                       *
    swap div and i, div+1
           [ 2 ] [ 1 ] [ 7 ] [ 4 ] [ 6 ] [ 9 ] [ 8 ] [ 5 ] [ 3 ]
                         |           ^                       *
     ...
           [ 2 ] [ 1 ] [ 7 ] [ 4 ] [ 6 ] [ 9 ] [ 8 ] [ 5 ] [ 3 ]
                         |                                  ^*
    swap piv with div value and call recursively
           [ 2 ] [ 1 ] [ 3 ] [ 4 ] [ 6 ] [ 9 ] [ 8 ] [ 5 ] [ 7 ]
	   {  |^   * }       { |^                            * }

    divide and conqure ...

**/

#include <iostream>
#include <vector>
#include <algorithm>   /// std::swap

using namespace std;

int nums[] = { 6, 2, 7, 4, 1, 9, 8, 5, 3 };

/**
    @brief partitions array into < div and >= div halfs
    @param arr Array
    @param left Left-most index in array
    @param right Right-most index in array
    @return The last index position of the divider
**/
int partition(vector<int>* arr, int left, int right)
{
    int piv;           /// pivot
    int div;           /// divider
    int it;            /// iterator
    
    /// initialize local variables
    piv = right;
    div = left;
    it = left;

    for (; it <= right; ++it) {
	if (arr->at(it) < arr->at(piv)) {
	    std::swap(arr->at(it), arr->at(div));
	    div += 1;
	}
    }
    std::swap(arr->at(piv), arr->at(div));
    return div;
}

/**
    quicksort function

    @param arr Array to quicksort
    @param left Left-most value in array
    @param right Right-most value in array

    Segment index is the index that divides
    the proceding recursive call in half
    [{quicksort()}, [seg_idx], {quicksort()}]
**/
void quicksort(vector<int>* arr, int left, int right)
{
    int seg_idx;       /// segment index

    if (left < right) {
	seg_idx = partition(arr, left, right);
	quicksort(arr, left, seg_idx - 1);
	quicksort(arr, seg_idx + 1, right);
    }
}

/// overloaded operator for printing
ostream& operator<<(ostream& os, vector<int> arr)
{
    for(int i = 0; i < arr.size(); ++i) {
	cout << " " << arr[i];
    }
    return os;
}

int main(int argc, char** argv)
{
    vector<int> arr(nums, nums + sizeof(nums) / sizeof(int));

    cout << arr << endl;
    quicksort(&arr, 0, arr.size() - 1);
    cout << arr << endl;

    return 0;
}

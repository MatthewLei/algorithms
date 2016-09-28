/// quick refresh of merge sort. for practice
/// rewrite in the future. better documentation and cleaner code
#include <iostream>
#include <queue>

using namespace std;

void printArr(vector<int> arr, int arr_sz)
{
    for (int i = 0; i < arr_sz; i++) {
	cout << arr.at(i) << " ";
	}
    cout << endl;
}

void merge(vector<int>* arr, int l, int m, int r)
{
    /// create two temporary lists [l, m] and [m+1, r] from arr
    vector<int> tmpL, tmpR;
    for (int i = l; i <= m; i++) {
	tmpL.push_back(arr->at(i));
    }
    for (int i = m+1; i <= r; i++) {
	tmpR.push_back(arr->at(i));
    }
    int itL = 0, itR = 0;
    for (int i = l; i <= r; i++) {
	if (tmpL.size() == itL) {
	    arr->at(i) = tmpR.at(itR);
	    itR += 1;
	} else if (tmpR.size() == itR) {
	    arr->at(i) = tmpL.at(itL);
	    itL += 1;
	} else {
	    if (tmpL.at(itL) < tmpR.at(itR)) {
		arr->at(i) = tmpL.at(itL);
		itL += 1;
	    } else {
		arr->at(i) = tmpR.at(itR);
		itR += 1;
	    }
	}
    }    
}

/// recursive call to div and conquer
void mergesort(vector<int>* arr, int l, int r)
{
    if (l < r) { /// until base case (one item)
	int mid = (l + r) / 2;
	mergesort(arr, l, mid);
	mergesort(arr, mid + 1, r);
	merge(arr, l, mid, r);
    }
}

int main(int argc, char** argv)
{
    int nums[] = {6,5,4,3,2,1};
    int arr_sz = sizeof(nums) / sizeof(int);
    vector<int> arr(nums, nums + arr_sz);
    mergesort(&arr, 0, arr_sz - 1); /// -1 for last index

    printArr(arr, arr_sz);

    return 0;
}

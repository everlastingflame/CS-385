/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Charles Booth
 * Version     : 1.0
 * Date        : 11/2/22
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);
/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long inversions = 0;
    for(int i = 0; i < length - 1; i++){
        for(int j = i + 1; j < length; j++){
            if(array[j] < array[i]){
                inversions ++;
            }
        }
    }
    return inversions;
}
/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    long inversions = 0;
    int* scratch = new int[length];
    for(int i = 0; i < length; i++){
        scratch[i] = 0;
    }
    int low = 0;
    int high = length - 1;
    inversions = mergesort(array, &scratch[0], low, high);
    delete [] scratch;
    return inversions;
}

long merge(int array[], int scratch[], int low, int mid, int high){
    long i1 = low; 
    long i2 = mid + 1;
    long i = low;
    long inversions = 0;
    while (i1 <= mid && i2 <= high){
        if (array[i1] <= array[i2]){
            scratch[i++] = array[i1++];
        }
        else{
            scratch[i++] = array[i2++];
            inversions += mid - i1 + 1;
        }
    }
    while(i1 <= mid){
        scratch[i++] = array[i1++];
    }
    while(i2 <= high){
        scratch[i++] = array[i2++];
    }
    for(int j = low; j <= high; j++){
        array[j] = scratch[j];
    }
    return inversions;
    
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long inversions = 0;
    if (low < high){
        int mid = low + (high - low)/2;
        inversions = inversions + mergesort(array, scratch, low, mid);
        inversions = inversions + mergesort(array, scratch, mid + 1, high);
        inversions = inversions + merge(array, scratch, low, mid, high);
    }
    return inversions;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    bool slow = false;

    if(argc > 1 && strcmp(argv[1], "slow") == 0){
        slow = true;
    }
    if(argc == 1){
        slow = false;
    }
    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }
    if(argc == 2 && (strcmp(argv[1], "slow") != 0)){
        cerr << "Error: Unrecognized option \'" << argv[1] << "\'." << endl;
        return 1;
    }


    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int length = values.size();

    if(length == 0){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // TODO: produce output
    if(slow == true){
        cout <<  "Number of inversions: " << count_inversions_slow(&values[0], length) << endl;
        return 0;
    }

    cout << "Number of inversions: " << count_inversions_fast(&values[0], length) << endl;
    return 0;
}
/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Charles Booth
 * Date        : 9/28/22
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I Pledge My Honor That I Have Abided By The Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (unsigned int i = 0; i < s.length(); i++){
        if ((isalpha(s[i]) == 0) || (isupper(s[i])!= 0)){
            cerr << "Error: String must contain only lowercase letters." << endl;
            return false;
        }
    }

    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.

    unsigned int vector = 0;
    unsigned int setter;

    for (unsigned int i = 0; i < s.length(); i++){
        setter = 1 << (s[i] - 'a');
        if((setter & vector) == 0){
            vector += setter; 
        }
        else{
            return false;
        }
    }

    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc != 2){
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    }

    if((is_all_lowercase(argv[1]) == false)){
        return 1;
    }

    if((is_all_lowercase(argv[1]) == true) && (all_unique_letters(argv[1]) == true)){
        cout << "All letters are unique." << endl;
        return 0;
    }

    if((is_all_lowercase(argv[1]) == true) && (all_unique_letters(argv[1]) == false)){
        cout << "Duplicate letters found." << endl;
        return 0;
    }

    else{
        return 1;
    }

}

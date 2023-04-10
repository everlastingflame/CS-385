/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Charles Booth  
 * Date        : 10/6/22
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I Pledge My Honor That I Have Abided By The Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector <int> steps;
vector <vector<int>> displaysteps;



vector <vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    
    if(num_stairs == 0){
        displaysteps.push_back(steps);
        return displaysteps;
    }

    if((num_stairs -1) >= 0){
        steps.push_back(1);
        get_ways(num_stairs - 1);
        steps.pop_back();
    }

    if((num_stairs - 2) >= 0){
        steps.push_back(2);
        get_ways(num_stairs - 2);
        steps.pop_back();
    }

    if((num_stairs -3) >= 0){
        steps.push_back(3);
        get_ways(num_stairs - 3);
        steps.pop_back();
    }
    return displaysteps; 
}

//helper
int stepWidth(int num){
    int length = 0;

    while(num > 0){
        num = num/10;
        length = length + 1;
    }

    return length;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int width = stepWidth(displaysteps.size());


    for(size_t i = 0; i < ways.size(); i++){
        cout << fixed << setw(width) << i + 1 << ". [";
        for(size_t j = 0; j < ways[i].size(); j++){
            cout << ways[i][j];
            if(ways[i].size() - 1 != j){
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

}




int main(int argc, char * const argv[]) {

if(argc != 2){
    cout << "Usage: ./stairclimber <number of stairs>" << endl;
    return 1;
}

if(atoi(argv[1]) < 1){
    cerr <<  "Error: Number of stairs must be a positive integer." << endl;
    return 1;
}

vector<vector<int>> storage = get_ways(atoi(argv[1]));

if(atoi(argv[1]) == 1){
    cout << "1 way to climb 1 stair." << endl; 
}
else{
    cout << storage.size() << " ways to climb " << atoi(argv[1]) << " stairs." << endl;
}

display_ways(storage);

return 0;
}

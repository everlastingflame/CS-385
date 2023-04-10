/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Charles Booth  
 * Date        : 10/20/22
 * Description : Solves the waterjug problem.
 * Pledge      : I Pledge My Honor That I Have Abided By The Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <queue>
using namespace std;



struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : a(_a), b(_b), c(_c), directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions << " (" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    // vector<string> path;
};

bool eq(State *one, State *two){
    if(((*one).a == (*two).a) && ((*one).b == (*two).b) && ((*one).c == (*two).c)){
        return true;
    }
    return false;
}

bool possible(int pour, int jug, int jugCap){
    if(jug < jugCap && pour > 0){
        return true;
    }
    return false;
}

string BFSM(int values[6]){
    int a = values[0];
    int b = values[1];
    int c = values[2]; 
    int ga = values[3];
    int gb = values[4];
    int gc = values[5];
    
    queue<State*> capQ;
    State *begin = new State(0, 0, c, "Initial state.");
    capQ.push(begin);
    State *goalState = new State(ga, gb, gc, "Goal");
    State *saveState = nullptr;
    string printer;
    State ***jugArray = new State**[a + 1];
    int pourCalc; 


    //creates 2d array
    for(int i = 0; i < a + 1; i++) {
        jugArray[i] = new State*[b + 1];
        for(int j = 0; j < b + 1; j++) {
            jugArray[i][j] = nullptr;
        }
    }

    while(!capQ.empty()){
        State *currentState = &(*capQ.front());
        capQ.pop();
        
        if(eq((currentState),(goalState))){
            string finalAnswer = (*currentState).to_string();
            while((*currentState).parent != nullptr){
                currentState = (*currentState).parent;
                finalAnswer = (*currentState).to_string() + "\n" + finalAnswer;
            }
            delete goalState;
            delete begin;

            for(int i = 0; i < a + 1; i++) {
                for(int j = 0; j < b + 1; j++) {
                    if(jugArray[i][j] != nullptr){
                        delete jugArray[i][j];
                    }
                }
                delete [] jugArray[i];
            }
            delete [] jugArray;

            return finalAnswer;
        }


        //C to A
        if(possible((*currentState).c, (*currentState).a, a)){
            if((*currentState).c < a - (*currentState).a){
                if((*currentState).c != 1 || (a - (*currentState).a != 1)){
                    printer = "Pour " + to_string((*currentState).c) + " gallons from C to A.";
                    saveState = new State((*currentState).a + (*currentState).c, (*currentState).b, 0, printer);
                }
                else{
                    printer = "Pour " + to_string((*currentState).c) +  " gallon from C to A.";
                    saveState = new State((*currentState).a + (*currentState).c, (*currentState).b, 0, printer);
                }
            }
            else{
                pourCalc = a - (*currentState).a;
                if((*currentState).c != 1 || (a - (*currentState).a != 1)){
                    printer = "Pour " + to_string(pourCalc) + " gallons from C to A.";
                    saveState = new State(a, (*currentState).b, (*currentState).c - pourCalc , printer);
                }
                else{
                    printer = "Pour " + to_string(pourCalc) +  " gallon from C to A.";
                    saveState = new State(a, (*currentState).b, (*currentState).c - pourCalc , printer);
                }
            }
            if(saveState != nullptr) {
                if(jugArray[(*saveState).a][(*saveState).b] == nullptr) {
                    (*saveState).parent = &(*currentState);
                    capQ.push(saveState);
                    jugArray[(*saveState).a][(*saveState).b] = saveState;
                } 
                else{
                    delete saveState;
                }
            }

            
        }
        //B to A
        if(possible((*currentState).b, (*currentState).a, a)){
            if((*currentState).b < a - (*currentState).a){
                if((*currentState).b != 1 && (a - (*currentState).a) != 1){
                    printer = "Pour " + to_string((*currentState).b) + " gallons from B to A.";
                    saveState = new State((*currentState).a + (*currentState).b, 0 , (*currentState).c, printer);
                }
                else{
                    printer = "Pour " + to_string((*currentState).b) +  " gallon from B to A.";
                    saveState = new State((*currentState).a + (*currentState).b, 0 , (*currentState).c, printer);
                }
            }
            else{
                pourCalc = a - (*currentState).a;
                if((*currentState).b != 1 && (a - (*currentState).a) != 1){
                    printer = "Pour " + to_string(pourCalc) + " gallons from B to A.";
                    saveState = new State(a, (*currentState).b - pourCalc, (*currentState).c , printer);
                }
                else{
                    printer = "Pour " + to_string(pourCalc) +  " gallon from B to A.";
                    saveState = new State(a, (*currentState).b - pourCalc, (*currentState).c , printer);
                }
            }
            if(saveState != nullptr) {
                if(jugArray[(*saveState).a][(*saveState).b] == nullptr) {
                    (*saveState).parent = &(*currentState);
                    capQ.push(saveState);
                    jugArray[(*saveState).a][(*saveState).b] = saveState;
                } 
                else{
                    delete saveState;
                }
            }
        }
        //C to B
        if(possible((*currentState).c, (*currentState).b, b)){
            if((*currentState).c < b - (*currentState).b){
                if((*currentState).c != 1 && (b - (*currentState).b) != 1){
                    printer = "Pour " + to_string((*currentState).c) + " gallons from C to B.";
                    saveState = new State((*currentState).a,  (*currentState).c + (*currentState).b, 0, printer);
                }
                else{
                    printer = "Pour " + to_string((*currentState).c) +  " gallon from C to B.";
                    saveState = new State((*currentState).a , (*currentState).c + (*currentState).b, 0, printer);
                }
            }
            else{
                pourCalc = b - (*currentState).b;
                if((*currentState).c != 1 && (b - (*currentState).b) != 1){
                    printer = "Pour " + to_string(pourCalc) + " gallons from C to B.";
                    saveState = new State((*currentState).a, b, (*currentState).c - pourCalc , printer);
                }
                else{
                    printer = "Pour " + to_string(pourCalc) +  " gallon from C to B.";
                    saveState = new State((*currentState).a, b, (*currentState).c - pourCalc , printer);
                }
            }

            //pushes current to parent and puts it onto the queue   
            if(saveState != nullptr) {
                if(jugArray[(*saveState).a][(*saveState).b] == nullptr) {
                    (*saveState).parent = &(*currentState);
                    capQ.push(saveState);
                    jugArray[(*saveState).a][(*saveState).b] = saveState;
                } 
                else{
                    delete saveState;
                }
            }
        }
        //A to B
        if(possible((*currentState).a, (*currentState).b, b)){
            if((*currentState).a < b - (*currentState).b){
                if((*currentState).a != 1 && (b - (*currentState).b) != 1){
                    printer = "Pour " + to_string((*currentState).a) + " gallons from A to B.";
                    saveState = new State(0, (*currentState).a + (*currentState).b , (*currentState).c, printer);
                }
                else{
                    printer = "Pour " + to_string((*currentState).a) +  " gallon from A to B.";
                    saveState = new State(0, (*currentState).a + (*currentState).b , (*currentState).c, printer);
                }
            }
            else{
                pourCalc = b - (*currentState).b;
                if((*currentState).a != 1 && (b - (*currentState).b) != 1){
                    printer = "Pour " + to_string(pourCalc) + " gallons from A to B.";
                    saveState = new State((*currentState).a - pourCalc, b, (*currentState).c , printer);
                }
                else{
                    printer = "Pour " + to_string(pourCalc) +  " gallon from A to B.";
                    saveState = new State((*currentState).a - pourCalc, b, (*currentState).c , printer);
                }
            }
            if(saveState != nullptr) {
                if(jugArray[(*saveState).a][(*saveState).b] == nullptr) {
                    (*saveState).parent = &(*currentState);
                    capQ.push(saveState);
                    jugArray[(*saveState).a][(*saveState).b] = saveState;
                } 
                else{
                    delete saveState;
                }
            }
        }
        //B to C
        if(possible((*currentState).b, (*currentState).c, c)){
            if((*currentState).b < c - (*currentState).c){
                if((*currentState).b != 1 && (c - (*currentState).c) != 1){
                    printer = "Pour " + to_string((*currentState).b) + " gallons from B to C.";
                    saveState = new State((*currentState).a , 0 , (*currentState).b + (*currentState).c, printer);
                }
                else{
                    printer = "Pour " + to_string((*currentState).b) +  " gallon from B to C.";
                    saveState = new State((*currentState).a , 0 , (*currentState).b + (*currentState).c, printer);
                }
            }
            else{
                pourCalc = c - (*currentState).c;
                if((*currentState).b != 1 && (c - (*currentState).c) != 1){
                    printer = "Pour " + to_string(pourCalc) + " gallons from B to C.";
                    saveState = new State((*currentState).a, (*currentState).b - pourCalc, c , printer);
                }
                else{
                    printer = "Pour " + to_string(pourCalc) +  " gallon from B to C.";
                    saveState = new State((*currentState).a, (*currentState).b - pourCalc, c , printer);
                }
            }
            if(saveState != nullptr) {
                if(jugArray[(*saveState).a][(*saveState).b] == nullptr) {
                    (*saveState).parent = &(*currentState);
                    capQ.push(saveState);
                    jugArray[(*saveState).a][(*saveState).b] = saveState;
                } 
                else{
                    delete saveState;
                }
            }
        }
        //A to C
        if(possible((*currentState).a, (*currentState).c, c)){
            if((*currentState).a < c - (*currentState).c){
                if((*currentState).a != 1 && (a - (*currentState).c) != 1){
                    printer = "Pour " + to_string((*currentState).a) + " gallons from A to C.";
                    saveState = new State(0, (*currentState).b, (*currentState).a + (*currentState).c, printer);
                }
                else{
                    printer = "Pour " + to_string((*currentState).a) +  " gallon from A to C.";
                    saveState = new State(0, (*currentState).b, (*currentState).a + (*currentState).c, printer);
                }
            }
            else{
                pourCalc = c - (*currentState).c;
                if((*currentState).a != 1 && (c - (*currentState).c) != 1){
                    printer = "Pour " + to_string(pourCalc) + " gallons from A to C.";
                    saveState = new State((*currentState).a - pourCalc, (*currentState).b, c , printer);
                }
                else{
                    printer = "Pour " + to_string(pourCalc) +  " gallon from A to C.";
                    saveState = new State((*currentState).a - pourCalc, (*currentState).b, c , printer);
                }
            }
            if(saveState != nullptr) {
                if(jugArray[(*saveState).a][(*saveState).b] == nullptr) {
                    (*saveState).parent = &(*currentState);
                    capQ.push(saveState);
                    jugArray[(*saveState).a][(*saveState).b] = saveState;
                } 
                else{
                    delete saveState;
                }
            }
        }
    }

    for(int i = 0; i < a + 1; i++) {
        for(int j = 0; j < b + 1; j++) {
            if(jugArray[i][j] != nullptr){
                delete jugArray[i][j];
            }
        }
        delete [] jugArray[i];
    }
    delete [] jugArray;
    delete begin;
    delete goalState;

    return "No solution.";
}

int main(int argc, char * const argv[]) {

if(argc != 7){
    cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
    return 1;
}

int inputs[6];
char letters[6] = {'A','B','C','A','B','C'};
for(int i = 1; i < 7; i++){
    istringstream iss(argv[i]);
    iss >> inputs[i];

    if(((i - 1 < 3) && !(iss)) || ((inputs[i] <= 0) && (i - 1 < 3))){
        cerr << "Error: Invalid capacity \'" << argv[i] << "\' for jug " << letters[i - 1] << "." << endl;
            return 1;
    }
    if(((i - 1 >= 3) && !(iss)) || ((inputs[i] < 0) && (i - 1 >= 3))){
        cerr << "Error: Invalid goal \'" << argv[i] << "\' for jug " << letters[i - 1] <<  "." <<endl;
            return 1;
    }
}

for(int i = 1; i < 4; i++){
     if(atoi(argv[i]) < atoi(argv[i + 3])){
        cerr << "Error: Goal cannot exceed capacity of jug " << letters[i-1] << "."<< endl;
        return 1;  
      }
    }

int sum = atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6]);
    if(atoi(argv[3]) != sum){
    cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
    return 1;
}
    int data[6] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6])};

    std::cout << BFSM(data);
return 0;

}
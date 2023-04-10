/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Charles Booth  
 * Date        : 9/17/22
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

    void numMax();


private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    int columnCount = 0;

    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80/(max_prime_width +1);

    cout << endl;
    cout << "Number of primes found: " << count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    //nRow finds the number of rows, LRow finds leftover numbers that aren't divided nicely
    int nRow = count_num_primes()/primes_per_row; 
    int LRows = (count_num_primes() % primes_per_row);

    //finds extra numbers that dont divide nicely
    if (LRows != 0 ){
        nRow = nRow + 1;
    }

    for(int i = 2; i <= limit_ ; i++){
       
        if(is_prime_[i] == true){
            if(columnCount == primes_per_row){
                columnCount = 0;
                cout << endl;
            }
            if(columnCount != 0) {
                cout << " ";
            }
            if(nRow > 1){
                cout << setw(max_prime_width) << i;
                columnCount += 1;
            }
            else{
                cout << i; 
                columnCount += 1;
            }
        }
    }

}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int num = 0;
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i] == true){
            num = num + 1;
        }
    }
    return num;
}


//initialize a new method to evade the const in count_num_primes()
void PrimesSieve::numMax(){
    num_primes_ = count_num_primes();
    int max = 0;
    for(int i = 2; i < limit_; i++){
        if(is_prime_[i] == true){
            max = i;
        }
    }
    max_prime_ = max;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for(int i = 0; i <= limit_; i++){
        if((i == 0) || (i == 1)){
            is_prime_[i] = false;
        }
        else{
            is_prime_[i] = true;
        }
    }
    
    int i = 2;
    while(i <= sqrt(limit_)){
        if(is_prime_[i] == true){ //since this is true, we loop through the code and find more non-prime integers
            for(int j = i*i; j <= limit_; j += i){
                is_prime_[j] = false; //we mark all the non-prime integers with false so our iteration time gets significantly lower
            }
            i++;
        }
        else{
            i++; //incrementing here if the first case is false
        }
    }
    numMax();
}



int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.

    int length = 0;

    while(num > 0){
        num = num/10;
        length = length + 1;
    }

    return length;
}


int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    else{
        
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve*sieve = new PrimesSieve(limit);
    sieve->display_primes();
    delete sieve;
    return 0;
}
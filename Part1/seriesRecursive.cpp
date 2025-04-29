#include <iostream>
#include <cstdlib> 

//TODO: add your documentation here
// TO DO: implement the recursive series function
//      Hint: it should return a long long (integers)

long long seriesRecursive(int n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1 || n == 2) {
        return 1;
    }
    else {
        return seriesRecursive(n-1) + 2 * seriesRecursive(n-2) + 4 * seriesRecursive(n-3);
    }
}

int main(int argc, char* argv[]) {
    // Read n from command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1; 
    }

    // Convert n to an integer
    int n = std::atoi(argv[1]); 

    // Compute series value of n
    long long result = seriesRecursive(n); 
    std::cout << "seriesRecursive(" << n << ") = " << result << std::endl;

    return 0; 
}

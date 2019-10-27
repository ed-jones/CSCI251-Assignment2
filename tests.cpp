#include "header.h"
using namespace std;

void argumentTests(int argc, char* argv[]) {
    // This function checks that the user has supplied the program 
    // with the correct arguments to function, and terminates if arguments invalid

    // Checks for the correct number of arguments (2 plus the executable)
    if (argc != 3) {
        cerr << "Error: program given an incorrect number arguments" << endl;
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    if (n < 1 || n > 5) {
        cerr << "Error: n must be an integer between 1 and 5 inclusive" << endl;
        exit(EXIT_FAILURE);
    }

    if (m < 1 || m > 10) {
        cout << "Error: m must be an integer between 1 and 10 inclusive" << endl;
        exit(EXIT_FAILURE);
    }
}
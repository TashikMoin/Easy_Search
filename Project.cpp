#include <math.h>
#include <iostream>
#include <string>
#include "Searching_Algorithms.h"

using namespace std;

int main() {
    clock_t start;
    start = clock();
    searchFromFileKM("GATC");
    start = clock() - start;
    cout << "Time taken for searching in KNUTTH MORRIS: " << (float)start / CLOCKS_PER_SEC << " seconds\n";

    start = clock();
    searchFromFileRK("GATC");
    start = clock() - start;
    cout << "Time taken for searching in RABIN KARP: " << (float)start / CLOCKS_PER_SEC << " seconds\n";
}

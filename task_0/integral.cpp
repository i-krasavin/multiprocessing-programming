#include <cmath>
#include <iostream>
#include <omp.h>

using namespace std;

#define MAX_THREADS 4

int main(int argc, char** argv)
{
    cout << "Compute result for integral of sin(x) from -10 to 20\n";

    double start = -10, end = 20, result = 0;
    int nSteps = 1000000;
    double segment = (end - start)/nSteps;

    cout << "Segment: " << segment << "\n";

    #pragma omp parallel for num_threads(MAX_THREADS) reduction(+:result)
    for(int i = 1; i < nSteps; i++) {
        result += sin(start + i * segment);
    }

    result = (result + 0.5 * (sin(start) + sin(end))) * segment;

    cout << "Result: " << result;

    return 0;
}

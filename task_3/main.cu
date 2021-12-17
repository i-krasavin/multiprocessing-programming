#include "cuda_runtime.h"
#include <iostream>
#include <math.h>

using namespace std;

double r(double value, int k)
{
    return (double)round((pow(2, k) * value)) / pow(2, k);
}

// define kernel
__global__ void customInt(double *x, double *y, double *result)
{
    int index = threadIdx.x;
    result[index] = (index + 1) * pow((y[index] - sin(x[index])), 2);
}

void runRungeKutta(int thereadCount, double *listX, double *listY, double h)
{
    double **fPointer = new double *[3];
    for (int i = 0; i < 3; i++)
    {
        fPointer[i] = new double[thereadCount];
    }

    double *listY1 = new double[thereadCount];
    listY1 = listY;

    while (r(listX[0], 2) < 1.0)
    {
        double *f0Pointer;
        cudaMalloc((void **)&f0Pointer, sizeof(double) * thereadCount);
        customInt<<<1, thereadCount>>>(listX, listY, f0Pointer);
        cudaMemcpy(&fPointer[0], f0Pointer, sizeof(int) * thereadCount, cudaMemcpyDeviceToHost);

        double *f1Pointer;
        cudaMalloc((void **)&f1Pointer, sizeof(double) * thereadCount);
        customInt<<<1, thereadCount>>>(listX, listY, f1Pointer);
        cudaMemcpy(&fPointer[1], f1Pointer, sizeof(int) * thereadCount, cudaMemcpyDeviceToHost);

        double *f2Pointer;
        cudaMalloc((void **)&f2Pointer, sizeof(double) * thereadCount);
        customInt<<<1, thereadCount>>>(listX, listY, f2Pointer);
        cudaMemcpy(&fPointer[2], f2Pointer, sizeof(double) * thereadCount, cudaMemcpyDeviceToHost);

        for (int j = 0; j < thereadCount; j++)
        {
            listY[j] = listY1[j] + (fPointer[0][j] + 2.0 * fPointer[1][j] + fPointer[2][j]) / 6.0;
        }

        // increment
        listX[0] += h;
    }

    // output
    for (int e = 0; e < thereadCount; e++) {
        cout << listY[e] << " ";
    }
}

int main()
{
    int thereadsCount = 1000;
    double *listX = new double[thereadsCount];
    double *listY = new double[thereadsCount];
    double h = 0.05;

    for (int i = 0; i < thereadsCount; i++)
    {
        listX[i] = rand() * 500;
        listY[i] = rand() * 500;
    }

    runRungeKutta(thereadsCount, listX, listY, h);

    return 0;
}
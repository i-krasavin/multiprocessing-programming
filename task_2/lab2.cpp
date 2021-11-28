#include <iostream>
#include <math.h>
#include "mpi.h"

using namespace std;

double generateRandon() {
	double randNumber = 10 + (rand() % static_cast<int>(20 - 5 + 1));
	cout << "Imprecise Rand = " << randNumber << endl;

	return randNumber;
}

double computeIntegral(double a, double b, double n) {
	double h = (b - a) / n;
	double res = 0;

	for (int i = 0; i < n; i++) {
		res += tan((i + 0.5) * h + b);
	}

	return res;
}

int main(int argc, char* argv[])
{
	double a = generateRandon();
	double b = (a + generateRandon()) * 10;
	double n = generateRandon() * 100;
	double h = (b - a) / n;

	cout << "Init MPI" << endl;
	MPI_Init(&argc, &argv);
	int rank;
	double integral, response[2];

	MPI_Request request;
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	cout << "Rank: " << rank << endl;

	if (rank == 0 || rank == 1) {
		integral = computeIntegral(a + rank * h / 3, a + (rank + 1) * h / 3, n);
		cout << "Rank = " << rank << "; " << "Integral = " << integral << endl;
		cout << "Rank = " << rank << "; " << "Send request to another rank" << endl;
		MPI_Isend(&integral, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, &request);
	}

	if (rank == 2) {
		MPI_Recv(&response[0], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&response[1], 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
		cout << "Rank = 2; Reseived request" << endl;
		integral = computeIntegral(20, 30, 1000) + response[0] + response[1];
		cout << "Rank = 2; Final result of integral is " << integral << endl;
	}

	MPI_Finalize();
	return 0;
}
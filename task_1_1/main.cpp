#include <iostream>
#include <omp.h>
#include <fstream>
#include <math.h>

using namespace std;

double g(double t, double y, double z) {
  return pow(t, 2);
}

double f(double t, double y, double z) {
  return pow(cos(y), 2) + t;
}

int main() {
  double t0, y0, z0, tn;
  int n, threadCount;

  ofstream resultFile;
  resultFile.open("results.txt");

  cout << "Enter values" << endl;

  cout << "Enter t0: ";
  cin >> t0;

  cout << "Enter y0: ";
  cin >> y0;

  cout << "Enter z0: ";
  cin >> z0;

  cout << "Enter the point tn that will be calculated: ";
  cin >> tn;

  cout << "Enter the split amount n: ";
  cin >> n;

  cout << "Enter the threads number: ";
  cin >> threadCount;

  double * t, * y, * z;

  t = (double * ) malloc(n * sizeof(double));
  y = (double * ) malloc(n * sizeof(double));
  z = (double * ) malloc(n * sizeof(double));

  double h = (tn - t0) / n;
  double k1, k2, k3, k4, l1, l2, l3, l4;

  t[0] = t0;
  y[0] = y0;
  z[0] = z0;

#pragma omp parallel for num_threads(threadCount)
  for (int i = 1; i < n; i++) {
    k1 = h * f(t[i - 1], y[i - 1], z[i - 1]);
    l1 = h * g(t[i - 1], y[i - 1], z[i - 1]);

    k2 = h * f(t[i - 1] + h / 2, y[i - 1] + k1 / 2, z[i - 1] + l1 / 2);
    l2 = h * g(t[i - 1] + h / 2, y[i - 1] + k1 / 2, z[i - 1] + l1 / 2);

    k3 = h * f(t[i - 1] + h / 2, y[i - 1] + k2 / 2, z[i - 1] + l2 / 2);
    l3 = h * g(t[i - 1] + h / 2, y[i - 1] + k2 / 2, z[i - 1] + l2 / 2);

    k4 = h * f(t[i - 1] + h, y[i - 1] + k3, z[i - 1] + l3);
    l4 = h * g(t[i - 1] + h, y[i - 1] + k3, z[i - 1] + l3);
    t[i] = t[i - 1] + h;
    y[i] = y[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    z[i] = z[i - 1] + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
  }

  for (int i = 0; i < n; i++) {
    resultFile << t[i] << " ";
  }

  resultFile << endl;

  for (int i = 0; i < n; i++) {
    resultFile << y[i] << " ";
  }

  resultFile << endl;

  for (int i = 0; i < n; i++) {
    resultFile << z[i] << " ";
  }

  resultFile.close();

  return 0;
}

#include <iostream>
#include <math.h>
#include <iostream>

using namespace std;

double integrateBySin(double firstVal, double secondVal)
{
    return sin(secondVal);
}

void runRungeKuttaMethod(double startValue, double endValue, double y, double h) {
    int n = (int)((endValue - startValue) / h);

    for (int i = 0; i < n; i++)
    {
        double k1 = integrateBySin(startValue, y);
        double k2 = integrateBySin(startValue + h / 2.0, y + h * k1 / 2.0);
        double k3 = integrateBySin(startValue + h / 2.0, y + h * k2 / 2.0);
        double k4 = integrateBySin(startValue + h, y + h * k3);

        y += (k1 + 2 * k2 + 2 * k3 + k4) * h / 6.0;

        startValue += h;
    }

    cout << "x =  " << y;
}

int main()
{
    double startValue, endValue, y, h;
    cout << "Enter the start value\n";
    cin >> startValue;
    cout << "Enter the end value\n";
    cin >> endValue;
    cout << "Enter the y\n";
    cin >> y;
    cout << "Enter the h\n";
    cin >> h;

    runRungeKuttaMethod(startValue, endValue, y, h);
    return 0;
}
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    cout << "Enter A and B: ";
    int a, b;
    cin >> a >> b;
    cout << "A + B = " << a + b << '\n'
         << "A - B = " << a - b << '\n'
         << "A * B = " << a * b << '\n'
         << "A / B = " << a / b << '\n';
         if (a > b)
            cout << "max = " << a << '\n';
         else
            cout << "max = " << b << '\n';
        if (a > b)
            cout << "min = " << b << '\n';
         else
            cout << "min = " << a << '\n';
}

#include <iostream>
#include <cmath>

using namespace std;

const double STATETAX = 0.04;
const double COUNTYTAX = 0.04;


int main() {
    double result = floor(3.78);
    return result;
}
// Give summary of tax to be paid
void taxMan(double revenue) {
    double total_tax = revenue * STATETAX + revenue * COUNTYTAX;
    // summary print to console
    cout << "Revenue = " << total_tax << endl
            << "State Tax = " << STATETAX * 100 << "%" << endl
            << "County Tax = " << COUNTYTAX * 100 << "%" << endl
            << "Total Tax = $" << total_tax;
}
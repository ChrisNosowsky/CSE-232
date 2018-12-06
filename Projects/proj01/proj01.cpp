//Created by Chris Nosowsky

#include <iostream>
#include <iomanip>
#include <cmath>
using std::endl;

int main() {
    long year;
    double userSlope;
    double slope = 0.01173;
    double intercept = 34.3491;


    std::cout << "";
    std::cin >> year;
    std::cout << "";
    std::cin >> userSlope;

    double temp = slope * year + intercept;
    std::cout << std::fixed << std::setprecision(2) << temp << endl;
    //y-intercept/slope
    long year2 = std::round(((temp +7)- intercept)/slope);
    std::cout << year2 << endl;
    long year3 = std::round(((temp+7) - intercept)/userSlope);
    std::cout << year3 << endl;

}

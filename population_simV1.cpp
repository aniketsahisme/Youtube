// Include Files
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

// To not type std:: again and again
using namespace std;

// Gloabl variable initialization
int war_period = 50, tension = 0;
double K = 1'000'000'000, tech_factor = 0;

// Function Declaration and Function Code
double update_population(double g, double Ip, double K, mt19937& rng)
{
    // Function Logic
    double r_;

    // Only for debugging
    double I_Ip = Ip;

    // War chance
    uniform_int_distribution<int> war(1, war_period + tension);  // Mapping

    if (war(rng) == 1)
    {
        Ip -= 0.05 * Ip;
        cout << "\nWar occured!!!";
    }
    r_ = g * (1 - Ip / K);
    Ip *= (1 + r_);

    cout << "\n\nIp > P: " << (I_Ip > Ip);  // For debugging

    return Ip;
}

// Function Declaration and Function Code
double noise_F(mt19937& rng)
{
    static std::uniform_real_distribution<double> dist(-0.05, 0.05);
    double noise = dist(rng);
    return noise;
}
// Main function Declaration
int main()
{
    // To increase Output speed
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    // Declaration
    double b, e_b, d, e_d, g, _r, Ip, ag;
    // Initialization
    int i = 0, j = 0;
    bool advance_100_years = true;

    static mt19937 rng(time(0));  // Chance basically srand(time(0)) and rand()

    // Input remove comments
    // cout << "Enter the birth rate: ";
    // cin >> b;
    // cout << "Enter the death rate: ";
    // cin >> d;
    // cout << "Enter the Initial Population: ";
    // cin >> Ip;

    b = 0.05, d = 0.03, Ip = 1000;
    double noise;

    // Output
    // To make output presentable
    cout << fixed << setprecision(0);

    cout << "\nThe population at year " << 0 << ": " << static_cast<long long>(Ip);

    // Processing
    // Loop
    do
    {
        while (i < 100)
        {
            noise = noise_F(rng);
            e_b = b;
            e_d = d;
            _r = e_b - e_d + noise;
            Ip = update_population(_r, Ip, K, rng);
            // Output
            cout << "\nThe population at year " << (j * 100 + i++) + 1 << ": " << Ip;
        }
        i = 0;
        ++j;

        cout << "\nAdvance 100 years(1/0): ";
        cin >> advance_100_years;
    } while (advance_100_years);

    // Successful execution return statement
    return 0;
}
